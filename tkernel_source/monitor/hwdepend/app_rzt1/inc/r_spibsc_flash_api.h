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
* Copyright (C) 2017 Renesas Electronics Corporation. All rights reserved.
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
*              : 01.07.2015 1.1      First Release
*              : 30.11.2015 1.2      Second Release
*                                     - No modification
*              : 31.03.2017 1.3      Third Release
*                                     - Loader API is changed to local function
*******************************************************************************/
#ifndef R_SPIBSC_FLASH_API_H
#define R_SPIBSC_FLASH_API_H


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_spibsc_ioset_api.h"


/******************************************************************************
Typedef definitions
******************************************************************************/


/******************************************************************************
Macro definitions
******************************************************************************/


/******************************************************************************
Variable Externs
******************************************************************************/


/******************************************************************************
Functions Prototypes
******************************************************************************/
/* api function */
int32_t sflash_erase_sector(uint32_t addr, uint32_t data_width, uint32_t addr_mode);
int32_t sflash_byte_program(uint32_t addr, uint8_t *buf, int32_t size, uint32_t data_width, uint32_t addr_mode);
int32_t sflash_spibsc_transfer(st_spibsc_spimd_reg_t *regset);
int32_t sflash_ctrl_protect(uint32_t req, uint32_t data_width);


/* User defined function */
int32_t Userdef_SFLASH_Set_Mode(uint32_t data_width, uint32_t addr_mode);
int32_t Userdef_SFLASH_Write_Enable(void);
int32_t Userdef_SFLASH_Busy_Wait(uint32_t data_width);
int32_t Userdef_SFLASH_Ctrl_Protect(uint32_t req, uint32_t data_width);


#endif /* R_SPIBSC_FLASH_API_H */


/* End of File */
