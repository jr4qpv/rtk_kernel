/*
 *----------------------------------------------------------------------
 *
 *    T-Kernel Software Package
 *
 *----------------------------------------------------------------------
 */

/*
 *	@(#)pboot.S (RZT1) 2017/08/07
 *
 */

#include <machine.h>

//	.extern	Csym(start)
	.extern	_start



/*----------------------------------------------------------------------
       PBOOT(一次ブート)のロード／ディスク起動処理 (512Byte)
----------------------------------------------------------------------*/
/*
 *[Note]
 *・PBOOTルーチンは、
 *  どこのメモリに配置されても動くようリロケータブルにコーディングする事。
 */
#define	BOOTSIGNATURE_CODE	0xe382

	.section PBOOT, "ax"
	.arm
	.global	_pboot
_pboot:

/*
 * .textをコピー
 */
	ldr	r5, =__text_org		// Initialization of 'text' area 
	ldr	r6, =__text_start
	ldr	r7, =__text_end
	cmp	r6, r7
	bhs	nocopy_text
  copy_text:
	ldr	r4, [r5], #4
	str	r4, [r6], #4
	cmp	r6, r7
	blo	copy_text
  nocopy_text:

/*
 * キャッシュフラッシュ
 */
	dsb

	ldr	r4, =0
	mcr	p15, 0, r4, cr7, c5, 0	// Invalidate I-Cache(ICIALLU)

	mcr	p15, 0, r4, cr7, c5, 6	// (BPIALL)

	isb                         /* Ensuring Context-changing */

/*
 * 起動処理へ分岐
 */
//	ldr	r0, =Csym(start)
	ldr	r0, =_start
	bx	r0

	.pool

	.org	0x1fe
BootSignature:	.hword	BOOTSIGNATURE_CODE
pboot_end:

	
/*----------------------------------------------------------------------
#|History of "pboot.S"
#|=====================
#|* 2017/08/07	[app_rzt1]用に、新規作成。
#|
*/
