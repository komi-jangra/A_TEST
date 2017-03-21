
include ${SCM_ROOT}/scm.mk


OBJS= \
	scm_encaps.o    scm_init.o      scm_nw.o    \
	scm_alarms.o    scm_misc_func.o scm_linkhashtable.o\
	scm_cmd_hadler.o scm_util.o   scm_linksethashtable.o\
	scm_stk.o       scm_db.o     scm_timer.o

all: ${OBJS}

.c.o:
	$(CC) ${DEFINES} ${CFLAGS} ${INCLUDES} -c $<
clean:
	${RM} ${OBJS}

