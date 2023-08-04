/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: MS51 read UID demo
//***********************************************************************************************************
#include "ms51_8k_sdcc.h"

/* For printf code only. Disable this define to reduce code size. */
//#define print_function 

void main(void)
{
	unsigned char i;

	MODIFY_HIRC(HIRC_24);
	Enable_UART0_VCOM_printf_24M_115200();
	printf ("\n Test start ...");

	Read_UID();

  printf ("\n UID = ");
  for(i=0;i<12;i++)
  {
    printf (" 0x%hx",UIDBuffer[i]);
  }

  
  while(1);


}
