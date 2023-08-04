/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 Time 1 demo
//***********************************************************************************************************
#include "ms51_16k_sdcc.h"


/* if define TIMER0_FSYS_DIV12, timer = (256-56)*12/16MHz = 150us */
/* if define TIMER0_FSYS, timer = (256-56)/16MHz = 12.5us */
#define TH1_INIT        56 
#define TL1_INIT        56

/************************************************************************************************************
*    TIMER 1 interrupt subroutine
************************************************************************************************************/
void Timer1_ISR (void) __interrupt (3)              //interrupt address is 0x000B
{
    PUSH_SFRS;
  
  
    P12 ^= 1;                                 // GPIO1 toggle when interrup

    POP_SFRS;
}

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{

    P12_PUSHPULL_MODE;;
    TIMER1_MODE2_ENABLE;
    TIMER1_FSYS_DIV12;
  
    TH1 = TH1_INIT;            //initial counter values 
    TL1 = TL1_INIT;    
   
    ENABLE_TIMER1_INTERRUPT;                                    //enable Timer1 interrupt
    ENABLE_GLOBAL_INTERRUPT;                       //enable interrupts
  
    set_TCON_TR1;                                  //Timer1 run

    while(1);
}

