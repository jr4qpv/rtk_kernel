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
 *    Modified by T.Yokobayashi since 2016/03/14.
 *
 *----------------------------------------------------------------------
 */

/*
 *	@(#)kernel-ram.lnk (sysmain, RZT1) 2019/05/02
 *	linker script (RAM)
 */

OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

SECTIONS
{
/*	.text 0x00006000 : {	/* ATCM */
	.text 0x4040000 : {	/* INST-RAM */
/*	.text 0x4C020000 : {	/* SDRAM */
		KEEP (*(.init))
/*		*(.text)	/**/
		*(EXCLUDE_FILE (*tkernel.o ) .text)
		*(.text.*)
		*(.stub)
		KEEP (*(.fini))
		PROVIDE (__etext = .);
		PROVIDE (_etext = .);
		PROVIDE (etext = .);
		*(.rodata)
		*(.rodata.*)
		*(.rodata1)
		. = ALIGN(0x10);
	} =0

	.ARM.exidx ALIGN(4) :
	{
		__ARM_exidx_start = .;
		*(.ARM.exidx*)
		__ARM_exidx_end = .;
	}

	.data.org ALIGN(4) : {
		__data_org = .;			/* .data */
		. = . + (_edata - __data_start);
	}

	.atcm.org ALIGN(4) : {
		__atcm_org = .;			/* ATCM */
		. = . + (__atcm_end - __atcm_start);
	}

	.atcm_data.org ALIGN(4) : {
		__atcm_data_org = .;		/* ATCM */
		. = . + (__atcm_data_end - __atcm_data_start);
	}

	.data ALIGN(0x10) : AT(__data_org)
	{
		__data_start = . ;
/*		*(.data)	/**/
		*(EXCLUDE_FILE (*tkernel.o ) .data)
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
/*		*(.bss)		/**/
		*(EXCLUDE_FILE (*tkernel.o ) .bss)
		*(.bss.*)
		*(COMMON)
		. = ALIGN(4);
		_end = .;
		PROVIDE (end = .);
	}

	.atcm 0x00006000 : AT(__atcm_org)
	{
		__atcm_start = . ;
		*tkernel.o (.text)
		__atcm_end = .;
	}

	.atcm_data ALIGN(4) : AT(__atcm_data_org)
	{
		__atcm_data_start = . ;
		*tkernel.o (.data)
		__atcm_data_end = .;
	}

	.atcm_bss ALIGN(4) (NOLOAD) : {
		__atcm_bss_start = . ;
		*tkernel.o (.bss)
		__atcm_bss_end = .;
	}

}


/*----------------------------------------------------------------------
#|History of "kernel-ram.lds"
#|---------------------------
#|* 2016/03/14	../tef_em1d/から、 [app_rzt1]用にコピーし、修正。
#|* 2016/03/14	拡張子は｢.lnk｣→｢.lds｣に変更｡(Windowsでは｢.lnk｣は特殊ﾌｧｲﾙの為)
#|* 2016/03/16	KPIT GCCに対応の為、OUTPUT_FORMAT 指定を
#|  "elf32-larm-tkernel"→"elf32-littlearm",
#|  "elf32-barm-tkernel"→"elf32-bigarm" に変更
#|* 2016/06/06	RAM実行の時は、__data_org と __data_start は同じ値にする
#|* 2017/12/26	.data領域の初期値は.data.orgの別領域に割り当て
#|
*/
