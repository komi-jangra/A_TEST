# Makefile for Cellh 

BASE_NAME = libdiagLibapi.so
MAKEFILE_NAME = Makefile.new
SYS_LIB_PATH = $(BSC_BASE)/Bin/Target/CommonLib/CP
# BIN_NAME is the name with which binary is to be installed and used.
BIN_NAME      = libdiagLibapi.so

all: compile install 

compile:
	make -f $(MAKEFILE_NAME) 

install:

clean:
	make -f $(MAKEFILE_NAME) clean

uninstall:
	rm -f $(SYS_LIB_PATH)/$(BIN_NAME)
