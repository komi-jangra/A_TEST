include ${SCM_ROOT}/scm.mk

VERSION_SCM=${BASE}.${MAJOR}.${MINOR}
DBUTIL_LIB = ${SCM_ROOT}/../../Bin

DIRS= \
	Src

LIB_DIRS= \
        ${SCM_ROOT}/Lib

ifeq ($(BSC_FLAG),1)
DB_LIB= -lCLIB -ldbwrappers 
endif
ifeq ($(MSC_FLAG),1)
DB_LIB= -lCLIB
endif

all:	
	make clean
	for i in ${DIRS}; \
	do \
		(cd $$i; \
			echo $$i; \
			${MAKE} all \
		); \
	done
	# Anand Singh code addition BEGINS
	if test $a -eq 1; \
	then \
	$(CC) -g  -o ${SCM_ROOT}/Bin/SCM-${VERSION_SCM} ${SCM_ROOT}/Src/*.o  \
	-L${DBUTIL_LIB}/Host/CommonLib -lsksdb          \
	-L${SCM_ROOT}/Lib  -L${SYSEXE_ROOT}/Host/CommonLib/CP  \
	-lpthread -llog  -ltau -lfrm ${DB_LIB}\
	-L/usr/ccs/lib -lrt; \
	fi
	if test $a -eq 2; \
	then \
	$(CC) -g  -o ${SCM_ROOT}/Bin/SCM-${VERSION_SCM} ${SCM_ROOT}/Src/*.o  \
	-L${DBUTIL_LIB}/Host/CommonLib -lsksdb   \
	-L${SCM_ROOT}/Lib  -L${SYSEXE_ROOT}/Host/CommonLib/CP  \
	-lpthread -llog  ${DB_LIB} \
	-L/usr/ccs/lib -lrt; \
	fi
	if test $a -eq 0; \
	then \
	$(CC) -g  -o ${SCM_ROOT}/Bin/SCM-${VERSION_SCM} ${SCM_ROOT}/Src/*.o   \
	-L${DBUTIL_LIB}/Target/CommonLib -lsksdb        \
	-L${SCM_ROOT}/Lib -L${SYSEXE_ROOT}/Target/CommonLib/CP   \
	-lpthread -lplatformLib -llog -ltau -lfrm -lstdc++ ${DB_LIB} \
	-L/usr/ccs/lib -lrt; \
	fi
	# Anand Singh code addition ENDS
	for i in ${DIRS}; \
	do \
		(cd $$i; \
			echo $$i; \
			${MAKE} all \
		); \
	done


	echo 'Successfully made a Build....'

clean:
	for i in ${DIRS}; \
	do \
		(cd $$i; \
			echo $$i; \
			${MAKE} clean \
		); \
	done

	${RM} -rf ${SCM_ROOT}/Bin/*.* 
