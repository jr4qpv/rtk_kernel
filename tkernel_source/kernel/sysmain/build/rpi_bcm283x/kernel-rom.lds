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
 *    Modified by T.Yokobayashi since 2016/03/01.
 *
 *----------------------------------------------------------------------
 */

/*
 *      @(#)kernel-rom.lnk (sysmain, BCM283x) 2019/05/02
 *	linker script (ROM)
 */

OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
/* ENTRY(_start) */

SECTIONS
{
	__rom_start = 0x00030000;

	.pboot __rom_start : AT (__rom_start)
	{
		KEEP(pboot.o(PBOOT))
	}

	.rom_contents __rom_start + 0x200 : AT (__rom_start + 0x200)
	{
		__text_org = .;			/* .text */
		. = . + (__text_end - __text_start);
		__ARM_exidx_org = .;		/* .ARM.exidx */
		. = . + (__ARM_exidx_end - __ARM_exidx_start);
		__data_org = .;			/* .data */
		. = . + (_edata - __data_start);
	}

	__rom_bottom = .;

	.text 0x10006000 : AT (__text_org)	/* SDRAM */
	{
		__text_start = .;
		KEEP (*(.init))
		*(.text)
		*(.text.*)
		KEEP (*(.fini))
		PROVIDE (__etext = .);
		PROVIDE (_etext = .);
		PROVIDE (etext = .);
		*(.rodata)
		*(.rodata.*)
		*(.rodata1)
		. = ALIGN(0x10);
		__text_end = .;
	} =0

	.ARM.exidx : AT (__ARM_exidx_org)
	{
		__ARM_exidx_start = .;
		*(.ARM.exidx*)
		__ARM_exidx_end = .;
	}

	.data ALIGN(0x10) : AT(__data_org)
	{
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
		*(.sdata)
		*(.sdata.*)
		. = ALIGN(4);
		_edata = .;
		PROVIDE (edata = .);
	}

	.bss ALIGN(4) (NOLOAD) : {
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
	}

}


/*----------------------------------------------------------------------
#|History of "kernel-rom.lds"
#|---------------------------
#|* 2016/03/01	../tef_em1d/から、 [rpi_bcm283x]用にコピーし、修正。
#|* 2016/03/01	拡張子は｢.lnk｣→｢.lds｣に変更｡(Windowsでは｢.lnk｣は特殊ﾌｧｲﾙの為)
#|* 2016/03/16	KPIT GCCに対応の為、OUTPUT_FORMAT 指定を
#|  "elf32-larm-tkernel"→"elf32-littlearm",
#|  "elf32-barm-tkernel"→"elf32-bigarm" に変更
#|* 2016/03/16	.ARM.exidx ｾｸｼｮﾝの定義追加
#|* 2016/08/18	text領域を0x00030000番地からに割り当て
#|
*/
