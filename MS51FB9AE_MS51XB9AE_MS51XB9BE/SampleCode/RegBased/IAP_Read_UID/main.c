/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: MS51 read UID demo
//***********************************************************************************************************
#include "ms51_16k_sdcc.h"


void main(void)
{
  unsigned char READ1;
  ALL_GPIO_QUASI_MODE;

/* Modify HIRC to 24MHz for UART printf function only */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();

  Read_UID();
  printf ("\n UID = ");
  for(READ1=0;READ1<12;READ1++)
  {
    printf (" 0x%hx",UIDBuffer[READ1]);
  }
  
  while(1);


}
