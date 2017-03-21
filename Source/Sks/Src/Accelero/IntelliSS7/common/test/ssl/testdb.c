/*  *********************************************************************
    File: testdb.c

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: testdb.c     database support for resumable sessions


    ****************************************************************** */

#include "testssl.h"
#include <stdio.h>
#include <stdlib.h>
#ifndef WIN32
#include <unistd.h>
#endif
#include <string.h>

#define DB_VERSION 1

typedef struct TestDBLine
{   struct TestDBLine   *next;
    struct TestDBLine   *prev;
    int                 keyLength;
    void                *key;
    int                 valueLength;
    void                *value;
} TestDBRecord;

typedef struct
{   char            version;
    FILE            *dbFile;
    int             recordCount;
    TestDBRecord    *records;
} TestDatabase;

static SSLErr ReadV1Database(TestDatabase *db);
static SSLErr QueueDBRecord(TestDatabase *db, TestDBRecord *rec);
static SSLErr DequeueDBRecord(TestDatabase *db, TestDBRecord *rec);
static SSLErr FreeDB(TestDatabase *db);
static SSLErr FreeRecord(TestDatabase *db, TestDBRecord *rec);
static SSLErr FindDBRecord(TestDatabase *db, void *key, int keyLength, TestDBRecord **result);
static SSLErr ReadDatabase(TestDatabase *db);
static SSLErr WriteV1Database(TestDatabase *db);

static TestDatabase testDB;

SSLErr
InitDatabase(const char *filename, void **dbRef)
{   SSLErr      err;

    testDB.recordCount = 0;
    testDB.records = 0;
    
    testDB.dbFile = fopen(filename, "rb+");
    if (testDB.dbFile)
    {   if (ERR(err = ReadDatabase(&testDB)) != 0)
            return err;
    }
    else        /* Create a new empty database */
    {   testDB.dbFile = fopen(filename, "wb+");
        if (!testDB.dbFile)
            return ERR(SSLIOErr);
        testDB.version = DB_VERSION;
        if (ERR(err = WriteV1Database(&testDB)) != 0)
            return err;
    }
    
    *dbRef = (void*)&testDB;
    return SSLNoErr;
}

SSLErr  
DisposeDatabase()
{   SSLErr  err;
    
    if (ERR(err = WriteV1Database(&testDB)) != 0)
        return err;
    if (ERR(err = FreeDB(&testDB)) != 0)
        return err;
    
    fclose(testDB.dbFile);
    
    return SSLNoErr;
}

static SSLErr   
ReadDatabase(TestDatabase *db)
{   SSLErr          err;
    
    if (ERR(err = FreeDB(db)) != 0)
        return err;
    
    fseek(db->dbFile, 0, SEEK_SET);
    
    if (fread(&db->version, sizeof(char), 1, db->dbFile) < 1)
        return ERR(SSLIOErr);
    
    if (db->version == DB_VERSION)
        return ERR(ReadV1Database(db));
    else
        return ERR(SSLUnsupportedErr);
}

static SSLErr
ReadV1Database(TestDatabase *db)
{   TestDBRecord    *rec;
    int             count;
    SSLErr          err;
    
    if (fread(&count, sizeof(int), 1, db->dbFile) < 1)
        return ERR(SSLIOErr);
    
    while (count--)
    {   if ((rec = (TestDBRecord*)malloc(sizeof(TestDBRecord))) == 0)
            return ERR(SSLMemoryErr);
        rec->next = rec->prev = 0;
        if (fread(&rec->keyLength, sizeof(int), 1, db->dbFile) < 1)
            return ERR(SSLIOErr);
        ASSERT(rec->keyLength < 50);
        if (fread(&rec->valueLength, sizeof(int), 1, db->dbFile) < 1)
            return ERR(SSLIOErr);
        if ((rec->key = malloc(rec->keyLength)) == 0)
            return ERR(SSLMemoryErr);
        if ((rec->value = malloc(rec->valueLength)) == 0)
            return ERR(SSLMemoryErr);
        if (fread(rec->key, 1, rec->keyLength, db->dbFile) < rec->keyLength)
            return ERR(SSLIOErr);
        if (fread(rec->value, 1, rec->valueLength, db->dbFile) < rec->valueLength)
            return ERR(SSLIOErr);
        
        if (ERR(err = QueueDBRecord(db, rec)) != 0)
            return err;
    }
    
    return SSLNoErr;
}

static SSLErr
WriteV1Database(TestDatabase *db)
{   TestDBRecord    *rec;
    int     count;
    
    ASSERT(db->dbFile != 0);
    fseek(db->dbFile, 0, SEEK_SET);
    
    if (fwrite(&db->version, sizeof(char), 1, db->dbFile) < 1)
        return ERR(SSLIOErr);
    if (fwrite(&db->recordCount, sizeof(int), 1, db->dbFile) < 1)
        return ERR(SSLIOErr);
    
    count = 0;
    rec = db->records;
    while (rec)
    {   if (fwrite(&rec->keyLength, sizeof(int), 1, db->dbFile) < 1)
            return ERR(SSLIOErr);
        if (fwrite(&rec->valueLength, sizeof(int), 1, db->dbFile) < 1)
            return ERR(SSLIOErr);
        if (fwrite(rec->key, 1, rec->keyLength, db->dbFile) < rec->keyLength)
            return ERR(SSLIOErr);
        if (fwrite(rec->value, 1, rec->valueLength, db->dbFile) < rec->valueLength)
            return ERR(SSLIOErr);
        rec = rec->next;
        DEBUGMSG("Record written");
        ++count;
    }
    
    fflush(db->dbFile);
    
    ASSERT(count == db->recordCount);
    
    return SSLNoErr;
}

/* If using in a multithreaded environment, add locking to [Dequeue|Queue]DBRecord */
static SSLErr
QueueDBRecord(TestDatabase *db, TestDBRecord *rec)
{   
    rec->next = db->records;        /* Init this record */
    rec->prev = 0;
    
    ASSERT(db->records == 0 || db->records->prev == 0);
    
    if (db->records != 0)
        db->records->prev = rec;    /* Set prev for previous first record */
    db->records = rec;              /* Enqueue this one */
    ++(db->recordCount);
    DEBUGVAL1("Record added, now %d", db->recordCount);
    return SSLNoErr;
}

/* If using in a multithreaded environment, add locking to [Dequeue|Queue]DBRecord */
static SSLErr
DequeueDBRecord(TestDatabase *db, TestDBRecord *rec)
{   
    if (rec->next != 0)
    {   ASSERT(rec->next->prev == rec);
        rec->next->prev = rec->prev;
    }
    if (rec->prev != 0)
    {   ASSERT(rec->prev->next == rec);
        rec->prev->next = rec->next;
    }
    else
    {   ASSERT(db->records == rec);
        db->records = rec->next;
    }
    --(db->recordCount);
    DEBUGVAL1("Record removed, now %d", db->recordCount);
    return SSLNoErr;
}

static SSLErr
FreeDB(TestDatabase *db)
{   SSLErr          err;
    TestDBRecord    *rec, *next;
    
    next = db->records;
    
    while (next != 0)
    {   rec = next;
        next = rec->next;
        if (ERR(err = FreeRecord(db, rec)) != 0)
            return err;
    }
    
    return SSLNoErr;
}

static SSLErr
FreeRecord(TestDatabase *db, TestDBRecord *rec)
{   SSLErr      err;
    
    if (ERR(err = DequeueDBRecord(db, rec)) != 0)
        return err;
    
    free(rec->key);
    free(rec->value);
    free(rec);
    
    return SSLNoErr;
}

static SSLErr
FindDBRecord(TestDatabase *db, void *key, int keyLength, TestDBRecord **result)
{   TestDBRecord    *rec;
    
    *result = 0;
    
    rec = db->records;
    
    while (rec != 0)
    {   if (rec->keyLength == keyLength && memcmp(rec->key, key, keyLength) == 0)
        {   *result = rec;
            return SSLNoErr;
        }
        rec = rec->next;
    }
    
/* Return no error for a search sucessfully completed, but without matching
 *  (in this case, *result == 0)
 */
    return SSLNoErr;
}

SSLErr
SSLAddSession (SSLBuffer key, SSLBuffer data, void *sessionRef)
{   TestDatabase    *db = (TestDatabase*)sessionRef;
    TestDBRecord    *rec;
    SSLErr          err;
    
    ASSERT(db != 0);
    if (!db)
        return SSLNoErr;
    
    if (ERR(err = FindDBRecord(db, key.data, key.length, &rec)) != 0)
        return err;
    
    if (rec == 0)       /* record not found; create */
    {   if ((rec = (TestDBRecord*)malloc(sizeof(TestDBRecord))) == 0)
            return ERR(SSLMemoryErr);
        rec->keyLength = key.length;
        if ((rec->key = malloc(rec->keyLength)) == 0)
            return ERR(SSLMemoryErr);
        memcpy(rec->key, key.data, rec->keyLength);
        rec->valueLength = data.length;
        if ((rec->value = malloc(rec->valueLength)) == 0)
            return ERR(SSLMemoryErr);
        memcpy(rec->value, data.data, rec->valueLength);
        if (ERR(err = QueueDBRecord(db, rec)) != 0)
            return err;
    }
    else                /* record found; replace value */
    {   if (ERR(err = DequeueDBRecord(db, rec)) != 0)
            return err;
        if (rec->value != 0)
            free(rec->value);
        rec->valueLength = data.length;
        if ((rec->value = malloc(rec->valueLength)) == 0)
            return ERR(SSLMemoryErr);
        memcpy(rec->value, data.data, rec->valueLength);
        if (ERR(err = QueueDBRecord(db, rec)) != 0)
            return err;
    }
    
    return SSLNoErr;
}

SSLErr
SSLGetSession (SSLBuffer key, SSLBuffer *sessionData, void *sessionRef)
{   TestDatabase    *db = (TestDatabase*)sessionRef;
    TestDBRecord    *rec;
    SSLErr          err;
    
    ASSERT(db != 0);
    if (!db)
        return SSLSessionNotFoundErr;
        
    if (ERR(err = FindDBRecord(db, key.data, key.length, &rec)) != 0)
        return err;
    
    if (!rec)
        return SSLSessionNotFoundErr;
    
/* Allocation method must match that used in SSLAlloc() so this buffer can be freed with SSLFree() */
    sessionData->length = rec->valueLength;
    if ((sessionData->data = malloc(sessionData->length)) == 0)
        return ERR(SSLMemoryErr);
    memcpy(sessionData->data, rec->value, sessionData->length);
    
    return SSLNoErr;
}

SSLErr
SSLDeleteSession (SSLBuffer key, void *sessionRef)
{   TestDatabase    *db = (TestDatabase*)sessionRef;
    TestDBRecord    *rec;
    SSLErr          err;
    
    ASSERT(db != 0);
    if (!db)
        return SSLSessionNotFoundErr;
    
    if (ERR(err = FindDBRecord(db, key.data, key.length, &rec)) != 0)
        return err;
    
    if (!rec)
        return SSLSessionNotFoundErr;
    
    if (ERR(err = FreeRecord(db, rec)) != 0)
        return err;
    
    return SSLNoErr;
}
