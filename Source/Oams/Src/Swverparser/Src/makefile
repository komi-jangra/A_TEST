include ../../../../Csapp/Util/make.opt

lib1=libSwVerParser.so
objs1:= swversion_parser.${PLATFORM}.o

USERINCL := -I../Inc/ 
      
all: lib1  install

install:
	cp -f $(lib1) $(REL_BIN)/CommonLib/CP/

uninstall:
	rm -f $(REL_BIN)/CommonLib/CP/$(lib1)

lib1 : $(lib1)


$(lib1): $(objs1)
	$(CC) $(LFLAGS) $(LIBS)  -shared -o $@ $^

%.${PLATFORM}.o: %.c
	$(CC) $(CFLAGS) $(USERINCL) -D__C_APPL -c $^ -o $@


clean:
	-rm $(lib1) $(objs1)
