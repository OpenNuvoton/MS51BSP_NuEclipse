/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: MS51 power down code for test power down current, BOD disabled.
//***********************************************************************************************************
#include "ms51_32k_sdcc.h"


void main (void) 
{
  unsigned char i;
/*Quasi mode better for power down power comsuption */  
    ALL_GPIO_QUASI_MODE;
/* clock only for reference, real chip please don't output clock*/  
    set_CKCON_CLOEN;
    CKDIV=0x50;
/*MUST DISABLE BOD to low power */
    DISABLE_BOD;              //BOD enable power down current please check datasheet DC charactor.

    while(P01);
    CKDIV = 0;
    for (i=0;i<0x05;i++)
    {
      P35 ^= 1;
      Timer0_Delay(16000000,200,1000);
    }

    P0=0;
    P1=0;
    P2=0;
    P3=0;
/* Real into power down mode */
    set_PCON_PD;
    while(1);  
  
}



