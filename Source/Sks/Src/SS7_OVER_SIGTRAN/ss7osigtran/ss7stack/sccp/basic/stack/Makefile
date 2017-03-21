##############################################################################
#
#       Makefile:
#                       Makefile for HSS test target development
#                       environment.
#
#      DATE       NAME           REFERENCE       REASON
#      -----------------------------------------------------
#      28Jan'98   Sriganesh Kini                 Original
#
#  Copyright (C) 1998, Hughes Software Systems
##############################################################################

include ${sccp_project_path}/sc_macro.mk

SUBDIRS= \
	stat \
	errp \
	db \
	init \
	scmg \
	scrc \
	sclc \
	scoc \
	dsccp \
	redn \
	disp

OBJS=	

all:            build
install:        install_objs
touch:          touch_all
clean:          clean_all

build:  $(SUBDIRS)
	-for i in $(SUBDIRS);\
        do\
                echo "Building in $$i" ; \
                (cd $$i ; \
                        $(MAKE) \
                ) ; \
        done

install_objs:
	$(RM) $(INSTALL_DIR)/$(STACK_ARCHIVE)
	-for i in $(SUBDIRS);\
        do\
                echo "Copying objects from $$i" ; \
                (cd $$i ; \
                        $(MAKE) install \
                ) ; \
        done

touch_all:
	-for i in $(SUBDIRS);\
        do\
                echo "Touching files in $$i" ; \
                (cd $$i ; \
                        $(MAKE) touch \
                ) ; \
        done

clean_all:
	-for i in $(SUBDIRS);\
        do\
                echo "Cleaning $$i" ; \
                (cd $$i ; \
                        $(MAKE) clean \
                ) ; \
        done

