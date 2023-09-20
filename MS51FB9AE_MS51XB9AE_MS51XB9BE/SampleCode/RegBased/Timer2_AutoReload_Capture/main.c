/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 Timer 2 capture function demo                                                       */
//***********************************************************************************************************/
#include "ms51_16k_sdcc.h"

/************************************************************************************************************/
/*    Capture interrupt subroutine                                                                   */
/************************************************************************************************************/
void Capture_ISR (void) __interrupt (12)
{
    PUSH_SFRS;
  
    clr_CAPCON0_CAPF0;                  /* clear capture0 interrupt flag  */
    P1 = C0L;                            /* For capture mode CxL/CxH with data capture from I/O pin*/
    P2 = C0H;                            
    clr_T2CON_TF2;

    POP_SFRS;
}
/************************************************************************************************************/
/*    Main function                                                                                         */
/************************************************************************************************************/
void main (void)
{
	MODIFY_HIRC(HIRC_24);

    P00_QUASI_MODE;
    P00 = 1;

    TIMER2_CAP2_Capture_Mode;
    IC3_P00_CAP3_BOTHEDGE_CAPTURE;
      
    ENABLE_CAPTURE_INTERRUPT;                        //Enable Capture interrupt
    ENABLE_GLOBAL_INTERRUPT;
    set_T2CON_TR2;                       //Triger Timer2


    while(1);
}
