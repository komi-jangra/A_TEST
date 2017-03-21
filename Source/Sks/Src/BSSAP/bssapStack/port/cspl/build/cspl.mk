ifndef PORT
	PORT = simple
endif

ifndef DRIVER
	DRIVER = simple
endif

CSPL_INCLUDES = -I$(ROOTDIR)../h 

ifdef	PORTDIR
	include $(PORTDIR)os.mk
	CSPL_INCLUDES += -I$(PORTDIR)
else
	include $(ROOTDIR)../ports/$(PORT)/os.mk
	CSPL_INCLUDES += -I$(ROOTDIR)../ports/$(PORT) -I$(ROOTDIR)../drivers/$(DRIVER)
endif

ifdef CONFIG
	include $(CONFIG)
endif
