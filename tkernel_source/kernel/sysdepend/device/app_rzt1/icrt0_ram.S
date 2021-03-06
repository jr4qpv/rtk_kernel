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
 *    Modified by T.Yokobayashi at 2016/06/02.
 *
 *----------------------------------------------------------------------
 */

/*
 *	@(#)icrt0_ram.S (RZT1) 2018/08/24
 *	System Startup
 */

#include <machine.h>
#include <tk/asm.h>

#if _Csym == 0
#define	START	_start
#else
#define	START	start
#endif

	/* Low level memory manager information */
	.comm	Csym(lowmem_top), 4	// Head of area (Low address)
	.comm	Csym(lowmem_limit), 4	// End of area (High address)

	.lcomm	monitor_stacktop, 4	// Monitor stack pointer for re-startup

#define	SYSINFO		0x00800800	// System common information
#define	RAM_TOP		(SYSINFO + 0)	// Head of ext. RAM free area
#define	RAM_END		(SYSINFO + 4)	// End of ext. RAM free area
#define	SYSCONF		(SYSINFO + 8)	// SYSCONF top

	.text
	.balign	4
	.globl	START
	.type	START, %function
START:
	/* Use the stack set by the monitor */
	ldr	ip, =PSR_SVC|PSR_DI|PSR_F	// SVC mode/Interrupt disable
	msr	cpsr_xc, ip

	/* MMU is already ON. The initial setting is done.
	   Only cache should be ON */
	mrc	p15, 0, r4, cr1, c0		// SCTLR
	orr	r4, r4, #CR1_C
	orr	r4, r4, #CR1_I|CR1_Z
	mcr	p15, 0, r4, cr1, c0		// SCTLR
#ifdef	CPU_ARMv6
	ldr	r4, =0
	mcr	p15, 0, r4, cr7, c7, 0	// Cache flush, Invalidate I/D-Cache
#else	/* CPU_ARMv7以降 */
	ldr	r4, =0
	mcr	p15, 0, r4, cr7, c5, 0	// Invalidate I-Cache(ICIALLU)
	mcr	p15, 0, r4, cr7, c6, 1	// Invalidate D-Cache(DCIMVAC)
#endif
	dsb
	isb

/*
 * .atcmをコピー
 */
	ldr	r5, =__atcm_org		// Initialization of '.atcm' area 
	ldr	r6, =__atcm_start
	ldr	r7, =__atcm_end
	cmp	r6, r7
	bhs	nocopy_atcm
  copy_atcm:
	ldr	r4, [r5], #4
	str	r4, [r6], #4
	cmp	r6, r7
	blo	copy_atcm
  nocopy_atcm:

/*
 * キャッシュフラッシュ
 */
	dsb

	ldr	r4, =0
	mcr	p15, 0, r4, cr7, c5, 0	// Invalidate I-Cache(ICIALLU)

	mcr	p15, 0, r4, cr7, c5, 6	// (BPIALL)

	dsb
	isb                         /* Ensuring Context-changing */

/*
 * .atcm_dataをコピー
 */
	ldr	r5, =__atcm_data_org	// Initialization of 'atcm_data' area
	ldr	r6, =__atcm_data_start
	subs	r10, r5, r6		// If r10 != 0, start Rom
	beq	nocopy_atcm_data
	ldr	r7, =__atcm_data_end
	cmp	r6, r7
	bhs	nocopy_atcm_data
  copy_atcm_data:
	ldr	r4, [r5], #4
	str	r4, [r6], #4
	cmp	r6, r7
	blo	copy_atcm_data
  nocopy_atcm_data:

/*
 * .atcm_bssをクリア
 */
	ldr	r4, =0			// Clear 'atcm_bss' area
	ldr	r5, =__atcm_bss_start
	ldr	r6, =__atcm_bss_end
	cmp	r5, r6
	bhs	noatcmbss
  clratcmbss:
	str	r4, [r5], #4
	cmp	r5, r6
	blo	clratcmbss
  noatcmbss:

/*
 * .dataをコピー
 */
	ldr	r5, =__data_org		// Initialization of 'data' area (ROM startup)
	ldr	r6, =__data_start
	subs	r10, r5, r6		// If r10 != 0, start Rom
	beq	nocopy_data
	ldr	r7, =_edata
	cmp	r6, r7
	bhs	nocopy_data
  copy_data:
	ldr	r4, [r5], #4
	str	r4, [r6], #4
	cmp	r6, r7
	blo	copy_data
  nocopy_data:

	ldr	r4, =0			// Clear 'bss' area
	ldr	r5, =__bss_start
	ldr	r6, =_end
	cmp	r5, r6
	bhs	nobss
  clrbss:
	str	r4, [r5], #4
	cmp	r5, r6
	blo	clrbss
  nobss:

	ldr	ip, =monitor_stacktop	// Monitor stack pointer for re-startup
	str	sp, [ip]		// Save
	bic	sp, sp, #7		// align stack module 8 bytes

	ldr	ip, =RAM_TOP		// Low level memory manager initial setting
	ldr	r5, [ip]
	cmp	r6, r5			// _end or RAM_TOP
	movhi	r5, r6			// Either of High addresses
	ldr	ip, =lowmem_top
	str	r5, [ip]		// lowmem_top = _end or RAM_TOP
	ldr	ip, =RAM_END
	ldr	r5, [ip]
	ldr	ip, =lowmem_limit
	str	r5, [ip]		// lowmem_limit = RAM_END

	ldr	r4, =SYSCONF
	ldr	r5, [r4]
	cmp	r5, #0
	bleq	l1
	
	cmp	r10, #0
	bleq	l2

  l1:
	bl	Csym(ROM_startup)	// Initialization at ROM startup

  l2:
	bl	Csym(main)		// System startup

  l_end:				// Not suppose to return from 'main,'
	b	l_end			// but, just in case, prepare for out of control.


/*----------------------------------------------------------------------
#|History of "icrt0_ram.S"
#|------------------------
#|* 2016/07/19	[app_rzt1]用に、[tef_em1d]用の"ictr0_ram.S"を参考に作成。
#|* 2018/04/12	.atcmコピーの追加
#|* 2018/08/24	SYSINFOを、0x00800800 に変更
#|
*/
