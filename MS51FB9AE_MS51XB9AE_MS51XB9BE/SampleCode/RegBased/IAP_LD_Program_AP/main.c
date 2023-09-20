/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k_sdcc.h"

/************************************************************************************************************/
/* FUNCTION_PURPOSE: Main Loop                                                                              */
/* Before using this demo code, please remind below CONFOGs setting, thanks.                              */
/*                  CONFIG0.7 --> CBS=0                                                                     */
/*                  CONFIG1 = 0xFC, because this demo code size is 2495 Byte                                */
/************************************************************************************************************/
void main (void) 
{
    unsigned char i;

    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n Toggle P12 to low to start test ...");

    GPIO_LED_QUASI_MODE;
    while (GPIO_LED);

    for(i=0;i<128;i++)
      IAPDataBuf[i]=i;

    Erase_APROM(0x80,128);
    Erase_Verify_APROM(0x80,128);
    Program_APROM(0x80,128);
    Program_Verify_APROM(0x80,128);

    while(1);
}

