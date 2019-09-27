/*
 *----------------------------------------------------------------------
 *
 *    T-Kernel Software Library
 *
 *----------------------------------------------------------------------
 */

/*
 *	@(#)_type_rzt_def.h () 2019/09/18
 */

#ifndef _TYPE_RZT_DEF_
#define _TYPE_RZT_DEF_

/*******************************************************************************
Includes <System Includes> , "Project Includes"
*******************************************************************************/

/*******************************************************************************
Macro definitions
*******************************************************************************/

#ifndef TYPE_RZT				/* Default is RSK board */
#define	TYPE_RZT				(0)
#endif


/* Serial Flash ROM Type Define */
#define	TYPE_MX25L				(0)		/* MXIC,MX25L51245G(RSK) */
#define TYPE_MT25QL				(1)		/* Micron,MT25QL128 */

/* SD-RAM Type Define */
#define TYPE_MD56V62161M		(1)		/* LAPIS,MD56V62161M,64Mbit */
#define TYPE_MT48LC16M16A2		(2)		/* MICRON,MT48LC16M16A2,256Mbit */


#if (TYPE_RZT == 1)
#define	BOARD_RZT1_SCPZ			1		/*--- SCPZ-1 board define ---*/
#define	SPIBSC_SFLASH_TYPE		TYPE_MT25QL
#define	__MT25QL_BUS_WITDH		(1)
#define	BSC_SDRAM_TYPE			TYPE_MT48LC16M16A2		/* SCPZ-1 */
//#define	BSC_SDRAM_TYPE			TYPE_MD56V62161M		/* RZT-1*/
#else
#define	BOARD_RZT1_RSK			1		/*--- RSK board define ---*/
#define	SPIBSC_SFLASH_TYPE		TYPE_MX25L
#define	BSC_SDRAM_TYPE			(0)
#endif


/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/

#endif	/* #ifndef _TYPE_RZT_DEF_ */

/* End of File */

/*----------------------------------------------------------------------
#|History of "_type_rzt_def.c"
#|----------------------------
#|* 2018/03/30	New created.(By T.Yokobayashi)
#|
*/
