/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2017 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* System Name  : RZ/T1 Init program
* File Name    : loader_param.c
* Version      : 1.3
* Device       : R7S910017
* Abstract     : Loader program 2
* Tool-Chain   : e2studio
* OS           : not use
* H/W Platform : RZ/T1 Evaluation Board (RTK7910022C00000BR)
* Description  : Loader settings of RZ/T1
* Limitation   : none
*******************************************************************************/
/*******************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 01.07.2015 1.1      First Release
*              : 30.11.2015 1.2      Second Release
*                                     - No modification
*              : 31.03.2017 1.3      Third Release
*                                     - No modification
*******************************************************************************/

#define DUMMY 0x0

#if defined (RAM_BOOT)
// Parameter is not needed for RAM boot.
#else
/*******************************************************************************
Parameter Information for the Loader in SPI Boot Mode
*******************************************************************************/
const unsigned int Loader_Param[]  __attribute__ ((section (".loader_param"))) = {
		0x00000000, //CACHE_FLG
		0x00070707, //SSLDR_V
		0x00000003, //SPBCR_V
		0x0,        //DRCR_V
		0x0,        //SPIBSC_FLG
		0x3000004C, //LDR_ADDR_NML
	#if 0	/* 0x00803000 start(チェックサムは同じ) */
		0x00005000, //LDR_SIZE_NML
		0x00803000, //DEST_ADDR_NML
	#else
		0x00006000, //LDR_SIZE_NML
		0x00802000, //DEST_ADDR_NML
	#endif
		DUMMY,      //DUMMY1
		DUMMY,      //DUMMY2
		DUMMY,      //DUMMY3
		DUMMY,      //DUMMY4
		DUMMY,      //DUMMY5
		DUMMY,      //DUMMY6
		DUMMY,      //DUMMY7
		DUMMY,      //DUMMY8
		DUMMY,      //DUMMY9
		DUMMY,      //DUMMY10
		0x0000B7DD  //CHECK_SUM
};
#endif
/*----------------------------------------------------------------------
#|History of "loader_param.c"
#|---------------------------
#|* 2017/07/15	ローダプログラムの展開先を0x802000→0x803000に変更
#|* 2018/04/23	ローダプログラムの展開先を0x803000→0x802000に戻した
#|
*/
