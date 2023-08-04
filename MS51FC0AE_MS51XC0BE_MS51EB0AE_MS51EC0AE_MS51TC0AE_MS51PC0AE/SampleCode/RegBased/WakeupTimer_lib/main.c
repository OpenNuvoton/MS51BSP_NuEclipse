/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2022 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/************************************************************************************************************/
/*  File Function: MS51 Wakeup timer demo code with interrupt with lib                                      */
/************************************************************************************************************/

#include "ms51_32k_sdcc.h"

__bit wktflag;

void WKT_ISR (void) __interrupt (17)            /* Vector @  0x8B  */
{
    PUSH_SFRS;
    wktflag = 1;
    clr_WKCON_WKTF;
    POP_SFRS;
}


void main (void)
{
    P35_PUSHPULL_MODE;
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();

    printf ("\n Test start ...");
    printf ("\n");
/**----------------------------------------------------------------------------
 *  Note: Since the divider limiation. All value define is approximate value  
 *-----------------------------------------------------------------------------*/
//    WKT_AutoReload_Interrupt_Initial_MS(200);     /* WKT delay 200 ms */
    WKT_AutoReload_Interrupt_Initial_S(3);      /* WKT delay 3s */
    ENABLE_GLOBAL_INTERRUPT;

    while(1)
    {
      while (!wktflag);
      SFRS = 0; printf (" WKT interrupt! \n");
      wktflag = 0;
      set_PCON_PD;
      CALL_NOP;
      CALL_NOP;
    }

}
