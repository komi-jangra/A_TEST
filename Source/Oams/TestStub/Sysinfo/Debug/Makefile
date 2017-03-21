#************ START ***********
#HDRFILES=-I ../../../../Inc/Oam \
 -I ../../../../Inc/Oams \
 -I ../../../../Inc/Sys \
 -I ../../../../Inc/Csapp \
 -I ../../../Oams/Src/Cellh/Inc/ \
 -I ../../Inc \
 -I ../../../../Inc/Sys/ \
 -I ../../../../Inc/Dbs \
 -I ../../../../Inc/ \
 -I ../../../../Inc/Ipc/ 
ROOT_PATH = ../../../../..
HDRFILES=-I $(ROOT_PATH)/Inc/Sys \
        -I $(ROOT_PATH)/Inc/Ipc \
       -I $(ROOT_PATH)/Inc/Dbs \
    -I $(ROOT_PATH)/Source/Oams/Inc \
    -I $(ROOT_PATH)/Inc/Oams \
    -I $(ROOT_PATH)/Inc/Oam \
    -I $(ROOT_PATH)/Source/Oams/Src/Cellh/CellhModel/Inc \
    -I $(ROOT_PATH)/Source/Oams/Src/Cellh/Inc \
    -I $(ROOT_PATH)/Inc/Csapp 
    

CFLAGS=-g -D__C_APPL
COMPILER= gcc 
USRLIBPATH=-L$(ROOT_PATH)/Bin/Host/CommonLib/CP \
	 -L$(ROOT_PATH)/Src/Oams/Bin/Host/CommonLib
TARGET=TestSysInfoEncoder
USRLIB=-lCLIB -llog -ltau -lfrm -linst-DB -ldbwrappers 
#CC=gcc -g -Wall $(HDRFILES)  $(LIBRARY_PATH) -D__C_APPL -DCPLUSPLUS   
$(TARGET):../main.c
	$(COMPILER) $(CFLAGS) $(HDRFILES) $(USRLIBPATH) $(USRLIB) ../main.c $(ROOT_PATH)/Source/Oams/Src/Cellh/Src/oamscellh_sysinfo_encoder.c -o $(TARGET)

clean:
	rm -rf *.o TestSysInfoEncoder 
