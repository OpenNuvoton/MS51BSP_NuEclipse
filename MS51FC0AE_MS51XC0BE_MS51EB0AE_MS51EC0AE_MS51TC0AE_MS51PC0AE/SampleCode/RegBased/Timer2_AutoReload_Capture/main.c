/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 Timer 2 capture function demo                                                       */
//***********************************************************************************************************/
#include "ms51_32k_sdcc.h"

__sbit  captureflag;
/************************************************************************************************************/
/*    Capture interrupt subroutine                                                                   */
/************************************************************************************************************/
void Capture_ISR (void) __interrupt (12)
{
    PUSH_SFRS;
  
    clr_CAPCON0_CAPF0;                  /* clear capture0 interrupt flag  */
    clr_T2CON_TF2;
    captureflag = 1;

    POP_SFRS;
}
/************************************************************************************************************/
/*    Main function                                                                                         */
/************************************************************************************************************/
void main (void)
{
	MODIFY_HIRC(HIRC_24);
	Enable_UART0_VCOM_printf_24M_115200();
	printf ("\n Test start ...");

    P00_QUASI_MODE;
    TIMER2_CAP2_Capture_Mode;
    IC3_P00_CAP2_BOTHEDGE_CAPTURE;
      
    set_EIE_ECAP;                        //Enable Capture interrupt
    set_T2CON_TR2;                       //Trigger Timer2
    ENABLE_GLOBAL_INTERRUPT;

    while(!captureflag);
    SFRS = 0;
    printf ("\n capture high byte value = 0x%hx",C0H);
    printf ("\n low byte value = 0x%hx",C0L);

    while(1);
}
