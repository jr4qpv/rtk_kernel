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
 *
 *    Modified by T.Yokobayashi at 2016/04/21.
 *
 *----------------------------------------------------------------------
 */

/*
 *	@(#)reset.c () 2017/08/07
 *
 *       Reset and reboot after Flash ROM write
 */

#include "flash.h"
#include <tk/sysdef.h>
#include <iodefine.h>

IMPORT void _start( void );	/* start address after reset */

/*
 * reset and reboot
 */
EXPORT void flashwr_reset( void )
{
#if 1
	/* プロテクションレジスタの解除（マニュアル11.2.1） */
	SYSTEM.PRCR.LONG = 0x0000A502;		/* ﾘｾｯﾄ関連 PRC1=1 */
	
	/* ソフトウェアリセット（マニュアル6.2.2） */
	SYSTEM.SWRR1.LONG = 0x4321A501;		/* ｿﾌﾄｳｪｱﾘｾｯﾄ */

	while (1) {
		;
	}
#else
#define	PAGETBL_BASE	(_UW *)0x30000000

	void (* volatile reset_p)( void ) = 0;

        /* Remap the NOR FlashROM area to its original space, and jump */
	*PAGETBL_BASE = 0x9402;	// Strongly-order, Kernel/RO
	DSB();
	Asm("mcr p15, 0, %0, cr8, cr7, 0":: "r"(0));	// I/D TLB invalidate
	Asm("mcr p15, 0, %0, cr7, cr5, 6":: "r"(0));	// invalidate BTC
	DSB();
	ISB();
	(*reset_p)();		/* call reset entry (does not return) */
#endif
}


/*----------------------------------------------------------------------
#|History of "reset-rzt1.c"
#|=========================
#|* 2016/04/21	It's copied from "setup-em1d.c" and it's modified.
#|* 2017/08/07	RZ/T1ではﾏﾆｭｱﾙﾘｾｯﾄﾚｼﾞｽﾀでﾘｾｯﾄ実行するようにした。
#|
*/
