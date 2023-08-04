/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//**********************************************************************************************************/
//  File Function: MS51 ADC read bandgap to VDD demo code                                                  */
//**********************************************************************************************************/

#include "ms51_8k_sdcc.h"


//*****************  The Following is in define in Fucntion_define.h  ***************************
//****** Always include Function_define.h call the define you want, detail see main(void) *******
//***********************************************************************************************
float Bandgap_Voltage,VDD_Voltage,Bandgap_Value;      //please always use "double" mode for this
float bgvalue;
unsigned char i;

void READ_BANDGAP(void)
{
	UINT8 BandgapHigh,BandgapLow,BandgapMark;
  
    set_CHPCON_IAPEN;
    IAPCN = READ_UID;
    IAPAL = 0x0d;
    IAPAH = 0x00;
    set_IAPTRG_IAPGO;
    BandgapLow = IAPFD;
    BandgapMark = BandgapLow&0xF0;
    BandgapLow = BandgapLow&0x0F;
    IAPAL = 0x0C;
    IAPAH = 0x00;
    set_IAPTRG_IAPGO;
    BandgapHigh = IAPFD;
    Bandgap_Value = (BandgapHigh<<4)+BandgapLow;
    Bandgap_Voltage= Bandgap_Value*3/4;
    clr_CHPCON_IAPEN;
}

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
/* UART0 settting for printf function */
	MODIFY_HIRC(HIRC_24);
	Enable_UART0_VCOM_printf_24M_115200();
	printf ("\n Test start ...");
/*Read bandgap value */
    READ_BANDGAP();
/*Sampling bandgap ADC result */
    ENABLE_ADC_BANDGAP;
    ADCCON1|=0x30;            /* clock divider */
    ADCCON2|=0x0E;            /* AQT time */

    clr_ADCCON0_ADCF;
    set_ADCCON0_ADCS;                                
    while(ADCF == 0);

/* to convert VDD value */
    bgvalue = (ADCRH<<4) + ADCRL;
    VDD_Voltage = (0x1000/bgvalue)*Bandgap_Voltage;
/*printf result value */
    printf_fast_f ("\n BG Voltage = %f", Bandgap_Voltage);
    printf ("\ mV");
    printf_fast_f ("\n VDD voltage = %f", VDD_Voltage);
    printf ("\ mV");
  
    while(1);

}


