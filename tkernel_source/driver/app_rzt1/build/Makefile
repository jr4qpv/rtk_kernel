#
# ----------------------------------------------------------------------
#     T-Kernel 2.0 Software Package
#
#     Copyright 2011 by Ken Sakamura.
#     This software is distributed under the latest version of T-License 2.x.
# ----------------------------------------------------------------------
#
#     Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
#     Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
#
# ----------------------------------------------------------------------
#
#     Modified by T.Yokobayashi at 2016/06/01.
#
# ----------------------------------------------------------------------
#

#
#	@(#)Makefile for gmake (driver) 2018/04/10
#	make all drivers for app_rzt1
#

# T-Engine type
MACHINE = rzt1
TETYPE = app

##DRV_TARGET = clk console kbpd lowkbpd screen sysdsk
DRV_TARGET = clk console
DRV_SRC_TARGET = clk console

# ----------------------------------------------------------------------------
.PHONY: all clean source clean_source clean_all

all: $(DRV_TARGET)

$(DRV_TARGET):
	cd ../$@/build ; \
	$(MAKE) ; \
	$(MAKE) install

clean:
	@( cd ../ ; \
	for dir in $(DRV_TARGET); do \
		( cd $$dir/build ; $(MAKE) clean clean_install ) ; \
	done ) ;

source:
	@( cd ../ ; \
	for dir in $(DRV_SRC_TARGET); do \
		( cd $$dir/build ; $(MAKE) source ) ; \
	done ) ;

clean_source:
	@( cd ../ ; \
	for dir in $(DRV_SRC_TARGET); do \
		( cd $$dir/build ; $(MAKE) clean_source ) ; \
	done ) ;

clean_all: clean clean_source


# ----------------------------------------------------------------------
#|History of "Makefile"
#|---------------------
#|* 2016/06/01	../../tef_em1d/から、 [app_rzt1]用にコピーし修正。
#|
