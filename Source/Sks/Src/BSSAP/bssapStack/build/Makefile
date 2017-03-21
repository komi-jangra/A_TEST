#
# Makefile for GSN system
#
		
include $(ccm_project_path)/lib/macros.mk

SHELL = /bin/sh

subdir +=  cspl port ss7stack 


all:
	for dir in $(subdir); do \
	    if cd $$dir && $(MAKE) $@ && cd ..; then \
		true; \
	    else \
		exit 1; \
	    fi; \
	done
	-find $(ccm_project_path) -name Makefile -exec tail -1 {} \; > /dev/null 2>&1
	-find $(ccm_project_path) -name '*.mk' -exec tail -1 {} \; > /dev/null 2>&1


clean: 
	for dir in $(subdir); do \
	    if cd $$dir && $(MAKE) $@ && cd ..; then \
		true; \
	    else \
		exit 1; \
	    fi; \
	done


