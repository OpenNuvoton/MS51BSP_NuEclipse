/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_32k_sdcc.h"

__at 0x88          unsigned char temp;
__idata __at  0x88 unsigned char itemp;
__xdata __at  0x88 unsigned char xtemp;

//----------------------------------------------------------------------------------------------//
void main (void)
{
  ALL_GPIO_QUASI_MODE;

  while(1)
  {
    P1 = 0xff;
    P35 ^=1;
    Timer0_Delay(16000000,200,1000);
    P1=0x00;
    Timer0_Delay(16000000,200,1000);
    if (!(P3&SET_BIT0))
    	P35 ^= 1;
  }
}



