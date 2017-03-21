include $(ccm_project_path)/lib/macros.mk

PORTDIR=$(ccm_project_path)/port/
ROOTDIR=$(ccm_project_path)/port/cspl/build/

all:
	cd $(ARCH) && $(MAKE) -f $(ccm_project_path)/port/cspl/build/Makefile ROOTDIR=$(ROOTDIR) PORTDIR=$(PORTDIR)

clean:
	cd $(ARCH) && $(MAKE) -f $(ccm_project_path)/port/cspl/build/Makefile ROOTDIR=$(ROOTDIR) PORTDIR=$(PORTDIR) $@

