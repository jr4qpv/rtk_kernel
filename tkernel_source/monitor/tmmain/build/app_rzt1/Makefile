#
# ----------------------------------------------------------------------
#     T-Kernel 2.0 Software Package
#
#     Copyright 2011 by Ken Sakamura.
#     This software is distributed under the latest version of T-License 2.x.
# ----------------------------------------------------------------------
#
#     Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
#     Modified by T-Engine Forum at 2011/09/08.
#     Modified by T-Engine Forum at 2012/11/07.
#     Modified by T-Engine Forum at 2013/03/01.
#     Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
#
# ----------------------------------------------------------------------
#
#     Modified by T.Yokobayashi at 2016/04/02.
#
# ----------------------------------------------------------------------
#

#	@(#)T-Monitor : tmmain (RZT1) 2019/09/20

MACHINE = rzt1
TETYPE = app

SRC_SYSDEP =

# ----------------------------------------------------------------------------

DEPS = Dependencies
DEPENDENCIES_OUTPUT := $(DEPS)

include $(BD)/etc/makerules
OPTSYS := $(BD)/OPT

# install directory
TMONITOR_INSTALLDIR = $(BD)/monitor/bin/$(TETYPE)_$(MACHINE)

# h/w depend module path
HWDEPEND_PATH = $(BD)/monitor/hwdepend/$(TETYPE)_$(MACHINE)/build

# command/svc module path
CMDSVC_PATH = $(BD)/monitor/cmdsvc/build/$(TETYPE)_$(MACHINE)

# each driver module path
DRV_SIO_PATH = $(BD)/monitor/driver/sio/build/$(TETYPE)_$(MACHINE)
DRV_FLASH_PATH = $(BD)/monitor/driver/flash/build/$(TETYPE)_$(MACHINE)
DRV_MEMDISK_PATH = $(BD)/monitor/driver/memdisk/build/$(TETYPE)_$(MACHINE)

# header paths 
HEADER = $(BD)/include $(OPTSYS)/include $(BD)/monitor/include

# ----------------------------------------------------------------------------

# version
VER := 2.01.00

# vsersion for T-Monitor
VER_TMON := 0.60

# RZ/T1 board name
ifeq ($(TYPE_RZT),1)
  BOARDNAME := SCPZ-1
endif
ifeq ($(TYPE_RZT),0)
  BOARDNAME := RSK-RZT1
endif

# T-Monitor boot message
define VERSION
char const Version[] = "$(VER)";
char const * const Title[5] = {
  "T-Monitor/$(TETYPE)_$(MACHINE) Version $(VER) for $(BOARDNAME) r$(VER_TMON)",
  0,
  "@(#)$(shell LC_TIME=C date)",
  "$(BOARDNAME)",
  "$(VER_TMON)"
};
endef

# ----------------------------------------------------------------------------

TARGET = tmonitor

S = ../../src

VPATH = $(S)
HEADER += $(S)

SRC = $(SRC_SYSDEP)

OBJ	= $(addsuffix .o, $(basename $(SRC)))

# compiler options
CFLAGS += $(CFLAGS_WARNING)
CPPFLAGS += -D__TMONITOR_BUILD__

# ----------------------------------------------------------------------------

M_OBJ =	$(TMONITOR_INSTALLDIR)/hwdepend.o \
	$(TMONITOR_INSTALLDIR)/cmdsvc.o \
	$(TMONITOR_INSTALLDIR)/wrkbuf.o \
	$(TMONITOR_INSTALLDIR)/sio.o \
	$(TMONITOR_INSTALLDIR)/flash.o \
	$(TMONITOR_INSTALLDIR)/memdisk.o

LDLIBS = -lgcc

LDFLAGS += -static -nostdlib -T ../$(TETYPE)_$(MACHINE)/$(LINKSCRIPT)

ifneq ($(filter ram, $(options)), )
  # RAM version, for debug purpose
  LINKSCRIPT = monitor-ram.lds
else
  LINKSCRIPT = monitor.lds
endif

# ----------------------------------------------------------------------------

.PHONY: all clean install

ALL = $(TARGET).mot $(TARGET).map

all: hwdepend cmdsvc drivers $(ALL) install

$(TARGET).mot:	$(TARGET)
	$(OBJCOPY) -O srec --srec-forceS3 --srec-len 32 $< $@

$(TARGET): $(M_OBJ) $(OBJ) ver_info.o
	$(CC) $(TARGET_ARCH) $(LDFLAGS) $^ $(LDLIBS) $(OUTPUT_OPTION)

ver_info.c: Makefile $(OBJ) $(M_OBJ)
	echo "$$VERSION" > ver_info.c

hwdepend:
	( cd $(HWDEPEND_PATH) ; $(MAKE) ; $(MAKE) install ; )

cmdsvc:
	( cd $(CMDSVC_PATH) ; $(MAKE) ; $(MAKE) install ; )

drivers:
	( cd $(DRV_SIO_PATH) ; $(MAKE) ; $(MAKE) install ; )
	( cd $(DRV_FLASH_PATH) ; $(MAKE) ; $(MAKE) install ; )
	( cd $(DRV_MEMDISK_PATH) ; $(MAKE) ; $(MAKE) install ; )

clean:
	( cd $(HWDEPEND_PATH) ; $(MAKE) clean )
	( cd $(CMDSVC_PATH) ; $(MAKE) clean )
	( cd $(DRV_SIO_PATH) ; $(MAKE) clean )
	( cd $(DRV_FLASH_PATH) ; $(MAKE) clean )
	( cd $(DRV_MEMDISK_PATH) ; $(MAKE) clean )
	$(RM) ver_info.[co] $(OBJ) $(M_OBJ) $(TARGET) $(ALL) $(DEPS)

install: $(addprefix $(EXE_INSTALLDIR)/, $(ALL))

ifdef DEPENDENCIES_OUTPUT
  $(DEPS): ; touch $(DEPS)
else
  $(DEPS): $(SRC) ; $(MAKEDEPS) $@ $?
endif
-include $(DEPS)

$(SRC.C):


# ----------------------------------------------------------------------
#|History of "Makefile"
#|---------------------
#|* 2016/03/14	../tef_em1d/から、 [app_rzt1]用にコピーし、
#|  MACHINE, TETYPE を修正。
#|* 2016/03/14	ﾘﾝｸｽｸﾘﾌﾟﾄの拡張子は｢.lnk｣→｢.lds｣に変更｡
#|  (Windowsでは｢.lnk｣は特殊ﾌｧｲﾙの為)
#|* 2016/04/02	ram時のTARGETﾌｧｲﾙ名に"-ram"を付加するようにした
#|* 2016/04/11	debugﾌｫﾙﾀﾞとmakefileとﾘﾝｸｽｸﾘﾌﾟﾄが共通にできるように、
#|  ﾘﾝｸｽｸﾘﾌﾟﾄに"../$(TETYPE)_$(MACHINE)/"のパス記述追加
#|* 2016/04/20	Title[0]にBOARDNAME文字列と、Title[3]にBOARDNAME文字列の追加
#|* 2017/04/10	バージョン情報のファイル名を ver_info に変更
#|* 2017/07/11	TYPE_RZT指定(0,1)でBOARDNAMEを変更するように対応
#|* 2018/04/06	「__TMONITOR_BUILD__」定義の追加
#|* 2019/09/20	VER_TMON=0.60に変更
#|
