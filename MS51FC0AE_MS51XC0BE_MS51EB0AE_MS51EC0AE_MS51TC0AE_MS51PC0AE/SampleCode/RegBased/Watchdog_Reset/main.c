/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_32k_sdcc.h"

/************************************************************************************************************/
/* FUNCTION_PURPOSE: Main Loop                                                                              */
/************************************************************************************************************/
void main (void)
{
    uint8_t   ct;

    WDT_Clear();
    WDT_Open(1024);

    GPIO_LED_QUASI_MODE;
/* Note WDT timer base is LIRC 10Khz*/
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf("\n\r  Test start MCU reset ");
    WDT_Clear();

    Read_CONFIG();
    SFRS = 0;
    printf ("\n\r Now config value is :   ");
    for(ct=0;ct<5;ct++)
    {
      SFRS = 0;
      printf ("\r 0x%bX", IAPCFBuf[ct]);
      WDT_Clear();
    }
    if (IAPCFBuf[4] != 0xFF)
    {
      SFRS = 0;
      printf("\n\r  WDT Reset enabled in CONFIG ");
      WDT_Clear();
    }
    else
    {
      SFRS = 0;
      printf("\n\r  Please ENABLE WDT RESET in CONFIG  (Options => Debug => Setting )!!! ");
      WDT_Clear();
    }


    printf ("\n\r ");
    WDT_Clear();

    while (GPIO_LED)
    {
      printf("\n\r  P12 connect to VDD, WDT not reset ");
      WDT_Clear();
    }
    while(1);

}
