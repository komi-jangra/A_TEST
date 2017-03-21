#
# Makefile for SS7 stack
#
SHELL=/bin/sh

  subdir = common   

all clean:
	for dir in $(subdir); do \
	    if cd $$dir && $(MAKE) $@ && cd ..; then \
		true; \
	    else \
		exit 1; \
	    fi; \
	done
