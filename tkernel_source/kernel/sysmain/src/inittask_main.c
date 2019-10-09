/*
 *----------------------------------------------------------------------
 *    T-Kernel 2.0 Software Package
 *
 *    Copyright 2011 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
 *    Modified by T-Engine Forum at 2013/02/28.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
 *
 *----------------------------------------------------------------------
 *
 *    Modified by T.Yokobayashi since 2016/09/08.
 *
 *----------------------------------------------------------------------
 */

/*
 *	@(#)inittask_main.c (sysmain) 2019/10/09
 *	Initial Task
 */

#include "sysmain.h"
#include "kernel.h"
#include <sys/rominfo.h>
#include <sys/debug.h>

typedef INT	(*MAIN_FP)(INT, UB **);

/* ------------------------------------------------------------------------ */

/*
 * Initial task Main
 *	The available stack size is slightly less than 8KB.
 *	The initial task is the system task,
 *	so it should not be deleted.
 */
EXPORT INT init_task_main( void )
{
	INT	fin;
	MAIN_FP	adr;

	/* Start message */
#if USE_KERNEL_MESSAGE
 #ifdef _TEF_EM1D_
	tm_putstring((UB*)BOOT_MESSAGE);
 #else	/* Modified by T.Yokobayashi */
extern const char * const TitleAPP[5];	/* Boot Messages */
	tm_printf("\n%s [%s]\n\n", TitleAPP[0], TitleAPP[2]);
 #endif
#endif

	fin = 1;
	adr = (MAIN_FP)ROMInfo->userinit;
#if 1	/* Modified by T.Yokobayashi */	
	while ( adr != NULL ) {
		W *p = (W*)adr;
		/* Check ApSignature & StartAddress */
		if ((p[1] == 0x12345678) && (p[2] == (W)p)) {
			/* Check ApType code */
			if (p[3] == 0) {
				/* Perform user defined initialization sequence */
				fin = (*adr)(0, NULL);
				break;
			}
			else if (p[3] == 1) {
				/* Perform user defined program in usermain() */
				tm_printf((UB*)"Userinit(%#x) executes in usermain mode.\n", (int)p);
				break;
			}
			else {
				/* ApType code error */	;
			}
		}

		tm_printf((UB*)"Userinit(%#x) code not found.\n", (int)p);
  #if 0	/* for debug */
		extern void    *lowmem_top, *lowmem_limit;
		tm_printf("lowmem_top=%#x, lowmem_limit=%#x\n",
				  (int)lowmem_top, (int)lowmem_limit);
  #endif
		tk_dly_tsk(200);
		tm_monitor();
	}
#else	/* Original code */
	if ( adr != NULL ) {
		/* Perform user defined initialization sequence */
		fin = (*adr)(0, NULL);
	}
#endif
	if ( fin > 0 ) {
		/* Perform user main */
		fin = usermain();
	}
	if ( adr != NULL ) {
		/* Perform user defined finalization sequence */
		(*adr)(-1, NULL);
	}

	return fin;
}


/*----------------------------------------------------------------------
#|History of "inittask_main.c"
#|----------------------------
#|* 2016/09/08	The string of TitleAPP[0] is displayed at startup.
#|* 2019/05/02	Added Check ApSignature & StartAddress.
#|* 2019/10/09	Added Check ApType code.
#|
*/
