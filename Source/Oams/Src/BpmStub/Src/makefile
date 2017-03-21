include ../../../../Csapp/Util/make.opt

lib1=libbpmstub.a
objs1:= stubLib.o

USERINCL := -I../Inc/ 
      
all: lib1  install

install:
	cp -f $(lib1) $(REL_BIN)/CommonLib/CP/

uninstall:
	rm -f $(REL_BIN)/CommonLib/CP/$(lib1)

lib1 : $(lib1)


#$(lib1): $(objs1)
#	$(CC) $(LFLAGS) $(LIBS)  -pthread -lrt -shared -WL -o $@ $^

$(lib1): $(objs1)
	ar rcs $(lib1) $(objs1)

%.${PLATFORM}.o: %.c
	$(CC) $(CFLAGS) $(USERINCL) -pthread -D__USE_XOPEN2K -D__C_APPL -c $^ -o $@


clean:
	-rm $(lib1) $(objs1)
