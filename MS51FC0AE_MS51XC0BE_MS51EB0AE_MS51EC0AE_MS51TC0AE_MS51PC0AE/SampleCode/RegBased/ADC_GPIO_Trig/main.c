/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: MS51 ADC trig by GPIO demo
//***********************************************************************************************************
#include "ms51_32k_sdcc.h"

BIT adcintflag;
/******************************************************************************
 * FUNCTION_PURPOSE: ADC interrupt Service Routine
 ******************************************************************************/
void ADC_ISR (void) __interrupt (11)
{
    PUSH_SFRS;
    clr_ADCCON0_ADCF;                               //clear ADC interrupt flag
    adcintflag =1;
    POP_SFRS;
}

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{

/* UART0 settting for printf function */
/* Only for printf function enabled */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n Test start ...");


/*---------------------------------------------------------------*/
/* ADC port trig initial setting toggle P0.4 to start ADC        */
/*---------------------------------------------------------------*/
    ENABLE_ADC_CH0;                              // Enable AIN0 P1.7 as ADC pin
	  ADC_ConvertTime(ADC_CH0,2,7);
    P04_INPUT_MODE;
    P04_FALLINGEDGE_TRIG_ADC;                      // P0.4 falling edge as adc start trig signal
/* Enable ADC interrupt */
    set_IE_EADC;                                  // Enable ADC interrupt (if use interrupt)

    ENABLE_GLOBAL_INTERRUPT;
/* Trig P04 falling edge to start adc, no need set ADCS bit*/
    while(1)
    {
    	if (adcintflag)
    	{
    	    printf ("\n ADCRH Value = 0x%hx",ADCRH);
    	    printf (" ADCRL Value = 0x%hx",ADCRL);// Wait ADC interrupt
    	    adcintflag = 0;
    	}
    }


}


