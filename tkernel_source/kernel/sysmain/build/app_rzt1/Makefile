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
#     Modified by T-Engine Forum at 2014/07/31.
#     Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
#
# ----------------------------------------------------------------------
#
#     Modified by T.Yokobayashi since 2016/03/14.
#
# ----------------------------------------------------------------------
#

#
#	@(#)Makefile for gmake (RZT1) 2019/10/10
#	sysmain (system-dependent description)
#

# T-Engine type
MACHINE = rzt1
TETYPE	= app

# ----------------------------------------------------------------------------
# T-Kernel for RZT1 version
APP_VER = 0.60

# ----------------------------------------------------------------------------
# default rules
include ../../../../etc/makerules

# ----------------------------------------------------------------------------
# rpi board name
BOARDNAME := RZ/T1

# ----------------------------------------------------------------------------
# user source files (system-dependent)
SRC	= usermain.c appl_main.c sample_command.c

# userinit execute mode in usermain
CFLAGS += -D_USERINIT_IN_USERMAIN_

# include debug sample code in usermain.c
##CFLAGS += -DDEBUG_SAMPLE
CFLAGS += -D_APPL_SAMPLE_

# user-level libraries
LDUSRLIBS =

# ----------------------------------------------------------------------------
# device driver definitions
DRV_CONSOLE = yes
#DRV_CLOCK   = yes
###DRV_SYSDISK = yes
###DRV_SCREEN  = yes
###DRV_KBPD    = yes
###DRV_LOWKBPD = yes

OBJ_DRIVER = ../../../../driver/$(TETYPE)_$(MACHINE)/build
ifdef DRV_CONSOLE
  I_OBJ += $(OBJ_DRIVER)/console.o
  CFLAGS += -DDRV_CONSOLE
  LDUSRLIBS += -lconsolesvc
endif
ifdef DRV_CLOCK
  I_OBJ += $(OBJ_DRIVER)/clkdrv.o
  CFLAGS += -DDRV_CLOCK
  LDUSRLIBS += -lem1diic
endif
ifdef DRV_SYSDISK
  I_OBJ += $(OBJ_DRIVER)/sysdsk.o
  CFLAGS += -DDRV_SYSDISK
endif
ifdef	DRV_SCREEN
  I_OBJ += $(OBJ_DRIVER)/screen.o
  CFLAGS += -DDRV_SCREEN
endif
ifdef	DRV_KBPD
  I_OBJ += $(OBJ_DRIVER)/kbpd.o
  CFLAGS += -DDRV_KBPD
endif
ifdef	DRV_LOWKBPD
  I_OBJ += $(OBJ_DRIVER)/lowkbpd.o
  CFLAGS += -DDRV_LOWKBPD
endif

# ----------------------------------------------------------------------------
# additional libraries
LDUSRLIBS += -ldrvif -lstr

# ----------------------------------------------------------------------------
# include main makefile (common description)
include ../Makefile.common


# ----------------------------------------------------------------------
#|History of "Makefile"
#|---------------------
#|* 2016/03/14	../tef_em1d/から、 [app_rzt1]用にコピーし、
#|  MACHINE, TETYPE を修正。
#|* 2017/09/05	APP_VER=0.11の追加
#|* 2019/09/29	APP_VER=0.60に変更
#|* 2019/10/08	DRV_CONSOLEを有効にした
#|* 2019/10/10	サンプルアプリを追加した
#|
