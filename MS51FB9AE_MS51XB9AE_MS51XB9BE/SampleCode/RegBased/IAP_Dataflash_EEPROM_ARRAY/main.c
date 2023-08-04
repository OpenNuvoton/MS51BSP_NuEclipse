/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


#include "ms51_16k_sdcc.h"

struct
{
  unsigned int a;
  unsigned long b;
  unsigned char  c;
  
}StructData;

unsigned char ArrayData[50];
unsigned char i;

/**
 * @brief       IAP program dataflash as EEPROM
 * @param       None
 * @return      None
 * @details     define dataflash need be modify address and value,
 */

void main (void) 
{
    unsigned int system16highsite;
  
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n Toggle P12 to low to start...");

  /*loop here while P46 = 1; */  
    P12_QUASI_MODE;
    while(P12);


/** IAP program APROM as EEPROM way
   * include eeprom.c in Library       */ 
 
    Write_DATAFLASH_BYTE (0x3882,0x34);

    for(i=0;i<50;i++)
    {
      ArrayData[i]=i;
    }

     StructData.a=0xA1A2;
     StructData.b=0xA3A4A5A6;
     StructData.c=0xA7;
  
    Write_DATAFLASH_ARRAY(0x38E0,ArrayData,50);//write 50 bytes
    Write_DATAFLASH_ARRAY(0x38FE,(unsigned char *)&StructData,sizeof(StructData));//write structure
  
  
/*call read byte */
    system16highsite = ((Read_APROM_BYTE((uint16_t __code*)0x38FD)<<8)+Read_APROM_BYTE((uint16_t __code*)0x38FE));
	printf ("\n system16highsite = 0x%X", system16highsite);

	while(1);
}



