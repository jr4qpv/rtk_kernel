/*
 *----------------------------------------------------------------------
 *    T-Kernel 2.0 Software Package
 *
 *    Copyright 2011 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
 *
 *----------------------------------------------------------------------
 */

/*
 *	T-Kernel SVC interface library (sh7760)
 *
 *	   (generated automatically)
 */

#include <machine.h>
#include <tk/sysdef.h>
#include <sys/svc/tkfncd.h>

	.text
	.balign	2
	.globl	Csym(tk_sta_alm)
	.type	Csym(tk_sta_alm), @function
Csym(tk_sta_alm):
	mov.l	fno, r0
	trapa	#TRAP_SVC
	rts
	nop

	.balign	4
fno:	.long	TFN_STA_ALM

