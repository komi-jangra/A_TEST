
##########################################################################
#                                                                        #
#                                                                        #
#             Sample Makefile -- for UNIX platforms only                 #
#                                                                        #
#                                                                        #
#                                                                        #
# Copyright 1997, Hughes Software Systems, Ltd.                          #
##########################################################################

include ${sccp_project_path}/sc_macro.mk

OBJS=
SUBDIRS=        src


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
	-for i in $(SUBDIRS);\
        do\
                echo "Copying objects from $$i" ; \
                cp $$i/*.o $(INSTALL_DIR) ; \
                $(AR) -r $(INSTALL_DIR)/$(STACK_ARCHIVE) $$i/*.o ; \
        done

touch_all:
	-for i in $(SUBDIRS);\
        do\
                echo "Touching files in $$i" ; \
                (cd $$i ; touch *.c) ; \
        done

clean_all:
	-for i in $(SUBDIRS);\
        do\
                echo "Cleaning $$i" ; \
                (cd $$i ; rm *.o) ; \
        done

