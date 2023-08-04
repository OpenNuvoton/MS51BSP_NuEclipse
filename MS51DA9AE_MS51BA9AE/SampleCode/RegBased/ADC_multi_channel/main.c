/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************/
/*  File Function: MS51 ADC multi channel input demo code                                                 */
/**********************************************************************************************************/
#include "ms51_8k_sdcc.h"

/* For printf code only. Disable this define to reduce code size. */
//#define print_function 

unsigned char __xdata ADCdataAIN5H, ADCdataAIN5L;
unsigned char __xdata ADCdataVBGH, ADCdataVBGL;

/*****************************************************************************/
/*The main C function.  Program execution starts                             */
/*here after stack initialization.                                           */
/*****************************************************************************/
void main (void) 
{

	MODIFY_HIRC(HIRC_24);
	Enable_UART0_VCOM_printf_24M_115200();
	printf ("\n Test start ...");
  
/*Enable channel 5 */ 
      ENABLE_ADC_CH5;
      ADCCON1|=0X30;            /* clock divider */
      ADCCON2|=0X0E;            /* AQT time */
      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;                                
      while(ADCF == 0);
      ADCdataAIN5H = ADCRH;
      ADCdataAIN5L = ADCRL;
      DISABLE_ADC;

      printf("\n ADC channel 5 =0x%hx", ADCdataAIN5H);


/*Enable Bandgap */     
      ENABLE_ADC_BANDGAP;
      ADCCON1|=0X30;            /* clock divider */
      ADCCON2|=0X0E;            /* AQT time */
      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;                                
      while(ADCF == 0);
      ADCdataVBGH = ADCRH;
      ADCdataVBGL = ADCRL;
      DISABLE_ADC;


      printf("\n ADC channel bandgap =0x%hx", ADCdataVBGH);

      
    while(1);  
}
