# makefile for System: System_CCUH

sctAUTOCFGDEP =
sctCOMPFLAGS = -DXUSE_GENERIC_FUNC

include $(sctdir)/makeoptions

default: System_CCUH$(sctEXTENSION)

System_CCUH$(sctEXTENSION): \
  System_CCUH$(sctOEXTENSION) \
  U2ctypes$(sctOEXTENSION) \
  U2ExtraOps$(sctOEXTENSION) \
  CCUH$(sctOEXTENSION) \
  SYSInclude$(sctOEXTENSION) \
  Interface$(sctOEXTENSION) \
  OamInclude$(sctOEXTENSION) \
  CCUInclude$(sctOEXTENSION) \
  DBInclude$(sctOEXTENSION) \
  $(sctLINKKERNELDEP)
	$(sctLD)  System_CCUH$(sctOEXTENSION) U2ctypes$(sctOEXTENSION) U2ExtraOps$(sctOEXTENSION) CCUH$(sctOEXTENSION) SYSInclude$(sctOEXTENSION) Interface$(sctOEXTENSION) OamInclude$(sctOEXTENSION) CCUInclude$(sctOEXTENSION) DBInclude$(sctOEXTENSION) $(sctLINKKERNEL)  $(sctLDFLAGS) -o System_CCUH$(sctEXTENSION)

System_CCUH$(sctOEXTENSION): \
  System_CCUH.c \
  U2ctypes.h \
  U2ExtraOps.h \
  SYSInclude.h \
  Interface.h \
  CCUInclude.h \
  OamInclude.h \
  DBInclude.h \
  U2ctypes.h \
  U2ExtraOps.h \
  CCUH.h \
  U2ctypes.h \
  U2ExtraOps.h \
  SYSInclude.h \
  SYSInclude.h \
  U2ctypes.h \
  U2ExtraOps.h \
  Interface.h \
  SYSInclude.h \
  DBInclude.h \
  U2ctypes.h \
  U2ExtraOps.h \
  OamInclude.h \
  OamInclude.h \
  SYSInclude.h \
  DBInclude.h \
  U2ctypes.h \
  U2ExtraOps.h \
  CCUInclude.h \
  SYSInclude.h \
  U2ctypes.h \
  U2ExtraOps.h \
  DBInclude.h \
  CCUH.h \
  SYSInclude.h \
  Interface.h \
  CCUInclude.h \
  OamInclude.h \
  DBInclude.h \
  U2ctypes.h \
  U2ExtraOps.h
	$(sctCC) $(sctCPPFLAGS) $(sctCCFLAGS) $(sctIFDEF) System_CCUH.c -o System_CCUH$(sctOEXTENSION)

U2ctypes$(sctOEXTENSION): \
  U2ctypes.c \
  U2ctypes.h
	$(sctCC) $(sctCPPFLAGS) $(sctCCFLAGS) $(sctIFDEF) U2ctypes.c -o U2ctypes$(sctOEXTENSION)

U2ExtraOps$(sctOEXTENSION): \
  U2ExtraOps.c \
  U2ExtraOps.h
	$(sctCC) $(sctCPPFLAGS) $(sctCCFLAGS) $(sctIFDEF) U2ExtraOps.c -o U2ExtraOps$(sctOEXTENSION)

CCUH$(sctOEXTENSION): \
  CCUH.c \
  CCUH.h
	$(sctCC) $(sctCPPFLAGS) $(sctCCFLAGS) $(sctIFDEF) CCUH.c -o CCUH$(sctOEXTENSION)

SYSInclude$(sctOEXTENSION): \
  SYSInclude.c \
  SYSInclude.h
	$(sctCC) $(sctCPPFLAGS) $(sctCCFLAGS) $(sctIFDEF) SYSInclude.c -o SYSInclude$(sctOEXTENSION)

Interface$(sctOEXTENSION): \
  Interface.c \
  Interface.h
	$(sctCC) $(sctCPPFLAGS) $(sctCCFLAGS) $(sctIFDEF) Interface.c -o Interface$(sctOEXTENSION)

OamInclude$(sctOEXTENSION): \
  OamInclude.c \
  OamInclude.h
	$(sctCC) $(sctCPPFLAGS) $(sctCCFLAGS) $(sctIFDEF) OamInclude.c -o OamInclude$(sctOEXTENSION)

CCUInclude$(sctOEXTENSION): \
  CCUInclude.c \
  CCUInclude.h
	$(sctCC) $(sctCPPFLAGS) $(sctCCFLAGS) $(sctIFDEF) CCUInclude.c -o CCUInclude$(sctOEXTENSION)

DBInclude$(sctOEXTENSION): \
  DBInclude.c \
  DBInclude.h
	$(sctCC) $(sctCPPFLAGS) $(sctCCFLAGS) $(sctIFDEF) DBInclude.c -o DBInclude$(sctOEXTENSION)

clean: clean_gen_objs clean_kernel_objs

clean_gen_objs:
	$(sctRM) \
  System_CCUH$(sctOEXTENSION) \
  U2ctypes$(sctOEXTENSION) \
  U2ExtraOps$(sctOEXTENSION) \
  CCUH$(sctOEXTENSION) \
  SYSInclude$(sctOEXTENSION) \
  Interface$(sctOEXTENSION) \
  OamInclude$(sctOEXTENSION) \
  CCUInclude$(sctOEXTENSION) \
  DBInclude$(sctOEXTENSION) \
  System_CCUH$(sctEXTENSION)
