/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_32k_sdcc.h"

BIT bodflag;
void BOD_ISR (void) __interrupt (8)           // Vector @  0x43
{
    clr_CHPCON_IAPEN; 
    clr_BODCON0_BOF;
    bodflag=1;
}

//----------------------------------------------------------------------------------------------//
void main (void)
{
/* As defaut all multi function define as GPIO */ 
  GPIO_LED_QUASI_MODE;
  bodflag =0;
  BOD_Open(Enable, VBOD_2_7, BOD_Reset_Disable);
  BOD_LowPower(LPBOD_Mode_3);
  BOD_Interrupt(Enable);
  ENABLE_GLOBAL_INTERRUPT;
  while(1)
  {
     P1=~P1;
     CALL_NOP;
     if (bodflag)
     {
         GPIO_LED ^= 1;
         bodflag = 0;
     }
  }
}



