/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 Wakeup timer demo code with interrupt                                               */
/************************************************************************************************************/

#include "ms51_32k_sdcc.h"

__bit wktflag;

void WakeUp_Timer_ISR (void)   __interrupt (17)     //ISR for self wake-up timer
{
    PUSH_SFRS;

    wktflag =1;
    clr_WKCON_WKTF;                                   //clear interrupt flag

    POP_SFRS;
}


/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
   
    P35_PUSHPULL_MODE;
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n Test start ...");
//------------- ----------------------------------------
//  WKT initial   
//-----------------------------------------------------  
    SFRS = 0;
    WKCON = 0x02;                     //timer base 10k, Pre-scale = 1/16
    SFRS = 2;
    RWKH = 0xF0;
    SFRS = 0;
    RWKL = 0X00;                      //  if prescale is 0x00, never set RWK = 0xff
    ENABLE_WKT_INTERRUPT;             // enable WKT interrupt
    ENABLE_GLOBAL_INTERRUPT;
    set_WKCON_WKTR;                   // Wake-up timer run

    while(1)
    {
    	if (wktflag)
    	{
    		clr_WKCON_WKTR;
    	    printf ("\n WKT interrupt!");
    	    wktflag = 0;
    	    set_WKCON_WKTR;
    	}
      P35 ^= 1;
      Timer0_Delay(24000000,200,1000);
    }
}

