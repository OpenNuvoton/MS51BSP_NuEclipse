/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k_sdcc.h"


/************************************************************************************************************/
/* FUNCTION_PURPOSE: define IAP start address                                                               */
/************************************************************************************************************/
#define     DATA_START_ADDR     0x0000           

/************************************************************************************************************/
/* FUNCTION_PURPOSE: ADC interrupt Service Routine                                                          */
/************************************************************************************************************/

void main (void) 
{
    unsigned char i;
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n Toggle P12 to low to start test ...");

    GPIO_LED_QUASI_MODE;
    
    for (i=0;i<128;i++)
        IAPDataBuf[i]=i;

    while(GPIO_LED);

    Erase_LDROM(DATA_START_ADDR,128);
    Erase_Verify_LDROM(DATA_START_ADDR,128);
    Program_LDROM(DATA_START_ADDR,128);
    Program_Verify_LDROM(DATA_START_ADDR,128);

    while(1);
}
//-----------------------------------------------------------------------------------------------------------
