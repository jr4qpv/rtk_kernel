/*
 *----------------------------------------------------------------------
 *    T-Kernel 2.0 Software Package
 *
 *    Copyright 2011 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
 *    Modified by T-Engine Forum at 2013/03/11.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
 *
 *----------------------------------------------------------------------
 *
 *    Modified by T.Yokobayashi at 2016/03/01.
 *
 *----------------------------------------------------------------------
 */

/*
 *	kernel-ram.lnk (sysmain, EM1-D512)
 *	linker script (RAM)
 */

OUTPUT_FORMAT("elf32-larm-tkernel", "elf32-barm-tkernel", "elf32-larm-tkernel")
OUTPUT_ARCH(arm)
ENTRY(_start)

SECTIONS
{
	.text 0x30006000 : {
		KEEP (*(.init))
		*(.text)
		*(.text.*)
		*(.stub)
		*(.glue_7t)
		*(.glue_7)
		KEEP (*(.fini))
		PROVIDE (__etext = .);
		PROVIDE (_etext = .);
		PROVIDE (etext = .);
		*(.rodata)
		*(.rodata.*)
		*(.rodata1)
		. = ALIGN(0x1000);
	} /*:text*/ =0
	__data_org = . ;
	.data ALIGN(0x10) : {
		__data_start = . ;
		*(.data)
		*(.data.*)
		SORT(CONSTRUCTORS)
		*(.data1)
		KEEP (*(.eh_frame))
		*(.gcc_except_table)
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
		*(.sdata)
		*(.sdata.*)
		_edata = .;
		PROVIDE (edata = .);
	} /*:data*/
	.bss : {
		__bss_start = .;
		PROVIDE (__sbss_start = .);
		PROVIDE (___sbss_start = .);
		*(.sbss)
		*(.sbss.*)
		*(.scommon)
		PROVIDE (__sbss_end = .);
		PROVIDE (___sbss_end = .);
		*(.bss)
		*(.bss.*)
		*(COMMON)
		. = ALIGN(4);
		_end = .;
		PROVIDE (end = .);
	} /*:data*/
}


/*----------------------------------------------------------------------*/
/*
#|【kernel-ram.lds 変更履歴】
#|□2016/03/01	拡張子は｢.lnk｣→｢.lds｣に変更｡(Windowsでは｢.lnk｣は特殊ﾌｧｲﾙの為)
#|
 */
