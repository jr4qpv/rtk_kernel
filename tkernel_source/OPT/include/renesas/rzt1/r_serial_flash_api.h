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
* Copyright (C) 2015 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* System Name  : RZ/T1 Init program
* File Name    : r_spibsc_flash_api.h
* Version      : 1.3
* Device       : R7S910017
* Abstract     : API SPIBSC Flash settings
* Tool-Chain   : e2studio
* OS           : not use
* H/W Platform : RZ/T1 Evaluation Board (RTK7910022C00000BR)
* Description  : SPIBSC Flash setting API for RZ/T1
* Limitation   : none
*******************************************************************************/
/*******************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 22.12.2015 1.0      First Release
*              : 14.06.2016 1.1      Second Release
*              : 26.12.2016 1.2      Third Release
*                                     - No modification
*              : 31.10.2017 1.3      4th Release
*                                     - No modification
*******************************************************************************/
#ifndef R_SERIAL_FLASH_API_H
#define R_SERIAL_FLASH_API_H


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_serial_flash_ioset_api.h"
#include "_type_rzt_def.h"		/* for SPIBSC_SFLASH_TYPE */


/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/
#if (SPIBSC_SFLASH_TYPE == TYPE_MT25QL)
#define R_SERIAL_FLASH_TOP              (0x10000000U)
#define R_SERIAL_FLASH_END              (0x10FFFFFCU)
#define R_SERIAL_FLASH_ADDR_LIMIT       (0x11000000U)
#define R_SERIAL_FLASH_READ_SIZE        (64U)
#define R_SERIAL_FLASH_CNT_ADDR         (0x10FF0000U)
  #if (__MT25QL_BUS_WITDH == 1)
#define R_SERIAL_FLASH_DATA_WIDTH       (SPIBSC_1BIT)
  #elif (__MT25QL_BUS_WITDH == 4)
#define R_SERIAL_FLASH_DATA_WIDTH       (SPIBSC_4BIT)
  #endif
#define R_SERIAL_FLASH_ADDR_MODE        (SPIBSC_OUTPUT_ADDR_24)
#define R_SERIAL_FLASH_WRITE_BYTE       (4)
#define R_SERIAL_FLASH_READ_BYTE        (4)
#else
#define R_SERIAL_FLASH_TOP              (0x10000000U)
#define R_SERIAL_FLASH_END              (0x13FFFFFCU)
#define R_SERIAL_FLASH_ADDR_LIMIT       (0x14000000U)
#define R_SERIAL_FLASH_READ_SIZE        (64U)
#define R_SERIAL_FLASH_CNT_ADDR         (0x13FF0000U)
#define R_SERIAL_FLASH_DATA_WIDTH       (SPIBSC_4BIT)
#define R_SERIAL_FLASH_ADDR_MODE        (SPIBSC_OUTPUT_ADDR_32)
#define R_SERIAL_FLASH_WRITE_BYTE       (4)
#define R_SERIAL_FLASH_READ_BYTE        (4)
#endif

/******************************************************************************
Variable Externs
******************************************************************************/


/******************************************************************************
Functions Prototypes
******************************************************************************/
/* api function */
int32_t R_SPIBSC_EraseSector(uint32_t addr, uint32_t data_width, uint32_t addr_mode);
int32_t R_SPIBSC_ByteProgram(uint32_t addr, uint8_t *buf, int32_t size, uint32_t data_width, uint32_t addr_mode);
int32_t R_SPIBSC_ByteRead(uint32_t addr, uint8_t *buf, int32_t size, uint32_t data_width, uint32_t addr_mode);
int32_t R_SPIBSC_SpibscTransfer(st_spibsc_spimd_reg_t *regset);

/* User defined function */
int32_t userdef_sflash_write_enable(void);
int32_t userdef_sflash_busy_wait(uint32_t data_width);


void OutAddrMode_to_SPIMode(void);

#endif /* R_SERIAL_FLASH_API_H */


/* End of File */

/*----------------------------------------------------------------------
#|History of "r_serial_flash_api.h"
#|---------------------------------
#|* 2018/03/31	SPIBSC_SFLASH_TYPE==TYPE_MT25QLに対応(by T.Yokobayashi)
#|
*/
