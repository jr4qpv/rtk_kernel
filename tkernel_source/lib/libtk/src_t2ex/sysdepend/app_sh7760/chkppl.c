/*
 *----------------------------------------------------------------------
 *    T2EX Software Package
 *
 *    Copyright 2012 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2012/12/12.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/04.
 *
 *----------------------------------------------------------------------
 *
 *    Modified by T.Yokobayashi at 2016/01/05.
 *
 *----------------------------------------------------------------------
 */
/*
 * This software package is available for use, modification, 
 * and redistribution in accordance with the terms of the attached 
 * T-License 2.x.
 * If you want to redistribute the source code, you need to attach 
 * the T-License 2.x document.
 * There's no obligation to publish the content, and no obligation 
 * to disclose it to the TRON Forum if you have modified the 
 * software package.
 * You can also distribute the modified source code. In this case, 
 * please register the modification to T-Kernel traceability service.
 * People can know the history of modifications by the service, 
 * and can be sure that the version you have inherited some 
 * modification of a particular version or not.
 *
 *    http://trace.tron.org/tk/?lang=en
 *    http://trace.tron.org/tk/?lang=ja
 *
 * As per the provisions of the T-License 2.x, TRON Forum ensures that 
 * the portion of the software that is copyrighted by Ken Sakamura or 
 * the TRON Forum does not infringe the copyrights of a third party.
 * However, it does not make any warranty other than this.
 * DISCLAIMER: TRON Forum and Ken Sakamura shall not be held
 * responsible for any consequences or damages caused directly or
 * indirectly by the use of this software package.
 *
 * The source codes in bsd_source.tar.gz in this software package are 
 * derived from NetBSD or OpenBSD and not covered under T-License 2.x.
 * They need to be changed or redistributed according to the 
 * representation of each source header.
 */

/*
 *	@(#)chkppl.c (libtk/SH7760)
 *
 *	Check T2EX API Protection Level
 */

#include <tk/typedef.h>
#include <tk/errno.h>

IMPORT INT	t2ex_call_limit;

Inline INT PPL( void )
{
	UW	taskmode;
	Asm("stc r2_bank, %0": "=r"(taskmode));
	return (taskmode >> 16) & 3;
}

/*
 * Check protected level of extended SVC caller
 */
EXPORT ER ChkT2EXLevel( void )
{
	return ( PPL() > t2ex_call_limit )? E_OACV: E_OK;
}


/*----------------------------------------------------------------------*/
#if 0
#|【chkppl.c 変更履歴】
#|□2016/01/05	[app_sh7760]用に、[tef_em1d]の"chkppl.c"を参考に作成。
#|
#endif
