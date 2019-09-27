/*
 *----------------------------------------------------------------------
 *    T-Kernel 2.0 Software Package
 *
 *    Copyright 2011 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
 *    Modified by T-Engine Forum at 2013/02/12.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
 *
 *----------------------------------------------------------------------
 *
 *    Modified by T.Yokobayashi since 2017/12/04.
 *
 *----------------------------------------------------------------------
 */

/*
 *	@(#)ssid.h (sys) 2018/11/14
 *
 *	Subsystem ID and subsystem priority
 *
 *	(NB) Included also from the assembler source,
 *	     so only macros can be described.
 */

#ifndef __SYS_SSID_H__
#define __SYS_SSID_H__

/*
 * T-Kernel (1 - 9)
 *	1 - 6 and 9 were previously used for other purposes.
 */
#define CONSIO_SVC	1		/* Console I/O */
#define CONSIO_PRI		1
#define	SERIAL_SVC	5		/* Low-level serial I/O */
#define	SERIAL_PRI		1
#define DEVICE_SVC	8		/* T-Kernel/SM device management */
#define DEVICE_PRI		4
#define SYSTEM_SVC	9		/* T-Kernel/SM system management */
#define SYSTEM_PRI		1

/*
 * Subsystem (10 - )
 */
#define MM_SVC		11		/* Memory management		*/
#define MM_PRI			2
#if 1	/* Modified by T.Yokobayashi */
#define DT_SVC		15		/* Calendar management		*/
#define DT_PRI			8
#endif
#define SM_SVC		16		/* System management		*/
#define SM_PRI			2
#define SEG_SVC		17		/* Segment management		*/
#define SEG_PRI			2
#define	H8IO_SVC	25		/* (T-Engine) H8 input/output	*/
#define	H8IO_PRI		8

#if 1	/* Modified by T.Yokobayashi */
/*
 * OPT extension Subsystem (31 - 38)
 */
#define SYSCALLSIO_SVC	31		/* Newlib Syscalls I/O */
#define SYSCALLSIO_PRI		2
#define OPTBIOS_SVC     32      /* OPT-System BIOS call   */
#define OPTBIOS_PRI         10
#define SCPZBIOS_SVC    33      /* SCPZ-Board BIOS call   */
#define SCPZBIOS_PRI        10
#define LBUFCONS_SVC    34      /* Ling Buffer Console call */
#define LBUFCONS_PRI        10
#endif


#endif /* __SYS_SSID_H__ */


/*----------------------------------------------------------------------
#|History of "ssid.h"
#|-------------------
#|* 2017/12/04	Add SYSCALLSIO_SVC,SYSCALLSIO_PRI define.
#|* 2018/04/20	Add OPTBIOS_SVC,OPTBIOS_PRI define.
#|* 2018/07/24	Add DT_SVC,DT_PRI define.
#|* 2018/07/19	Add SCPZBIOS_SVC,SCPZBIOS_PRI define.
#|* 2018/07/24	Add DT_SVC,DT_PRI define.
#|* 2018/10/09	Add LBUFCONS_SVC,LBUFCONS_PRI define.
#|
*/
