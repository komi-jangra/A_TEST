/*  *********************************************************************
    File: testssl.c

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: testssl.c    Main function for the sample client


    ****************************************************************** */

#include "ssl.h"
#include "testssl.h"

#if MAC
#undef BIG_ENDIAN /* conflict with BSAFE */
#include <GUSI.h>
int gethostname(char *, int);
#elif WIN32
#include <winsock.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{   uint32      ipAddr;
    int         port;
} PeerSpec;

#ifdef WIN32
static SSLErr AcceptClientConnection(int port, SOCKET *socketNo, PeerSpec *peer);
static SSLErr MakeServerConnection(char *hostName, int port, SOCKET *socketNo, PeerSpec *peer);
#else
static SSLErr AcceptClientConnection(int port, int *socketNo, PeerSpec *peer);
static SSLErr MakeServerConnection(char *hostName, int port, int *socketNo, PeerSpec *peer);
#endif

static SSLErr ConfigureGenericSSLSession(SSLContext *ctx);
static SSLErr ReadPrivateKey(SSLRSAPrivateKey *key, SSLContext *ctx);
static SSLErr AddCertificates(SSLContext *ctx);
static SSLErr AddDistinguishedNames(SSLContext *ctx);
static SSLErr AddDHParams(SSLContext *ctx);

#define SERVER_MESSAGE  "<HTML><HEAD><TITLE>SSLRef 3 Test Server</TITLE></HEAD><BODY><H2>You have sucessfully made a secure connection!</H2>Message from the 'testssl' sample application, a part of <A HREF=\"http://home.netscape.com/newsref/std/SSL.html\">SSLRef 3.0</A>.</BODY></HTML>\015\012"
#define CLIENT_REQUEST  "GET /\015\012"

#define DEFAULTSERVER   0
#define DEFAULTHOST     "ssl3.netscape.com"
#define DEFAULTPORT     443
#define DEFAULTVERSION  SSL_Version_Undetermined
#define DEFAULTAUTH     0
#define DEFAULTCACHE    1
#define KEY_PASSWORD    "password"

void *gRandomRef;

int
main(int argc, char *argv[])
{   int                 i;
#ifdef WIN32
    SOCKET              sock;
    WORD                wVersionRequested;
    WSADATA             wsaData;
#else
    int                 sock;
#endif
    SSLErr              err;
    SSLContext          *ctx;
    uint32              length;
    int                 isServer = DEFAULTSERVER, port = DEFAULTPORT;
    int                 clientAuth = DEFAULTAUTH, useCache = DEFAULTCACHE;
    char                *hostName = DEFAULTHOST;
    SSLProtocolVersion  version = DEFAULTVERSION;
    uint8               buffer[4096];
    void                *databaseRef;
    PeerSpec            peer;
    SSLBuffer           peerID;
    SSLRSAPrivateKey    privKey;

#if MAC
    GUSISetup(GUSIwithSIOUXSockets);
    GUSISetup(GUSIwithInternetSockets);
    printf("*** Initialize ***\n");
#endif

    for (i = 1; i < argc; i++)
    {   if (argv[i][0] == '-')
        {   switch (argv[i][1])
            {   case 'c':
                    isServer = 0;
                    break;
                case 's':
                    isServer = 1;
                    break;
                case '2':
                    version = SSL_Version_2_0;
                    break;
                case '3':
                    version = SSL_Version_3_0_Only;
                    break;
                case 'h':
                    version = SSL_Version_3_0_With_2_0_Hello;
                    break;
                case 'n':
                    version = SSL_Version_Undetermined;
                    break;
                case 'A':
                    clientAuth = 1;
                    break;
                case 'a':
                    clientAuth = 0;
                    break;
                case 'R':
                    useCache = 1;
                    break;
                case 'r':
                    useCache = 0;
                    break;
                case 'p':
                    if (argv[i][2] >= '0' && argv[i][2] <= '9')
                        sscanf(argv[i]+2,"%d", &port);
                    else if (argc > (i+1))
                        sscanf(argv[++i],"%d", &port);
                    else
                        goto usage;
                    break;
                default:
                    printf("Bad argument %s\n", argv[i]);
                    goto usage;
                case 'H':
                case '?':
                    goto usage;
            }
        }
        else
            hostName = argv[i];
    }

    ctx = (SSLContext *)malloc(SSLContextSize());
    ConfigureGenericSSLSession(ctx);

    #ifdef WIN32
    wVersionRequested = 0x0101;

    if (err = WSAStartup(wVersionRequested, &wsaData))
        {
            printf("Could not start winsocks\n");
            exit(-1);
        }
    if ((LOBYTE(wsaData.wVersion) != 1) || (HIBYTE(wsaData.wVersion) != 1))
        {
            printf("Wrong version of winsock loaded.  We only work with 1.1\n");
            WSACleanup();
            exit(-1);
        }
    #endif

    if (isServer || clientAuth)
    {   ERR(ReadPrivateKey(&privKey, ctx));
        ERR(SSLSetPrivateKey(ctx, &privKey));
        ERR(AddCertificates(ctx));
    }
    if (isServer)
        ERR(SSLSetExportPrivateKey(ctx, &privKey));
    if (isServer && clientAuth)
        ERR(AddDistinguishedNames(ctx));

    ERR(AddDHParams(ctx));

    ERR(SSLSetProtocolVersion(ctx, version));

    if (useCache)
    {   InitDatabase("SessionDB", &databaseRef);
        ERR(SSLSetSessionRef(ctx, databaseRef));
    }
    else
        ERR(SSLSetSessionRef(ctx, (void*)0));

    memset(&peer, 0, sizeof(PeerSpec));
    if (isServer)
    {   ERR(SSLSetProtocolSide(ctx, SSL_ServerSide));
        ERR(SSLSetRequestClientCert(ctx, clientAuth));
        ERR(AcceptClientConnection(port, &sock, &peer));
    }
    else
    {   ERR(SSLSetProtocolSide(ctx, SSL_ClientSide));
        ERR(MakeServerConnection(hostName, port, &sock, &peer));
    }

    if (useCache)
    {   peerID.data = (uint8*)&peer;
        peerID.length = sizeof(peer);
        ERR(SSLSetPeerID(ctx, peerID));
    }

    ERR(SSLSetIORef(ctx, (void*)&sock));

    do
    {   err = SSLHandshake(ctx);
    } while (err == SSLWouldBlockErr);

    ERR(err);

    if (err == SSLNoErr)
    {   if (isServer)
        {   buffer[0] = 0;
            while (err == 0 && buffer[0] != '\012')
            {   length = 1;
                ERR(err = SSLRead(buffer, &length, ctx));
                fwrite(buffer, 1, length, stdout);
                if (err == SSLWouldBlockErr)
                    err = SSLNoErr;
            }
        
            if (err == SSLNoErr)
            {   length = sizeof(SERVER_MESSAGE) - 1;
                ERR(err = SSLWrite(SERVER_MESSAGE, &length, ctx));
            }
        
            if (err == SSLNoErr)
                ERR(SSLClose(ctx));
        }
        else
        {   
            length = sizeof(CLIENT_REQUEST) - 1;
        
            ERR(err = SSLWrite(CLIENT_REQUEST, &length, ctx));
            while (err == 0)
            {   length = sizeof(buffer);
                ERR(err = SSLRead(buffer, &length, ctx));
                fwrite(buffer, 1, length, stdout);
                if (err == SSLWouldBlockErr)
                    err = SSLNoErr;
            }
            if (err == SSLNoErr)
                ERR(SSLClose(ctx));
        }
    }

#ifdef WIN32
    closesocket(sock);
    WSACleanup();
#else
    close(sock);
#endif
    if (useCache)
        ERR(DisposeDatabase());

    SSLDeleteContext(ctx);
    free((char*)ctx);
    
#if BSAFE
    B_DestroyAlgorithmObject(gRandomRef);
#endif
        
    printf("*** done [%d] ***\n", err);
    return 0;

usage:
    fprintf(stderr, "Usage: %s [-c | -s] [-2 | -3 | -h | -n] [host] [-p port]\n", argv[0]);
    fprintf(stderr, "   -c: Act as client\n   -s: Act as server\n");
    fprintf(stderr, "   -2: SSL 2.0 only\n   -3: SSL 3.0 only\n");
    fprintf(stderr, "   -h: Support SSL 3.0, but allow SSL 2.0 hello messages\n");
    fprintf(stderr, "   -n: Support both 2.0 and 3.0\n");
    fprintf(stderr, "   -A: Request or support client authentication\n");
    fprintf(stderr, "   -a: Do not request or support client authentication\n");
    fprintf(stderr, "   -R: Use a cache to resume sessions\n");
    fprintf(stderr, "   -r: Disable session resumption\n");
    fprintf(stderr, "   host: Host to connect to\n   -p port: Use port number port\n");
    fprintf(stderr, "   Defaults are:\n    side: %s\n", DEFAULTSERVER ? "server" : "client");
    fprintf(stderr, "    host: %s\n    port: %d\n", DEFAULTHOST, DEFAULTPORT);
    {   char    *protocolName;
#define NAMECASE(version)   case version: protocolName = #version; break;
        switch(DEFAULTVERSION)
        {   NAMECASE(SSL_Version_2_0)
            NAMECASE(SSL_Version_3_0)
            NAMECASE(SSL_Version_3_0_Only)
            NAMECASE(SSL_Version_3_0_With_2_0_Hello)
            NAMECASE(SSL_Version_Undetermined)
        }
        fprintf(stderr, "    protocol: %s\n", protocolName);
    }
    fprintf(stderr, "    request authentication: %s\n", DEFAULTAUTH ? "yes" : "no");
    fprintf(stderr, "    use session caching: %s\n", DEFAULTCACHE ? "yes" : "no");
    exit(1);
    return 1;
}

static SSLErr
#ifdef WIN32
MakeServerConnection(char *hostName, int port, SOCKET *socketNo, PeerSpec *peer)
#else
MakeServerConnection(char *hostName, int port, int *socketNo, PeerSpec *peer)
#endif
{   struct sockaddr_in  addr;
    struct hostent      *ent;
    struct in_addr      host;

    if (hostName[0] >= '0' && hostName[0] <= '9')
    {
#if MAC
        host.s_addr = inet_addr(hostName).s_addr;
#else
        host.s_addr = inet_addr(hostName);
#endif
    }
    else
    {   ent = gethostbyname(hostName);
        if (!ent)
        {   printf("gethostbyname failed\n");
            exit(1);
        }
        memcpy(&host, ent->h_addr, sizeof(struct in_addr));
    }
    *socketNo = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_addr = host;
    addr.sin_port = htons((u_short)port);

    addr.sin_family = AF_INET;
    if (connect(*socketNo, (struct sockaddr *) &addr, sizeof(struct sockaddr_in)) != 0)
    {   printf("connect returned error\n");
        exit(1);
    }

    peer->ipAddr = addr.sin_addr.s_addr;
    peer->port = htons((u_short)port);

    return SSLNoErr;
}   

static SSLErr
#ifdef WIN32
AcceptClientConnection(int port, SOCKET *socketNo, PeerSpec *peer)
#else
AcceptClientConnection(int port, int *socketNo, PeerSpec *peer)
#endif
{   struct sockaddr_in  addr;
    struct hostent      *ent;
    char                buffer[100];
    int                 len;

    *socketNo = socket(AF_INET, SOCK_STREAM, 0);

    gethostname(buffer, 100);
    ent = gethostbyname(buffer);
    if (!ent)
    {   printf("gethostbyname failed\n");
        exit(1);
    }
    memcpy(&addr.sin_addr, ent->h_addr, sizeof(struct in_addr));

    addr.sin_port = htons((u_short)port);
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    len = sizeof(struct sockaddr_in);
    if (bind(*socketNo, (struct sockaddr *) &addr, len))
    {   printf("bind failed\n");
        exit(1);
    }
    if (listen(*socketNo, 1))
    {   printf("listen failed\n");
        exit(1);
    }
    *socketNo = accept(*socketNo, (struct sockaddr *) &addr, &len);
    if (*socketNo < 0)
    {   printf("accept failed\n");
        exit(1);
    }

    peer->ipAddr = addr.sin_addr.s_addr;
    peer->port = htons((u_short)port);

    return SSLNoErr;
}

static SSLErr
ConfigureGenericSSLSession(SSLContext *ctx)
{   ERR(SSLInitContext(ctx));
    ERR(SSLSetAllocFunc(ctx, SSLAlloc));
    ERR(SSLSetFreeFunc(ctx, SSLFree));
    ERR(SSLSetReallocFunc(ctx, SSLRealloc));
    ERR(SSLSetRandomFunc(ctx, SSLRandom));
    ERR(SSLSetTimeFunc(ctx, SSLTime));
    ERR(SSLSetConvertTimeFunc(ctx, SSLConvertTime));
    ERR(SSLSetReadFunc(ctx, SocketRead));
    ERR(SSLSetWriteFunc(ctx, SocketWrite));

    ERR(SSLSetAddSessionFunc(ctx, SSLAddSession));
    ERR(SSLSetGetSessionFunc(ctx, SSLGetSession));
    ERR(SSLSetDeleteSessionFunc(ctx, SSLDeleteSession));
    
#if BSAFE
    ERR(SeedRandom(&gRandomRef));
    SSLSetRandomRef(ctx, *(B_ALGORITHM_OBJ*)gRandomRef);
#else
    ERR(SeedRandom(&gRandomRef));
    SSLSetRandomRef(ctx, gRandomRef);
#endif

    return SSLNoErr;
}   

static SSLErr
ReadPrivateKey(SSLRSAPrivateKey *privKey, SSLContext *ctx)
{   FILE        *keyFile;
    uint8       keyData[1024];
    SSLBuffer   key, password;

    password.data = (uint8*)KEY_PASSWORD;
    password.length = sizeof(KEY_PASSWORD) - 1;

    keyFile = fopen("private.key", "rb");
    if (keyFile)
    {   key.data = keyData;
        key.length = fread(keyData, 1, 1024, keyFile);
        fclose(keyFile);
    
        if (key.length > 0 && key.length < 1024)
        {   SSLDecodePrivateKey(key, password, privKey, ctx);
        }
    }

    return SSLNoErr;
}

static SSLErr
AddCertificates(SSLContext *ctx)
{   SSLErr      err;
    FILE        *certFile;
    SSLBuffer   certData, cert;
    uint8       *progress;
    uint32      length;

    /* Format of certificate file is a set of { 24-bit length, followed by a cert },
        root cert last */

    certFile = fopen("test.crt", "rb");
    if (certFile)
    {   certData.data = malloc(10240);
        certData.length = fread(certData.data, 1, 10240, certFile);
        fclose(certFile);
    
        progress = certData.data;
        while (progress < certData.data + certData.length)
        {   length = *progress++;
            length = (length << 8) + *progress++;
            length = (length << 8) + *progress++;
            cert.data = malloc(length);
            cert.length = length;
            memcpy(cert.data, progress, length);
            progress += cert.length;
            if ((err = SSLAddCertificate(ctx, cert, 1, 0)) != 0)
            {   free(certData.data);
                return err;
            }
        }
        
        free(certData.data);
        
        cert.data = 0;      /* Just check chain validity */
        if ((err = SSLAddCertificate(ctx, cert, 0, 1)) != 0)
            return err;
    }
    
    return SSLNoErr;
}

/* extern arrays are in verisign.c; sizes are copied by hand from those definitions */
extern unsigned char CLASS1_ROOT_SUBJECT_NAME[];
#define CLASS1_ROOT_SUBJECT_NAME_SIZE 97
extern unsigned char CLASS2_ROOT_SUBJECT_NAME[];
#define CLASS2_ROOT_SUBJECT_NAME_SIZE 97
extern unsigned char CLASS3_ROOT_SUBJECT_NAME[];
#define CLASS3_ROOT_SUBJECT_NAME_SIZE 97
extern unsigned char CLASS4_ROOT_SUBJECT_NAME[];
#define CLASS4_ROOT_SUBJECT_NAME_SIZE 97

static
unsigned char RSA_COMMERCIAL_CA_ROOT_SUBJECT_NAME[] =
{   0x30, 0x5F, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x55, 0x53, 0x31, 
    0x20, 0x30, 0x1E, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x13, 0x17, 0x52, 0x53, 0x41, 0x20, 0x44, 0x61, 
    0x74, 0x61, 0x20, 0x53, 0x65, 0x63, 0x75, 0x72, 0x69, 0x74, 0x79, 0x2C, 0x20, 0x49, 0x6E, 0x63, 
    0x2E, 0x31, 0x2E, 0x30, 0x2C, 0x06, 0x03, 0x55, 0x04, 0x0B, 0x13, 0x25, 0x53, 0x65, 0x63, 0x75, 
    0x72, 0x65, 0x20, 0x53, 0x65, 0x72, 0x76, 0x65, 0x72, 0x20, 0x43, 0x65, 0x72, 0x74, 0x69, 0x66, 
    0x69, 0x63, 0x61, 0x74, 0x69, 0x6F, 0x6E, 0x20, 0x41, 0x75, 0x74, 0x68, 0x6F, 0x72, 0x69, 0x74, 
    0x79
};

static SSLErr
AddDistinguishedNames(SSLContext *ctx)
{   SSLErr      err;
    SSLBuffer   derDN;

    derDN.data = RSA_COMMERCIAL_CA_ROOT_SUBJECT_NAME;
    derDN.length = sizeof(RSA_COMMERCIAL_CA_ROOT_SUBJECT_NAME);
    if (ERR(err = SSLAddDistinguishedName(ctx, derDN)) != 0)
        return err;
    derDN.data = CLASS1_ROOT_SUBJECT_NAME;
    derDN.length = CLASS1_ROOT_SUBJECT_NAME_SIZE;
    if (ERR(err = SSLAddDistinguishedName(ctx, derDN)) != 0)
        return err;
    derDN.data = CLASS2_ROOT_SUBJECT_NAME;
    derDN.length = CLASS2_ROOT_SUBJECT_NAME_SIZE;
    if (ERR(err = SSLAddDistinguishedName(ctx, derDN)) != 0)
        return err;
    derDN.data = CLASS3_ROOT_SUBJECT_NAME;
    derDN.length = CLASS3_ROOT_SUBJECT_NAME_SIZE;
    if (ERR(err = SSLAddDistinguishedName(ctx, derDN)) != 0)
        return err;
    derDN.data = CLASS4_ROOT_SUBJECT_NAME;
    derDN.length = CLASS4_ROOT_SUBJECT_NAME_SIZE;
    if (ERR(err = SSLAddDistinguishedName(ctx, derDN)) != 0)
        return err;

    return SSLNoErr;
}

/* DH primes are in dhprimes.c */
extern unsigned char prime1024[1024/8];
unsigned char generator[1] = { 2 };

static SSLErr
AddDHParams(SSLContext *ctx)
{   SSLErr          err;
    SSLDHParams     dhParams;

#if RSAREF
    dhParams.primeLen = sizeof(prime1024);
    dhParams.generatorLen = sizeof(generator);
    dhParams.prime = prime1024;
    dhParams.generator = generator;
#elif BSAFE
    {   int                     rsaErr;
        A_DH_KEY_AGREE_PARAMS   dhKey;
        B_ALGORITHM_METHOD      *chooser[] = { &AM_DH_KEY_AGREE, 0 };
    
        dhKey.prime.len = sizeof(prime1024);
        dhKey.base.len = sizeof(generator);
        dhKey.prime.data = prime1024;
        dhKey.base.data = generator;
        dhKey.exponentBits = 128;
    
        if ((rsaErr = B_CreateAlgorithmObject(&dhParams)) != 0)
            return SSLUnknownErr;
        if ((rsaErr = B_SetAlgorithmInfo(dhParams, AI_DHKeyAgree, (POINTER)&dhKey)) != 0)
            return SSLUnknownErr;
        if ((rsaErr = B_KeyAgreeInit(dhParams, (B_KEY_OBJ)NULL_PTR, chooser, NO_SURR)) != 0)
            return SSLUnknownErr;
    }
#endif

    if (ERR(err = SSLSetDHAnonParams(ctx, &dhParams)) != 0)
        return err;

    return SSLNoErr;
}
