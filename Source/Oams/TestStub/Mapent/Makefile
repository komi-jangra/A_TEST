#************ START ***********
HDRFILES=-I ../../Inc \
 -I ../../../../../../Inc/Sys/ \
 -I ../../../../../../Inc/Db \
 -I ../../../../Inc/ \
 -I ../../../../../../Inc/Ipc/ 
CFLAGS=-g -D__C_APPL
COMPILER=gcc 
USRLIBPATH=-L$(ROOT_PATH)/Bin/Host/CommonLib -L$(ROOT_PATH)/Src/Oams/Bin/Host/CommonLib
TARGET=TestMapLtrxPtrxEnt
USRLIB= -lfrm -ltau -lmapLtrxPtrxEnt -ldbwrappers -lCLIB
#CC=gcc -g -Wall $(HDRFILES)  $(LIBRARY_PATH) -D__C_APPL -DCPLUSPLUS   
$(TARGET): MapLtrxPtrxEntMain.c
	$(COMPILER) $(CFLAGS) $(HDRFILES) $(USRLIBPATH) $(USRLIB) MapLtrxPtrxEntMain.c -o $(TARGET)

clean:
	rm -rf *.o TestMapLtrxPtrxEnt 

#$(TARGET): MapLtrxPtrxEntMain.c
#	$(CC)  MapLtrxPtrxEntMain.c $(LIBRARIES) -o $@ 
#$(OBJ) : MapLtrxPtrxEntMain.c
#	$(CC) -c MapLtrxPtrxEntMain.c
