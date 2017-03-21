
include $(ROOTDIR)cspl.mk

target = cspl.lib.o 
library = libcspl.a libporting.a libmpset.a libcpset.a

objects = \
	es.o              \
	run.o              \
	manifest.o        \
	cspl.o            \
	cpool.o           \
	stacklayer.o      \
	ylib-bitmap.o     \
	ylib-bufop.o      \
	ylib-hash.o       \
	ylib-pool.o       \
	ylib-tree.o       \
	ylib-bitstring.o  \
	ylib-crc.o        \
	ylib-list.o       \
	ylib-squeue.o

mpset_objects = mpoolset.o
cpset_oblects = cpoolset.o

ifdef	PORTDIR
	port_objects = port.o
	driver_objects = 
else
	port_objects = \
		os.o	\
		eflow.o

	driver_objects = \
		shell.o
endif

default: $(target) $(library)

$(target): $(objects) $(port_objects) $(driver_objects) $(mpset_objects) $(cpset_oblects)
	$(CSPL_LINKOBJ) -o $@ $(objects) $(port_objects) $(driver_objects) $(mpset_objects) $(cpset_oblects)

$(library): $(objects) $(port_objects) $(driver_objects) $(mpset_objects) $(cpset_oblects)
	$(CSPL_AR) libcspl.a $(objects) 
	$(CSPL_AR) libporting.a $(port_objects) $(driver_objects)
	$(CSPL_AR) libmpset.a $(mpset_objects) 
	$(CSPL_AR) libcpset.a $(cpset_oblects) 
	$(CSPL_RANLIB) libcspl.a
	$(CSPL_RANLIB) libporting.a
	$(CSPL_RANLIB) libmpset.a
	$(CSPL_RANLIB) libcpset.a

$(objects):%.o: $(ROOTDIR)../src/%.c
	$(CSPL_COMPILE) $(CSPL_FLAGS) -c $(CSPL_INCLUDES) -c $< -o $@

$(mpset_objects):%.o: $(ROOTDIR)../src/%.c
	$(CSPL_COMPILE) $(CSPL_FLAGS) -c $(CSPL_INCLUDES) -c $< -o $@

$(cpset_oblects):%.o: $(ROOTDIR)../src/%.c
	$(CSPL_COMPILE) $(CSPL_FLAGS) -c $(CSPL_INCLUDES) -c $< -o $@

ifdef	PORTDIR
$(port_objects):%.o: $(PORTDIR)%.c
	$(CSPL_COMPILE) $(CSPL_FLAGS) -c $(CSPL_INCLUDES) -c $< -o $@
else
$(port_objects):%.o: $(ROOTDIR)../ports/$(PORT)/%.c
	$(CSPL_COMPILE) $(CSPL_FLAGS) -c $(CSPL_INCLUDES) -c $< -o $@

$(driver_objects):%.o: $(ROOTDIR)../drivers/$(DRIVER)/%.c
	$(CSPL_COMPILE) $(CSPL_FLAGS) -c $(CSPL_INCLUDES) -c $< -o $@
endif

clean:
	rm -rf $(objects) $(target) $(library) $(port_objects) $(driver_objects) $(mpset_objects) $(cpset_oblects)

configshow:
	@echo 
	@echo "Configuration"
	@echo "    CSPL_COMPILE (Compiler) is:        $(CSPL_COMPILE)"
	@echo "    CSPL_FLAGS (Flags) are:            $(CSPL_FLAGS)"
	@echo "    CSPL_LINKOBJ (Partial Linker) is:  $(CSPL_LINKOBJ)"
	@echo "    CSPL_LINKEXE (Final Linker) is:    $(CSPL_LINKEXE)"
	@echo "    CSPL_LIBRARIES (Libraries) are:    $(CSPL_LIBRARIES)"
	@echo "    CSPL_AR (Archiver) is:             $(CSPL_AR)"
	@echo "    CSPL_RANLIB (Ranlib) is:           $(CSPL_RANLIB)"
	@echo "Usage:"
	@echo "    $(MAKE) [PORT=<port>] [DRIVER=<driver>] [CONFIG=<file>] <target>"
	@echo
