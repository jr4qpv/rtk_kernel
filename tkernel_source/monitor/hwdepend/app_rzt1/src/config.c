/*
 *----------------------------------------------------------------------
 *    T-Kernel 2.0 Software Package
 *
 *    Copyright(c) 2011 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
 *    Modified by T-Engine Forum at 2011/09/08.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
 *
 *----------------------------------------------------------------------
 *
 *    Modified by T.Yokobayashi at 2016/03/10.
 *
 *----------------------------------------------------------------------
 */

/*
 *	@(#)config.c (monitor) 2019/10/10
 *
 *       system-related processing / system configuration information
 *
 *       target: RZT1
 */

#include "sysdepend.h"
#include "iodefine.h"
#include "_type_rzt_def.h"		/* for BOARD_RZT1_SCPZ,BOARD_RZT1_RSK */


/* used device driver */
IMPORT	ER	initSIO_scifa(SIOCB *, const CFGSIO *, W speed);
IMPORT	ER	initMemDisk(DISKCB *, const CFGDISK *);

/* memory region definition */
EXPORT	MEMSEG	MemSeg[] = {
	// ATCM, 512Kbyte
	{0x00000000, 0x00080000, MSA_RAM,	PGA_RW|PGA_C},
	// BTCM, 32Kbyte
	{0x00800000, 0x00808000, MSA_RAM,	PGA_RW|PGA_C},
	// Instruction RAM, 512Kbyte
	{0x04000000, 0x04080000, MSA_RAM,	PGA_RW|PGA_C},
	// Data RAM, 512Kbyte
	{0x20000000, 0x20080000, MSA_RAM,	PGA_RW|PGA_C},
	// SFlash ROM Mirror, 64MB
	{0x30000000, 0x34000000, MSA_FROM,	PGA_RO|PGA_C |0x10000000},
	// CS3,SDRAM RAM, 32Mbyte(256Mbit)
	{0x4C000000, 0x4E000000, MSA_RAM,	PGA_RW|PGA_C},
	// CS4,5 External device (1)
	{0x70000000, 0x78000000, MSA_IO,	PGA_RW|PGA_D |PGA_S|PGA_XN},
	// 周辺IOレジスタ, 1MByte
	{0xa0000000, 0xa0100000, MSA_IO,	PGA_RW|PGA_D |PGA_S|PGA_XN},
	// Boot,Debug Area
	{0xe8000000, 0xffffffff, MSA_ROM,	PGA_RO|PGA_NC},

	{0x30000000, 0x30020000, MSA_MON,	0},
//	{0x00006000, 0x00080000, MSA_OS,	0},
//	{0x48006000, 0x49000000, MSA_OS,	0},
	{0x4C020000, 0x4C800000, MSA_OS,	0},
	{0x30030000, 0x32000000, MSA_RDA,	0},
};

EXPORT	W	N_MemSeg = sizeof(MemSeg) / sizeof(MEMSEG);

/* unused memory region definition */
EXPORT	MEMSEG	NoMemSeg[] = {
	{0x00080000, 0x00800000, 0,		0},
	{0x00808000, 0x04000000, 0,		0},
	{0x04080000, 0x20000000, 0,		0},
	{0x20080000, 0x30000000, 0,		0},
	{0x30040000, 0x4C000000, 0,		0},
	{0x4E000000, 0x70000000, 0,		0},
	{0x78000000, 0xa0000000, 0,		0},
	{0xa0100000, 0xe8000000, 0,		0},
};

EXPORT	W	N_NoMemSeg = sizeof(NoMemSeg) / sizeof(MEMSEG);

/*
 * serial port configuration definition
 *       list in the order of port number
 */
EXPORT	const	CFGSIO	ConfigSIO[] = {
	{initSIO_scifa, 2},					/* SCIFA#2 */
};

EXPORT	const W	N_ConfigSIO = sizeof(ConfigSIO) / sizeof(CFGSIO);


/*
 * disk drive configuration definition
 *	list in the order of port number
 */
EXPORT	const CFGDISK	ConfigDisk[] = {
	{"rda",	DA_RONLY,	initMemDisk,	0},	// FlashROM
};

EXPORT	const W	N_ConfigDisk = sizeof(ConfigDisk) / sizeof(CFGDISK);

/* boot information */
EXPORT	const UH	BootSignature = 0xe382;		// signature
EXPORT	UB *	const PBootAddr = (UB *)0x30200000;	// primary boot loader address
 
/* ------------------------------------------------------------------------ */

#define	TIMEOUT		1000000	// microsec

#define	IIC2_IRQ	39
#define	IRQbit(x)	(1 << ((x) % 32))


/* ------------------------------------------------------------------------ */

IMPORT	W	pmicRead(W reg);
IMPORT	W	pmicWrite(W reg, W dat);
#define	pmicDelay(x)	waitUsec(4)	// about 16msec
#define	USBPowerOn	0xe0		// GPIO13(OD), High * power is supplied to A connector only
#define	USBPowerOff	0xe0		// GPIO13(OD), High

/* obtain DipSw status */
EXPORT	UW	DipSwStatus(void)
{
	UW	d;

#ifdef BOARD_RZT1_RSK
	d = (~PORTU.PIDR.BIT.B7) & 0x1;		/* PU7(IN) SW4-6状態を最下位Bitにｾｯﾄ */
	
	if (PORT3.PIDR.BIT.B5 == 0)			/* P35(In) NMI-SW1 ? */
		d |= SW_MON;					/* SW ON='L'で、T-Mmonitor強制起動 */
#endif

#ifdef BOARD_RZT1_SCPZ
	_UW *dipsw = (_UW*)0x74000000;		/* CS5 */
	d = ~(*dipsw);						/* Read dipsw to D16～D31 */
	d = (d>>16) & 0x0000FFFF;

	if ((d & 0xF) == 0)					/* 下位4bit=0 ? */
		d |= SW_MON;					/* T-Mmonitor強制起動 */
#endif

	
#if 0
	/* read data from read port */
	d = IICGPIORead(0xd9);

	/* unnecessary bits are masked and then invert logic. */
	d = (d ^ SW_MON) & SW_MON;

	/* check abort switch */
	if (in_w(GIO_I(GIO_L)) & 0x00000100) d |= SW_ABT;
#endif

	return d;
}

/* USB power control */
EXPORT	void	usbPower(BOOL power)
{
#if _TEMPOLALY_DELETE_			/////////// kari //////////////
	pmicWrite(27, (pmicRead(27) & 0x0f) |
		  		(power ? USBPowerOn : USBPowerOff));
	pmicDelay();
#endif /* _TEMPOLALY_DELETE_ */		/////////// kari //////////////
}

/* power off */
EXPORT	void	powerOff(void)
{
	W	i;

	for (i = 10; i < 14; i++) pmicWrite(i, 0xff);	// IRQ_MASK_A-D (mask)
	pmicDelay();

	for (i = 5 ; i < 9; i++) pmicWrite(i, 0xff);	// EVENT_A-D (clear)
	pmicDelay();

	while (1) {
		pmicWrite(15, 0x60);	// DEEP_SLEEP
		pmicDelay();
	}
}

/* reset start*/
EXPORT	void	resetStart(void)
{
#if 1
	/* プロテクションレジスタの解除（マニュアル11.2.1） */
	SYSTEM.PRCR.LONG = 0x0000A502;		/* ﾘｾｯﾄ関連 PRC1=1 */
	
	/* ソフトウェアリセット（マニュアル6.2.2） */
	SYSTEM.SWRR1.LONG = 0x4321A501;		/* ｿﾌﾄｳｪｱﾘｾｯﾄ */

	while (1) {
		;
	}
#else
	while (1) {
                /* reset */
		pmicWrite(15, 0xac);		// SHUTDOWN
		pmicDelay();
	}
#endif
}

/* initialize hardware peripherals (executed only during reset) */
EXPORT	void	initHardware(void)
{
#if _TEMPOLALY_DELETE_			/////////// kari //////////////
	/* enable abort switch interrupt */
	out_w(GIO_IDT1(GIO_L), 0x00000008);	// asynchronous leading-edge high interrupt
	out_w(GIO_IIR(GIO_L), 0x00000100);
	out_w(GIO_IIA(GIO_L), 0x00000100);
	out_w(GIO_IEN(GIO_L), 0x00000100);
#endif /* _TEMPOLALY_DELETE_ */		/////////// kari //////////////

	return;
}

/* LED on/off */
/*
 * Note:下位16bitは点灯指定(0:OFF, 1:ON)、bit1=LED, bit0=LED
 *      上位16bitのﾏｽｸ値が'1'に対応するLEDの点灯状態は変更されない。
 *
 */
EXPORT	void	cpuLED(UW v)
{
	UB	m, d, r, c;
	UB	tmp;

	m = ~((v >> 16) | 0xf0);	// mask (0:unmodified 1:modify)
	d = ((v >>  0) & 0x0f);		// set value (0:off 1:on) :正論理
//	d = ~((v >>  0) | 0xf0);	// set value (0:on 1:off) :負論理

	/* PF7---LED0 */
	r = PORTF.PODR.BYTE;
	tmp = r;					// 退避
	r >>= 7;
	c = (r ^ d) & m;			// modify flag (0:unmodified 1:modify)
	c = (c & 0x01) << 7;		// bit0だけ有効
	r = tmp;					// 復帰
	PORTF.PODR.BYTE = r ^ c;

	/* PF56---LED1 */
	r = PORT5.PODR.BYTE;
	tmp = r;					// 退避
	r >>= 5;
	c = (r ^ d) & m;			// modify flag (0:unmodified 1:modify)
	c = (c & 0x02) << 5;		// bit1だけ有効
	r = tmp;					// 復帰
	PORT5.PODR.BYTE = r ^ c;

#ifdef BOARD_RZT1_RSK
	/* P77---LED2 */
	r = PORT7.PODR.BYTE;
	tmp = r;					// 退避
	r >>= 5;
	c = (r ^ d) & m;			// modify flag (0:unmodified 1:modify)
	c = (c & 0x04) << 5;		// bit2だけ有効
	r = tmp;					// 復帰
	PORT7.PODR.BYTE = r ^ c;

	/* PA0---LED3 */
	r = PORTA.PODR.BYTE;
	tmp = r;					// 退避
	r <<= 3;
	c = (r ^ d) & m;			// modify flag (0:unmodified 1:modify)
	c = (c & 0x08) >> 3;		// bit3だけ有効
	r = tmp;					// 復帰
	PORTA.PODR.BYTE = r ^ c;
#endif
	
///	r = IICGPIORead(0xb9);
///	c = (r ^ d) & m;			// modify flag (0:unmodified 1:modify)
///	IICGPIOWrite(0xb8, r ^ c);
}

/*
 * machine-dependent interrupt processing
 *       vec     interrupt vector number
 *       return value    0: unsupported target
 *               1: for the supported target, processing was performed. (monitor still continues)
 *               2: for the supported target, proceesing was performed (interrupt handler is exited)
 */
EXPORT	W	procHwInt(UW vec)
{
#if 1	//////////////////
//// 割り込み番号の範囲チェック必要 ////
	return 0;
#else	/////////////////
        /* only abort switch (GPIO(P8)) is supported */
	if (vec != EIT_GPIO(8)) return 0;

        /* clear interrupt */
	out_w(GIO_IIR(GIO_L), 0x00000100);

	DSP_S("Abort Switch (SW1) Pressed");
	return 1;
#endif	//////////////////
}

/* ------------------------------------------------------------------------ */

/*
        configure GPIO pin multiplexer

                * : used functions
	
        pin name      function 0(00)     function1(01)     function2(10)     function3(11)
	GIO_P0      GIO_P0*
	GIO_P1      GIO_P1*       USB_WAKEUP    USB_PWR_FAULT
	GIO_P2      GIO_P2*
	GIO_P3      GIO_P3*
	GIO_P4      GIO_P4*                     NAND_RB1
	GIO_P5      GIO_P5                      NAND_RB2      CAM_SCLK*
	GIO_P6      GIO_P6*                     NAND_RB3
	GIO_P7      GIO_P7*                     NAND_CE0
	GIO_P8      GIO_P8*                     NAND_CE1
	GIO_P9      GIO_P9*                     NAND_CE2
	GIO_P10     GIO_P10*                    NAND_CE3
	AB0_CLK     GIO_P11       AB0_CLK*      NTS_CLK
	AB0_AD0     GIO_P12       AB0_AD0*
	AB0_AD1     GIO_P13       AB0_AD1*
	AB0_AD2     GIO_P14       AB0_AD2*
	AB0_AD3     GIO_P15       AB0_AD3*
	
        pin name      function 0(00)     function1(01)     function2(10)     function3(11)
	AB0_AD4     GIO_P16       AB0_AD4*
	AB0_AD5     GIO_P17       AB0_AD5*
	AB0_AD6     GIO_P18       AB0_AD6*
	AB0_AD7     GIO_P19       AB0_AD7*
	AB0_AD8     GIO_P20       AB0_AD8*
	AB0_AD9     GIO_P21       AB0_AD9*
	AB0_AD10    GIO_P22       AB0_AD10*
	AB0_AD11    GIO_P23       AB0_AD11*
	AB0_AD12    GIO_P24       AB0_AD12*
	AB0_AD13    GIO_P25       AB0_AD13*
	AB0_AD14    GIO_P26       AB0_AD14*
	AB0_AD15    GIO_P27       AB0_AD15*
	AB0_A17     GIO_P28       AB0_A17*
	AB0_A18     GIO_P29       AB0_A18*
	AB0_A19     GIO_P30       AB0_A19*
	AB0_A20     GIO_P31       AB0_A20*
	
        pin name      function 0(00)     function1(01)     function2(10)     function3(11)
	AB0_A21     GIO_P32       AB0_A21*
	AB0_A22     GIO_P33       AB0_A22*
	AB0_A23     GIO_P34       AB0_A23*
	AB0_A24     GIO_P35       AB0_A24*
	AB0_A25     GIO_P36*      AB0_A25
	AB0_A26     GIO_P37*      AB0_A26
	AB0_ADV     GIO_P38       AB0_ADV*
	AB0_RDB     GIO_P39       AB0_RDB*      NTS_DATA3
	AB0_WRB     GIO_P40       AB0_WRB*      NTS_DATA4
	AB0_WAIT    GIO_P41       AB0_WAIT*     NTS_DATA5
	AB0_CSB0    GIO_P42       AB0_CSB0*     NTS_DATA6
	AB0_CSB1    GIO_P43       AB0_CSB1*     NTS_DATA7
	AB0_CSB2    GIO_P44*      AB0_CSB2      NTS_VS
	AB0_CSB3    GIO_P45       AB0_CSB3*     NTS_HS
	AB0_BEN0    GIO_P46       AB0_BEN0*
	AB0_BEN1    GIO_P47       AB0_BEN1*
	
        pin name      function 0(00)     function1(01)     function2(10)     function3(11)
	SP0_CS1     GIO_P48       SP0_CS1*
	SP0_CS2     GIO_P49       SP0_CS2*
	LCD_PXCLK   GIO_P50       LCD_PXCLK*
	LCD_R0      GIO_P51       LCD_R0*
	LCD_R1      GIO_P52       LCD_R1*
	LCD_R2      GIO_P53       LCD_R2*
	LCD_R3      GIO_P54       LCD_R3*
	LCD_R4      GIO_P55       LCD_R4*
	LCD_R5      GIO_P56       LCD_R5*
	LCD_G0      GIO_P57       LCD_G0*
	LCD_G1      GIO_P58       LCD_G1*
	LCD_G2      GIO_P59       LCD_G2*
	LCD_G3      GIO_P60       LCD_G3*
	LCD_G4      GIO_P61       LCD_G4*
	LCD_G5      GIO_P62       LCD_G5*
	LCD_B0      GIO_P63       LCD_B0*
	
        pin name      function 0(00)     function1(01)     function2(10)     function3(11)
	LCD_B1      GIO_P64       LCD_B1*
	LCD_B2      GIO_P65       LCD_B2*
	LCD_B3      GIO_P66       LCD_B3*
	LCD_B4      GIO_P67       LCD_B4*
	LCD_B5      GIO_P68       LCD_B5*
	LCD_HSYNC   GIO_P69       LCD_HSYNC*
	LCD_VSYNC   GIO_P70       LCD_VSYNC*
	LCD_ENABLE  GIO_P71       LCD_ENABLE*
	NTS_CLK     GIO_P72*      NTS_CLK                     PM1_CLK
	NTS_VS      GIO_P73*      NTS_VS        SP1_CLK
	NTS_HS      GIO_P74*      NTS_HS        SP1_SI
	NTS_DATA0   GIO_P75       NTS_DATA0     SP1_SO        CAM_YUV0*
	NTS_DATA1   GIO_P76       NTS_DATA1     SP1_CS0       CAM_YUV1*
	NTS_DATA2   GIO_P77       NTS_DATA2     SP1_CS1       CAM_YUV2*
	NTS_DATA3   GIO_P78       NTS_DATA3     SP1_CS2       CAM_YUV3*
	NTS_DATA4   GIO_P79       NTS_DATA4     SP1_CS3       CAM_YUV4*
	
        pin name      function 0(00)     function1(01)     function2(10)     function3(11)
	NTS_DATA5   GIO_P80*      NTS_DATA5     SP1_CS4       PM1_SEN
	NTS_DATA6   GIO_P81*      NTS_DATA6     SP1_CS5       PM1_SI
	NTS_DATA7   GIO_P82*      NTS_DATA7                   PM1_SO
	IIC_SCL     GIO_P83       IIC_SCL*
	IIC_SDA     GIO_P84       IIC_SDA*
	URT0_CTSB   GIO_P85       URT0_CTSB     URT1_SRIN*
	URT0_RTSB   GIO_P86       URT0_RTSB     URT1_SOUT*
	PM0_SI      GIO_P87       PM0_SI*
	SD0_DATA1   GIO_P88       SD0_DATA1*
	SD0_DATA2   GIO_P89       SD0_DATA2*
	SD0_DATA3   GIO_P90       SD0_DATA3*
	SD0_CKI     GIO_P91       SD0_CKI*
	SD1_CKI     GIO_P92       SD1_CKI       CAM_CLKI*
	SD2_CKI     GIO_P93       SD2_CKI*      NAND_OE
	PWM0        GIO_P94*      PWM0
	PWM1        GIO_P95*      PWM1
	
        pin name      function 0(00)     function1(01)     function2(10)     function3(11)
	USB_CLK     GIO_P96       USB_CLK*
	USB_DATA0   GIO_P97       USB_DATA0*
	USB_DATA1   GIO_P98       USB_DATA1*
	USB_DATA2   GIO_P99       USB_DATA2*
	USB_DATA3   GIO_P100      USB_DATA3*
	USB_DATA4   GIO_P101      USB_DATA4*
	USB_DATA5   GIO_P102      USB_DATA5*
	USB_DATA6   GIO_P103      USB_DATA6*
	USB_DATA7   GIO_P104      USB_DATA7*
	USB_DIR     GIO_P105      USB_DIR*
	USB_STP     GIO_P106      USB_STP*
	USB_NXT     GIO_P107      USB_NXT*
	URT2_SRIN   GIO_P108      URT2_SRIN*
	URT2_SOUT   GIO_P109      URT2_SOUT*
	URT2_CTSB   GIO_P110      URT2_CTSB*
	URT2_RTSB   GIO_P111      URT2_RTSB*
	
        pin name      function 0(00)     function1(01)     function2(10)     function3(11)
	SD2_CKO     GIO_P112      SD2_CKO*       NAND_D2
	SD2_CMD     GIO_P113      SD2_CMD*       NAND_D3
	SD2_DATA0   GIO_P114      SD2_DATA0*     NAND_D4
	SD2_DATA1   GIO_P115      SD2_DATA1*     NAND_D5
	SD2_DATA2   GIO_P116      SD2_DATA2*     NAND_D6
	SD2_DATA3   GIO_P117      SD2_DATA3*     NAND_D7
*/
#if 0	/////////////////////
EXPORT	const UW	GPIOConfig[] __attribute__((section(".startup"))) = {
	CHG_PINSEL_G(0),
	0x55400C00,		// AB0_CLK,AB0_AD3-0,CAM_SCLK
	CHG_PINSEL_G(16),
	0x55555555,		// AB0_AD15-4,AB0_A20-17
	CHG_PINSEL_G(32),
	0x54555055,		// AB0_BEN1-0,AB0_CSB3,AB0_CSB1-0,
				// AB0_WAIT,AB0_WRB,AB0_RDB,AB0_ADV,
				// AB0_A24-21

	CHG_CTRL_AB0_BOOT,	// AB0(AsyncBus0) pin:
	0x00000001,		// 	configured by PINSEL

	CHG_PINSEL_G(48),
	0x55555555,		// LCD,SP0_CS2-1
	CHG_PINSEL_G(64),
	0xffc05555,		// CAM_YUV4-0,LCD
	CHG_PINSEL_G(80),
	0x06556940,		// SD2_CKI,CAM_CLKI,SD0_CKI,SD0_DATA3-1,
				// PM0,URT1,IIC
	CHG_PINSEL_G(96),
	0x55555555,		// URT2,USB
	CHG_PINSEL_G(112),
	0x00000555,		// SD2
	CHG_PINSEL_SP0,
	0x00000000,
	CHG_PINSEL_DTV,
	0x00000001,
	CHG_PINSEL_SD0,
	0x00000000,
	CHG_PINSEL_SD1,
	0x00000002,
	CHG_PINSEL_IIC2,
	0x00000000,
	CHG_PULL_G(0),
	0x55055005,		// P7,P6,P4,P3,P0: IN, pull-up/down dis
	CHG_PULL_G(8),
	0x00000005,		// P8: IN, pull-up/down dis
	CHG_PULL_G(16),
	0x00000000,		// (default)
	CHG_PULL_G(24),
	0x00000000,		// (default)
	CHG_PULL_G(32),
	0x00550000,		// P37,36: IN, pull-up/down dis
	CHG_PULL_G(40),
	0x00050000,		// P44: IN, pull-up/down dis
	CHG_PULL_G(48),
	0x11111111,		// (default)
	CHG_PULL_G(56),
	0x11111111,		// (default)
	CHG_PULL_G(64),
	0x11111111,		// (default)
	CHG_PULL_G(72),
	0x00000005,		// P72: IN, pull-up/down dis
	CHG_PULL_G(80),
	0x00400050,		// P81: IN, pull-up/down dis
				// URT1_SRIN: IN, pull-down
	CHG_PULL_G(88),
	0x55000444,		// P95,94: IN, pull-up/down dis
				// SD0_DATA3-1: IN, pull-down
	CHG_PULL_G(96),
	0x44444444,		// USB signals: IN, pull-down
	CHG_PULL_G(104),
	0x04044444,		// USB signals: IN, pull-down
				// URT2_CTSB,URT2_SRIN: IN, pull-down
	CHG_PULL_G(112),
	0x00000000,		// (default)
	CHG_PULL_G(120),
	0x00000000,		// (default)

	CHG_PULL(0),
	0x50000004,		// URT0_SRIN: IN, pull-up/down dis
				// DEBUG_EN: IN, pull-down
	CHG_PULL(1),
	0x15110600,		// SP0_SO: OUT, pull-up/down dis
				// SP0_SI: IN, pull-up/down dis
				// SP0_CS: OUT, pull-up/down dis
				// SP0_CK: OUT, pull-up/down dis
				// JT0C: IN, pull-up
				// JT0B: OUT, pull-down
				// JT0A: OUT, pull-down
	CHG_PULL(2),
	0x60000661,		// PM0_SEN: IN, pull-up
				// SD0_DAT: IN, pull-up
				// SD1_CMD: IN, pull-up
				// SD0_CLK: OUT, pull-up/down dis
	CHG_PULL(3),
	0x00000000,		// (default)

	GIO_E0(GIO_L),
	0x000001d9,		// P8,P7,P6,P4,P3,P0: IN
	GIO_E1(GIO_L),
	0x00000604,		// P10,P9,P2: OUT
	GIO_E0(GIO_H),
	0x00001030,		// P44,P37,P36: IN
	GIO_E1(GIO_H),
	0x00000000,		// (default)
	GIO_E0(GIO_HH),
	0xc0020100,		// P95,P94,P81,P72:IN
	GIO_E1(GIO_HH),
	0x00040200,		// P82,P73: OUT
	GIO_OL(GIO_L),
	0x06040000,		// P10,P9,P2=0
	GIO_OL(GIO_HH),
	0x02000000,		// P73=0
	GIO_OH(GIO_HH),
	0x00040000,		// P82=0

	0x00000000,		// (terminate)
	0x00000000,
};
#endif	//////////////////////


/*----------------------------------------------------------------------
#|History of "config.c"
#|---------------------
#|* 2016/03/10	It's copied from "../tef_em1d/" and it's modified.
#|* 2017/08/08	resetStart()で、ソフトウェアリセット実行する対応
#|* 2019/10/08	RSK時、NMI(SW1)がONでT-Monitor強制起動とする。
#|
*/
