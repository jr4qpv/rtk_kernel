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
 *	T-Kernel driver SVC interface library
 *
 *	   (generated automatically)
 */

#include <machine.h>
#include <tk/sysdef.h>
#include "fnserialio.h"

	.text
	.balign	2
	.globl	Csym(serial_ctl)
	.type	Csym(serial_ctl), @function
Csym(serial_ctl):
	mov.l	r7, @-r15
	mov.l	r6, @-r15
	mov.l	r5, @-r15
	mov.l	r4, @-r15
	mov.l	fno, r0
	mov	r15, r4
	trapa	#TRAP_SVC
	rts
	add	#4*4, r15

	.balign	4
fno:	.long	SERIAL_SERIAL_CTL_FN

