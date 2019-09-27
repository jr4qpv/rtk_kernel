/*
 *----------------------------------------------------------------------
 *    T-Kernel 2.0 Software Package
 *
 *    Copyright 2011 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
 *    Modified by T-Engine Forum at 2013/03/01.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
 *
 *----------------------------------------------------------------------
 *
 *    Modified by T.Yokobayashi at 2016/07/12.
 *
 *----------------------------------------------------------------------
 */

/*
 *	@(#)portdef.h	(Console/Low-level serial I/O driver) 2018/11/15
 *
 *	Serial line low-level driver system-dependent port definition(RZT1)
 */

#include <renesas/rzt1/icu_vec.h>		/* for ICU_VEC_??? */

/* Port definition */
IMPORT	SC_FUNC	ScFuncSCIFA;

#define	N_PORTS		1

#define IV_BRIF2	IV_IRQ(ICU_VEC_BRIF2)	/* SCIFA Unit2 */
#define IV_RXIF2	IV_IRQ(ICU_VEC_RXIF2)	/* SCIFA Unit2 */
#define IV_TXIF2	IV_IRQ(ICU_VEC_TXIF2)	/* SCIFA Unit2 */
#define IV_DRIF2	IV_IRQ(ICU_VEC_DRIF2)	/* SCIFA Unit2 */


LOCAL  SC_DEFS	PortDefs[N_PORTS] = {
	/* Port #0: SCIFA2 */
	{
		&ScFuncSCIFA,
		{	0xa0065800,			/* SCIFA2 I/O base address */
			8,					/* iostep(SCIFAでは、ハード割り込みレベル) */
			IV_BRIF2			/* BRIF2 Interrupt Vector */
		},
		0,						/* fctl register value */
		{0, 0, 0},				/* dt[3]: Not used */
#if 1
		{0, 3, 0, 0, 115200},	/* default mode */
		{0, 0, 1, 1, 0, 0, 0},	/* default flow control */
#else
		{1, 3, 0, 0, 115200},	/* TERM標準 mode(odd,8bit,stop-1)  */
//		{1, 3, 0, 0, 38400},	/* TERM標準 mode(odd,8bit,stop-1)  */
		{0, 0, 0, 0, 0, 1, 1},	/* default flow control(XON/OFF control) */
#endif
		{0, 0, 0},				/* default flow status */
	}
};

#define	INIT_AUXPORT(sup)		/* Nothing */
#define	START_AUXPORT(sup)		/* Nothing */


/*----------------------------------------------------------------------
#|History of "portdef.c"
#|----------------------
#|* 2016/07/12	[app_rzt1]用に、[tef_em1d]の"portdef.h"を参考に作成。
#|
*/
