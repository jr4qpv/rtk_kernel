/*
 *----------------------------------------------------------------------
 *
 *    T-Kernel 2.0 Software Package
 *
 *----------------------------------------------------------------------
 */

/*
 *	@(#)rzt1_init.c (RZT1) 2019/10/08
 *
 *  RZ/T1 initialize routine
 *  ※"common/sflash_boot/bus_init_serial_boot.c"でも設定してるので参照
 */

#include <machine.h>
#include "iodefine.h"
#include "r_port.h"
#include "r_mpc.h"				/* for mpc_write_enable,mpc_write_disable */
#include "r_bsc.h"
#include "_type_rzt_def.h"		/* for BOARD_RZT1_SCPZ,BOARD_RZT1_RSK */


/*
 *      Initialize bus port settings for SCPZ
 */
#ifdef BOARD_RZT1_SCPZ
static void set_bus_port_scpz(void)
{
	//--- SCPZ用 IOポートの初期化(p605) ---
    PORT7.PDR.BIT.B0 = PORT_DIRECTION_HIZ;  // Initialize P70(D16)
    PORT7.PMR.BIT.B0 = PORT_MODE_GENERAL;   
    PORT7.PDR.BIT.B1 = PORT_DIRECTION_HIZ;  // Initialize P71(D17)
    PORT7.PMR.BIT.B1 = PORT_MODE_GENERAL;   
    PORT7.PDR.BIT.B2 = PORT_DIRECTION_HIZ;  // Initialize P72(D18)
    PORT7.PMR.BIT.B2 = PORT_MODE_GENERAL;   
    PORT7.PDR.BIT.B3 = PORT_DIRECTION_HIZ;  // Initialize P73(D19)
    PORT7.PMR.BIT.B3 = PORT_MODE_GENERAL;   
    PORT7.PDR.BIT.B4 = PORT_DIRECTION_HIZ;  // Initialize P74(D20)
    PORT7.PMR.BIT.B4 = PORT_MODE_GENERAL;   
    PORT7.PDR.BIT.B5 = PORT_DIRECTION_HIZ;  // Initialize P75(D21)
    PORT7.PMR.BIT.B5 = PORT_MODE_GENERAL;   
    PORT7.PDR.BIT.B6 = PORT_DIRECTION_HIZ;  // Initialize P76(D22)
    PORT7.PMR.BIT.B6 = PORT_MODE_GENERAL;   
    PORT7.PDR.BIT.B7 = PORT_DIRECTION_HIZ;  // Initialize P77(D23)
    PORT7.PMR.BIT.B7 = PORT_MODE_GENERAL;   
    PORTA.PDR.BIT.B0 = PORT_DIRECTION_HIZ;  // Initialize PA0(D24)
    PORTA.PMR.BIT.B0 = PORT_MODE_GENERAL;   
    PORTA.PDR.BIT.B1 = PORT_DIRECTION_HIZ;  // Initialize PA1(D25)
    PORTA.PMR.BIT.B1 = PORT_MODE_GENERAL;   
    PORTA.PDR.BIT.B2 = PORT_DIRECTION_HIZ;  // Initialize PA2(D26)
    PORTA.PMR.BIT.B2 = PORT_MODE_GENERAL;   
    PORTA.PDR.BIT.B3 = PORT_DIRECTION_HIZ;  // Initialize PA3(D27)
    PORTA.PMR.BIT.B3 = PORT_MODE_GENERAL;   
    PORTA.PDR.BIT.B4 = PORT_DIRECTION_HIZ;  // Initialize PA4(D28)
    PORTA.PMR.BIT.B4 = PORT_MODE_GENERAL;   
    PORTA.PDR.BIT.B5 = PORT_DIRECTION_HIZ;  // Initialize PA5(D29)
    PORTA.PMR.BIT.B5 = PORT_MODE_GENERAL;   
    PORTA.PDR.BIT.B6 = PORT_DIRECTION_HIZ;  // Initialize PA6(D30)
    PORTA.PMR.BIT.B6 = PORT_MODE_GENERAL;   
    PORTA.PDR.BIT.B7 = PORT_DIRECTION_HIZ;  // Initialize PA7(D31)
    PORTA.PMR.BIT.B7 = PORT_MODE_GENERAL;   
	
    PORTD.PDR.BIT.B0 = PORT_DIRECTION_HIZ;  // Initialize PD0(CS4#)
    PORTD.PMR.BIT.B0 = PORT_MODE_GENERAL;   
    PORTK.PDR.BIT.B1 = PORT_DIRECTION_HIZ;  // Initialize PK1(CS5#)
    PORTK.PMR.BIT.B1 = PORT_MODE_GENERAL;   
    PORT4.PDR.BIT.B3 = PORT_DIRECTION_HIZ;  // Initialize P43(WE2#)
    PORT4.PMR.BIT.B3 = PORT_MODE_GENERAL;   
    PORT4.PDR.BIT.B7 = PORT_DIRECTION_HIZ;  // Initialize P47(WE3#)
    PORT4.PMR.BIT.B7 = PORT_MODE_GENERAL;   
    PORT4.PDR.BIT.B4 = PORT_DIRECTION_HIZ;  // Initialize P44(WAIT#)
    PORT4.PMR.BIT.B4 = PORT_MODE_GENERAL;   
    PORTT.PDR.BIT.B5 = PORT_DIRECTION_HIZ;  // Initialize PT5(BS#)
    PORTT.PMR.BIT.B5 = PORT_MODE_GENERAL;   

	mpc_write_enable();  // Enables writing to the PFS register

	//--- SCPZ用 MPCの設定(p654) ---
    MPC.P70PFS.BIT.PSEL = 0x22;                    // Set P70 to D16
    MPC.P71PFS.BIT.PSEL = 0x22;                    // Set P71 to D17
    MPC.P72PFS.BIT.PSEL = 0x22;                    // Set P72 to D18
    MPC.P73PFS.BIT.PSEL = 0x22;                    // Set P73 to D19
    MPC.P74PFS.BIT.PSEL = 0x22;                    // Set P74 to D20
    MPC.P75PFS.BIT.PSEL = 0x22;                    // Set P75 to D21
    MPC.P76PFS.BIT.PSEL = 0x22;                    // Set P76 to D22
    MPC.P77PFS.BIT.PSEL = 0x22;                    // Set P77 to D23
    MPC.PA0PFS.BIT.PSEL = 0x22;                    // Set PA0 to D24
    MPC.PA1PFS.BIT.PSEL = 0x22;                    // Set PA1 to D25
    MPC.PA2PFS.BIT.PSEL = 0x22;                    // Set PA2 to D26
    MPC.PA3PFS.BIT.PSEL = 0x22;                    // Set PA3 to D27
    MPC.PA4PFS.BIT.PSEL = 0x22;                    // Set PA4 to D28
    MPC.PA5PFS.BIT.PSEL = 0x22;                    // Set PA5 to D29
    MPC.PA6PFS.BIT.PSEL = 0x22;                    // Set PA6 to D30
    MPC.PA7PFS.BIT.PSEL = 0x22;                    // Set PA7 to D31

    MPC.PD0PFS.BIT.PSEL = 0x23;                    // Set PD0 to CS4#
    MPC.PK1PFS.BIT.PSEL = 0x23;                    // Set PK1 to CS5#
    MPC.P43PFS.BIT.PSEL = 0x22;                    // Set P43 to WE2#
    MPC.P47PFS.BIT.PSEL = 0x22;                    // Set P47 to WE3#
    MPC.P44PFS.BIT.PSEL = 0x23;                    // Set P44 to WAIT#
    MPC.PT5PFS.BIT.PSEL = 0x23;                    // Set PT5 to BS#

	mpc_write_disable(); // Disables writing to the PFS register

    PORT7.PMR.BIT.B0 = PORT_MODE_PERIPHERAL;
    PORT7.PMR.BIT.B1 = PORT_MODE_PERIPHERAL;
    PORT7.PMR.BIT.B2 = PORT_MODE_PERIPHERAL;
    PORT7.PMR.BIT.B3 = PORT_MODE_PERIPHERAL;
    PORT7.PMR.BIT.B4 = PORT_MODE_PERIPHERAL;
    PORT7.PMR.BIT.B5 = PORT_MODE_PERIPHERAL;
    PORT7.PMR.BIT.B6 = PORT_MODE_PERIPHERAL;
    PORT7.PMR.BIT.B7 = PORT_MODE_PERIPHERAL;
    PORTA.PMR.BIT.B0 = PORT_MODE_PERIPHERAL;
    PORTA.PMR.BIT.B1 = PORT_MODE_PERIPHERAL;
    PORTA.PMR.BIT.B2 = PORT_MODE_PERIPHERAL;
    PORTA.PMR.BIT.B3 = PORT_MODE_PERIPHERAL;
    PORTA.PMR.BIT.B4 = PORT_MODE_PERIPHERAL;
    PORTA.PMR.BIT.B5 = PORT_MODE_PERIPHERAL;
    PORTA.PMR.BIT.B6 = PORT_MODE_PERIPHERAL;
    PORTA.PMR.BIT.B7 = PORT_MODE_PERIPHERAL;

    PORTD.PMR.BIT.B0 = PORT_MODE_PERIPHERAL;
    PORTK.PMR.BIT.B1 = PORT_MODE_PERIPHERAL;
    PORT4.PMR.BIT.B3 = PORT_MODE_PERIPHERAL;
    PORT4.PMR.BIT.B7 = PORT_MODE_PERIPHERAL;
    PORT4.PMR.BIT.B4 = PORT_MODE_PERIPHERAL;
    PORTT.PMR.BIT.B5 = PORT_MODE_PERIPHERAL;
}
#endif



/*
 *      RZ/T1 initialize routines
 */
void	rzt1_initialize(void)
{
	//--- システムクロックコントロールレジスタの設定(p233) ---
	SYSTEM.SCKCR.BIT.SERICK = 0;			/* ｼﾘｱﾙｸﾛｯｸSERICLK=150MHz */


	//--- 低消費電力機能の設定(p260) ---
	SYSTEM.PRCR.LONG = 0x0000a502;			// 低消費電力機能ﾚｼﾞｽﾀ書込許可

	// 周辺モジュール機能を有効化
	SYSTEM.MSTPCRA.BIT.MSTPCRA1 = 0;		// CWTW#0  ﾓｼﾞｭｰﾙｽﾄｯﾌﾟ解除
	SYSTEM.MSTPCRA.BIT.MSTPCRA4 = 0;		// CWT#0   ﾓｼﾞｭｰﾙｽﾄｯﾌﾟ解除
	SYSTEM.MSTPCRB.BIT.MSTPCRB7 = 0;		// SCIFA#2 ﾓｼﾞｭｰﾙｽﾄｯﾌﾟ解除

	SYSTEM.PRCR.LONG = 0x0000a500;			// 低消費電力機能ﾚｼﾞｽﾀ書込禁止


	/* Set bus port settings when operation mode is SCPZ board */
#ifdef BOARD_RZT1_SCPZ
	set_bus_port_scpz();

	/**************************************/
	/*      Set CS5 area : FPGA (p398)    */
	/**************************************/
	BSC.CS5BCR.BIT.IWW = BSC_IDLE_CYCLE_1;   // Set idle cycle 1
	BSC.CS5BCR.BIT.IWRWD = BSC_IDLE_CYCLE_0; // Set idle cycle 0
	BSC.CS5BCR.BIT.IWRWS = BSC_IDLE_CYCLE_0; // Set idle cycle 0
	BSC.CS5BCR.BIT.IWRRD = BSC_IDLE_CYCLE_0; // Set idle cycle 0 
	BSC.CS5BCR.BIT.IWRRS = BSC_IDLE_CYCLE_0; // Set idle cycle 0   
	BSC.CS5BCR.BIT.TYPE = BSC_TYPE_NORMAL;   // Set memory type to normal memory  
	BSC.CS5BCR.BIT.BSZ = BSC_WIDTH_32_BIT;   // Set data bus width to 32-bit
    
	BSC.CS5WCR.BIT.SW = BSC_DELAY_STATE_CYCLE_2_5; // Set delay cycle to 2.5 state
	BSC.CS5WCR.BIT.WR = BSC_ACCESS_WAIT_6 ;        // Set access wait to 6
	BSC.CS5WCR.BIT.WM = BSC_EXT_WAIT_IGNORED;      // Mask external wait input
	BSC.CS5WCR.BIT.HW = BSC_DELAY_STATE_CYCLE_0_5; // Set delay cycle to 0.5 state
#endif
	
	//--- マルチファンクションピンコントローラの設定(p619) ---
    PORT9.PDR.BIT.B1 = PORT_DIRECTION_HIZ;  // Initialize P91(TXD2)
    PORT9.PMR.BIT.B1 = PORT_MODE_GENERAL;   
    PORT9.PDR.BIT.B2 = PORT_DIRECTION_HIZ;  // Initialize P92(RXD2)
    PORT9.PMR.BIT.B2 = PORT_MODE_GENERAL;   
	
	mpc_write_enable();  // Enables writing to the PFS register

	MPC.P91PFS.BIT.PSEL = 0b001011;			// Set P91 to TXD2
	MPC.P92PFS.BIT.PSEL = 0b001011;			// Set P92 to RXD2

	mpc_write_disable(); // Disables writing to the PFS register

	PORT9.PMR.BIT.B1 = PORT_MODE_PERIPHERAL;	// TXD2(P91)
	PORT9.PMR.BIT.B2 = PORT_MODE_PERIPHERAL;	// RXD2(P92)


	//--- ＩＯポートの設定(p605) ---
	/* Set PF7 to Output port pin (Using LED0) */
	PORTF.PDR.BIT.B7 = PORT_DIRECTION_HIZ;  // Initialize port settings
	PORTF.PMR.BIT.B7 = PORT_MODE_GENERAL;

	PORTF.PODR.BIT.B7 = PORT_OUTPUT_LOW;    // Set output level to Low
	PORTF.PDR.BIT.B7 = PORT_DIRECTION_OUTPUT;  // Set port direction to output

	/* Set P56 to Output port pin (Using LED1) */
	PORT5.PDR.BIT.B6 = PORT_DIRECTION_HIZ;  // Initialize port settings
	PORT5.PMR.BIT.B6 = PORT_MODE_GENERAL;

	PORT5.PODR.BIT.B6 = PORT_OUTPUT_LOW;    // Set output level to Low
	PORT5.PDR.BIT.B6 = PORT_DIRECTION_OUTPUT;  // Set port direction to output

#ifdef BOARD_RZT1_RSK
	/* Set P77 to Output port pin (Using LED2) */
	PORT7.PDR.BIT.B7 = PORT_DIRECTION_HIZ;  // Initialize port settings
	PORT7.PMR.BIT.B7 = PORT_MODE_GENERAL;

	PORT7.PODR.BIT.B7 = PORT_OUTPUT_LOW;    // Set output level to Low
	PORT7.PDR.BIT.B7 = PORT_DIRECTION_OUTPUT;  // Set port direction to output

	/* Set PA0 to Output port pin (Using LED3) */
	PORTA.PDR.BIT.B0 = PORT_DIRECTION_HIZ;  // Initialize port settings
	PORTA.PMR.BIT.B0 = PORT_MODE_GENERAL;

	PORTA.PODR.BIT.B0 = PORT_OUTPUT_LOW;    // Set output level to Low
	PORTA.PDR.BIT.B0 = PORT_DIRECTION_OUTPUT;  // Set port direction to output

	/* Set PU7 to Input port pin (RSK Using DIPSW4-6) */
	PORTU.PDR.BIT.B7 = PORT_DIRECTION_HIZ;  // Initialize port settings
	PORTU.PMR.BIT.B7 = PORT_MODE_GENERAL;

	PORTU.PDR.BIT.B7 = PORT_DIRECTION_INPUT;  // Set port direction to intput
#endif
	
	return;
}


/*----------------------------------------------------------------------
#|History of "rzt1_init.c"
#|------------------------
#|* 2018/03/26	New created.(by T.Yokobayashi)
#|* 2018/04/16	「BOARD_RZT1_SCPZ」の定義追加。
#|* 2019/10/08	RSK時、PU7は入力ピンに設定。
#|
*/
