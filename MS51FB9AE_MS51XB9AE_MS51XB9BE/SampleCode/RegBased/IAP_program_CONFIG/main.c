/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 IAP program LDROM demo code
//***********************************************************************************************************
#include "ms51_16k_sdcc.h"


/*---------------------------------------------------------------
 * Try to avoid modify CONFIG in the program
 * NEVER modify config immediately after RESET
//---------------------------------------------------------------*/

void main (void) 
{
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n Use ICP programmer to define CONFIG is better choice.");
    printf ("\n Avoid reprogram CONFIG which can increase the stability of MCU operation.");
    printf ("\n MCU must be RESET after modified CONFGI value to take effect!");

    P12_QUASI_MODE;
    P12 = 1;
    while(P12);

    if(PCON&SET_BIT4)        /* Check with power on flag. Only the first power on check with CONFIG */
    {
       Modify_CONFIG(0xEF,0xFF,0x6B,0xFF,0xFF);
       PCON&=CLR_BIT4;      /* Clear power on flag to avoid software reset modify CONFIG again. */
    }

    while(1);
}
//-----------------------------------------------------------------------------------------------------------
