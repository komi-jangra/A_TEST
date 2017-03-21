include $(ccm_project_path)/lib/macros.mk

PORTDIR=$(ccm_project_path)/port/

ROOTDIR=$(ccm_project_path)/port/cspl/build/
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

all:
	cd $(ARCH) && $(MAKE) -f $(ccm_project_path)/port/cspl/build/Makefile ROOTDIR=$(ROOTDIR) PORTDIR=$(PORTDIR) 


clean:
	cd $(ARCH) && rm -f $(objects) $(target) $(library) $(port_objects) $(driver_objects) $(mpset_objects) $(cpset_oblects)
