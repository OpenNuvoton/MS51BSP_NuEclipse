/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 read UCID demo
//***********************************************************************************************************
#include "ms51_16k_sdcc.h"


/***********************/
/* main loop           */
/***********************/ 
void main(void)
{
  unsigned char READ1;
  
/* Modify HIRC to 24MHz for UART printf function only */
  MODIFY_HIRC(HIRC_24);
  Enable_UART0_VCOM_printf_24M_115200();
  printf ("\n UCID = ");

  Read_UCID();
  printf ("\n UCID = ");
  for(READ1=0;READ1<12;READ1++)
  {
    printf (" 0x%hx",UCIDBuffer[READ1]);
  }

  while(1);


}
