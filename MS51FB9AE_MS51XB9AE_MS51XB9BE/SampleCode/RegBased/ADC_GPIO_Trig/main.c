/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 ADC trig by GPIO demo
//***********************************************************************************************************
#include "ms51_16k_sdcc.h"


/******************************************************************************
 * FUNCTION_PURPOSE: ADC interrupt Service Routine
 ******************************************************************************/
void ADC_ISR (void) __interrupt (11)
{
//    _push_(SFRS);
  
    clr_ADCCON0_ADCF;                               //clear ADC interrupt flag
    printf ("\n int ADCRH Value = 0x%hx",ADCRH);

//    _pop_(SFRS);
}

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
	unsigned char temp;

    ALL_GPIO_QUASI_MODE;

  /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_166);
    P06_QUASI_MODE;
        UART_Open(16600000,UART0_Timer1,115200);
        ENABLE_UART0_PRINTF;
    temp = 0x69;
    PWMPH = 0x55;
    printf ("\n int PWMPH Value = 0x%hx",PWMPH);
    printf ("\n int temp Value = 0x%hx",temp);
/*---------------------------------------------------------------
  ADC port trig initial setting toggle P0.4 to start ADC 
----------------------------------------------------------------*/
    ENABLE_ADC_AIN0;                              // Enable AIN0 P1.7 as ADC pin
    P04_QUASI_MODE;
    P04_FALLINGEDGE_TRIG_ADC;                     // P0.4 falling edge as adc start trig signal
/* Enable ADC interrupt */
    set_IE_EADC;                                  // Enable ADC interrupt (if use interrupt)
    ENABLE_GLOBAL_INTERRUPT;
/* Trig P04 falling edge to start adc, no need set ADCS bit*/
    while(1);                                     // Wait ADC interrupt
}


