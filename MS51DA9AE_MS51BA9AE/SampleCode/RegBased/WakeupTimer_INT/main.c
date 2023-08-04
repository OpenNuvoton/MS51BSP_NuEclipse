/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/************************************************************************************************************/
/*  File Function: MS51 Wakeup timer demo code with interrupt                                               */
/************************************************************************************************************/

#include "ms51_8k_sdcc.h"

__bit WKTINTFG;

void WakeUp_Timer_ISR (void)   __interrupt (17)     //ISR for self wake-up timer
{
    PUSH_SFRS;

    WKTINTFG = 1;
    clr_WKTF;                                   //clear interrupt flag

    POP_SFRS;
}


/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
   

    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n WKT test start ...");

    /*  WKT initial  */
        WKCON = 0x04;                     //timer base 10k, Pre-scale = 1/16
        RWK = 0xEF;                       //  if prescale is 0x00, never set RWK = 0xff
        RWK = 0x00;
        ENABLE_WKT_INTERRUPT;             // enable WKT interrupt
        ENABLE_GLOBAL_INTERRUPT;
        set_WKCON_WKTR;                   // Wake-up timer run


        P17_PUSHPULL_MODE;

        while(1)
        {
        	if (WKTINTFG)
        	{
        		printf ("\n WKT interrupt! Clear flag.");
        		WKTINTFG = 0 ;
        		P17 ^=1;
        	}
        }
}

