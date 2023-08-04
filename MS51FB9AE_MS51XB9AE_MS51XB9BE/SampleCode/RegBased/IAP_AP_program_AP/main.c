/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 IAP erase / program / read verify demo code
//***********************************************************************************************************
#include "ms51_16k_sdcc.h"

//---------------------------------------------------------------
// Following define by customer
// Please confirm the start addresss not over your code size
//---------------------------------------------------------------
#define     DATA_SIZE           128
#define     DATA_START_ADDR     0x3800 


//-----------------------------------------------------------------------------------------------------------
void main (void) 
{
    unsigned char i,temp;

    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();

    printf ("\n Toggle P12 to low to start test ...");
    P12_INPUT_MODE;

    for(i=0;i<128;i++)
       IAPDataBuf[i] =  i;
       
    while(P12);
    Erase_APROM(DATA_START_ADDR,128);
    Erase_Verify_APROM(DATA_START_ADDR,128);
    Program_APROM(DATA_START_ADDR,128);
    Program_Verify_APROM(DATA_START_ADDR,128);

    temp = Read_APROM_BYTE ((uint16_t __code *)(DATA_START_ADDR+0x0A));

    printf ("\n Read out Value = 0x%hx", temp);

    while(1);
}
//-----------------------------------------------------------------------------------------------------------
