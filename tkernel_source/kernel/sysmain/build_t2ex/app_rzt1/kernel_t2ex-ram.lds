/*
 *----------------------------------------------------------------------
 *    T2EX Software Package
 *
 *    Copyright 2012 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2012/12/12.
 *    Modified by T-Engine Forum at 2013/03/04.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/04.
 *
 *----------------------------------------------------------------------
 *
 *    Modified by T.Yokobayashi at 2016/03/14.
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
 *	@(#)kernel_t2ex-ram.lnk (sysmain, RZT1) 2016/03/16
 *	linker script (RAM, with T2EX memory protection)
 */

/* OUTPUT_FORMAT("elf32-larm-tkernel", "elf32-barm-tkernel", "elf32-larm-tkernel") */
OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

SECTIONS
{
	.text 0x00006000 : {
		/* System Level (Executable) */
		PROVIDE (__stext = .);
		PROVIDE (_stext = .);
		PROVIDE (stext = .);
		KEEP (*(.init))
		*(EXCLUDE_FILE (*.uo) .text)
		*(EXCLUDE_FILE (*.uo) .text.*)
		*(EXCLUDE_FILE (*.uo) .stub)
		*(.text)
		*(.text.*)
		*(.stub)
		*(.glue_7t)
		*(.glue_7)
		KEEP (*(.fini))
		PROVIDE (__etext = .);
		PROVIDE (_etext = .);
		PROVIDE (etext = .);
		. = ALIGN(4);
		/* System Level (Read-Only Data) */
		PROVIDE (__srodata = .);
		PROVIDE (_srodata = .);
		PROVIDE (srodata = .);
		*(EXCLUDE_FILE (*.uo) .rodata)
		*(EXCLUDE_FILE (*.uo) .rodata.*)
		*(EXCLUDE_FILE (*.uo) .rodata1)
		PROVIDE (__erodata = .);
		PROVIDE (_erodata = .);
		PROVIDE (erodata = .);
		. = ALIGN(4);
		/* User Level (Executable) */
		PROVIDE (__stext_usr = .);
		PROVIDE (_stext_usr = .);
		PROVIDE (stext_usr = .);
		*.uo(.text)
		*.uo(.text.*)
		*.uo(.stub)
		PROVIDE (__etext_usr = .);
		PROVIDE (_etext_usr = .);
		PROVIDE (etext_usr = .);
		. = ALIGN(4);
		/* User Level (Read-Only Data) */
		PROVIDE (__srodata_usr = .);
		PROVIDE (_srodata_usr = .);
		PROVIDE (srodata_usr = .);
		*.uo(.rodata)
		*.uo(.rodata.*)
		*.uo(.rodata1)
		PROVIDE (__erodata_usr = .);
		PROVIDE (_erodata_usr = .);
		PROVIDE (erodata_usr = .);
		. = ALIGN(0x10);
	} /*:text*/ =0

	.data ALIGN(0x10) : {
		__data_org = . ;
		__data_start = . ;
		*(EXCLUDE_FILE (*.uo) .data)
		*(EXCLUDE_FILE (*.uo) .data.*)
		SORT(CONSTRUCTORS)
		*(EXCLUDE_FILE (*.uo) .data1)
		KEEP (*(EXCLUDE_FILE (*.uo) .eh_frame))
		*(EXCLUDE_FILE (*.uo) .gcc_except_table)
		KEEP (*crtbegin.o(.ctors))
		KEEP (*(EXCLUDE_FILE (*crtend.o ) .ctors))
		KEEP (*(SORT(.ctors.*)))
		KEEP (*(.ctors))
		KEEP (*crtbegin.o(.dtors))
		KEEP (*(EXCLUDE_FILE (*crtend.o ) .dtors))
		KEEP (*(SORT(.dtors.*)))
		KEEP (*(.dtors))
		*(.got.plt)
		*(.got)
		*(EXCLUDE_FILE (*.uo) .sdata)
		*(EXCLUDE_FILE (*.uo) .sdata.*)
		_edata = .;
		PROVIDE (edata = .);
	} /*:data*/

	.bss ALIGN(4) : {
		__bss_start = .;
		PROVIDE (__sbss_start = .);
		PROVIDE (___sbss_start = .);
		*(EXCLUDE_FILE (*.uo) .sbss)
		*(EXCLUDE_FILE (*.uo) .sbss.*)
		*(EXCLUDE_FILE (*.uo) .scommon)
		PROVIDE (__sbss_end = .);
		PROVIDE (___sbss_end = .);
		*(EXCLUDE_FILE (*.uo) .bss)
		*(EXCLUDE_FILE (*.uo) .bss.*)
		*(EXCLUDE_FILE (*.uo) COMMON)
		. = ALIGN(4);
		_end = .;
		PROVIDE (end = .);
		. = ALIGN(0x1000);
	} /*:bss*/
	__data_usr_org = . ;
	.data_usr ALIGN(0x10) : {
		__data_usr_start = . ;
		*.uo(.data)
		*.uo(.data.*)
		*.uo(.data1)
		KEEP (*.uo(.eh_frame))
		*.uo(.gcc_except_table)
		*.uo(.sdata)
		*.uo(.sdata.*)
		. = ALIGN(4);
		_edata_usr = .;
		PROVIDE (edata_usr = .);
	} /*:data_usr*/
	.bss_usr : {
		__bss_usr_start = .;
		PROVIDE (__sbss_usr_start = .);
		PROVIDE (___sbss_usr_start = .);
		*.uo(.sbss)
		*.uo(.sbss.*)
		*.uo(.scommon)
		PROVIDE (__sbss_usr_end = .);
		PROVIDE (___sbss_usr_end = .);
		*.uo(.bss)
		*.uo(.bss.*)
		*.uo(COMMON)
		. = ALIGN(4);
		_end_usr = .;
		PROVIDE (end_usr = .);
	} /*:bss_usr*/
}


/*----------------------------------------------------------------------
#|History of "kernel_t2ex-ram.lds"
#|================================
#|* 2016/03/14	../tef_em1d/から、 [app_rzt1]用にコピーし、修正。
#|* 2016/03/14	拡張子は｢.lnk｣→｢.lds｣に変更｡(Windowsでは｢.lnk｣は特殊ﾌｧｲﾙの為)
#|* 2016/03/16	KPIT GCCに対応の為、OUTPUT_FORMAT 指定を
#|  "elf32-larm-tkernel"→"elf32-littlearm",
#|  "elf32-barm-tkernel"→"elf32-bigarm" に変更
#|* 2016/07/07	RAM実行の時は、__data_org と __data_start は同じ値にする
#|
 */
