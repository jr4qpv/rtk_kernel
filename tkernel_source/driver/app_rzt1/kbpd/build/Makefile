#
# ----------------------------------------------------------------------
#     T-Kernel 2.0 Software Package
#
#     Copyright 2011 by Ken Sakamura.
#     This software is distributed under the latest version of T-License 2.x.
# ----------------------------------------------------------------------
#
#     Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
#     Modified by T-Engine Forum at 2012/11/07.
#     Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
#
# ----------------------------------------------------------------------
#
#     Modified by T.Yokobayashi at 2016/03/14.
#
# ----------------------------------------------------------------------
#

#
#	Makefile
#		for GNU make
#
#	device driver : kbpd (RZT1)

MACHINE = rzt1
TETYPE = app

SRC_SYSDEP =

# ----------------------------------------------------------------------------

DEPS = Dependencies
DEPENDENCIES_OUTPUT := $(DEPS)

include $(BD)/etc/makerules

HEADER = $(BD)/include

# ----------------------------------------------------------------------------

TARGET = kbpd

S = ../src

VPATH = $(S)
HEADER += $(S)

SRC = main.c accept.c receive.c \
	statmach.c key.c pdbut.c \
	innevt.c pdsim.c devcmd.c etc.c
SRC += $(SRC_SYSDEP)

OBJ = $(addsuffix .o, $(basename $(SRC)))

CFLAGS += $(CFLAGS_WARNING)

# ----------------------------------------------------------------------------

.PHONY: all clean install clean_install

ALL = $(TARGET).o

all: $(ALL)

$(TARGET).o: $(OBJ)
	$(LINK_R.o) $^ $(OUTPUT_OPTION)

clean:
	$(RM) $(OBJ) $(ALL) $(DEPS)

install: $(addprefix $(DRIVER_INSTALLDIR)/, $(ALL))

clean_install:
	$(RM) $(addprefix $(DRIVER_INSTALLDIR)/, $(ALL))

ifdef DEPENDENCIES_OUTPUT
  $(DEPS): ; touch $(DEPS)
else
  $(DEPS): $(SRC) ; $(MAKEDEPS) $@ $?
endif
-include $(DEPS)


# ----------------------------------------------------------------------
#|History of "Makefile"
#|=====================
#|* 2016/03/14	../tef_em1d/から、 [app_rzt1]用にコピーし、
#|  MACHINE, TETYPE を修正。
#|
