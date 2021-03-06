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
#     Modified by T-Engine Forum at 2013/02/20.
#     Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
#
# ----------------------------------------------------------------------
#
#     Modified by T.Yokobayashi at 2016/03/14.
#
# ----------------------------------------------------------------------
#

#     @(#)T-Monitor : flash (rzt1) 2018/04/06

MACHINE = rzt1
TETYPE = app

SRC_SYSDEP    = setup-rzt1.c

SRC_WR_SYSDEP = reset-rzt1.c spi_mx25.c cfi.c \
	r_serial_flash_api.c r_serial_flash_ioset_api.c \
	serial_flash_ioset_drv.c serial_flash_ioset_userdef.c \
	serial_flash_userdef.c \
	r_main_convert.c

###SRC_SYSDEP    = setup-em1d.c
###SRC_WR_SYSDEP = reset-em1d.c cfi_16x1.c cfi.c



# ----------------------------------------------------------------------------

DEPS = Dependencies
DEPENDENCIES_OUTPUT := $(DEPS)

include $(BD)/etc/makerules

TMONITOR_INSTALLDIR = $(BD)/monitor/bin/$(TETYPE)_$(MACHINE)

HEADER = $(BD)/include $(BD)/OPT/include $(BD)/monitor/include

# ----------------------------------------------------------------------------

TARGET = flash

S = ../../src

VPATH = $(S) $(S)/rzt1
VPATH += $(BD)/OPT/lib/librzt/src/drv/serial_flash/src
VPATH += $(BD)/OPT/lib/librzt/src/drv/serial_flash
HEADER += $(S)
HEADER += $(BD)/OPT/include/renesas/rzt1
HEADER += $(BD)/OPT/lib/librzt/src/drv/serial_flash/inc

SRC     = main.c
SRC    += $(SRC_SYSDEP)
SRC_WR  =
SRC_WR += $(SRC_WR_SYSDEP)

OBJ    = $(addsuffix .o, $(basename $(SRC)))
OBJ_WR = $(addsuffix .o, $(basename $(SRC_WR)))

# compiler options
CFLAGS += $(CFLAGS_WARNING)
CFLAGS += -D__TMONITOR_BUILD__

# adjust for flashwr object
REN_SECTION =	--rename-section .text=flashwr.text \
		--rename-section .rodata=flashwr.rodata
KEEP_SYMBOL =	--keep-global-symbol=flashwr \
		--keep-global-symbol=FROM_SECSZ

# ----------------------------------------------------------------------------

.PHONY: all clean install

ALL = $(TARGET).o

all: $(ALL)

$(TARGET).o: $(OBJ) flashwr.o
	$(LINK_R.o) $^ $(OUTPUT_OPTION)

flashwr.o: $(OBJ_WR)
	$(LINK_R.o) $^ -lgcc $(OUTPUT_OPTION)
	$(OBJCOPY) $(REN_SECTION) $(KEEP_SYMBOL) $@

clean:
	$(RM) $(OBJ) $(OBJ_WR) flashwr.o $(ALL) $(DEPS)

install: $(addprefix $(TMONITOR_INSTALLDIR)/, $(ALL))

$(TMONITOR_INSTALLDIR)/%: %
	$(BD)/etc/backup_copy -t -d !OLD $< $(TMONITOR_INSTALLDIR)

ifdef DEPENDENCIES_OUTPUT
  $(DEPS): ; touch $(DEPS)
else
  $(DEPS): $(SRC) ; $(MAKEDEPS) $@ $?
endif
-include $(DEPS)


# ----------------------------------------------------------------------
#|History of "Makefile"
#|---------------------
#|* 2016/03/14	../tef_em1d/から、 [app_rzt1]用にコピーし、
#|  MACHINE, TETYPE を修正。
#|* 2016/04/21	Renesas RZ/T1のsflashｻﾝﾌﾟﾙｺｰﾄﾞ SRC_COMMON /serial_flash 関係
#|  を追加
#|* 2018/04/06	「__TMONITOR_BUILD__」定義の追加
#|
