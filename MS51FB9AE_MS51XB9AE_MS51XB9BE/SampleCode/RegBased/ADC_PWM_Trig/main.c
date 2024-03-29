/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 ADC PWM trig convert demo code
//***********************************************************************************************************
#include "ms51_16k_sdcc.h"

/******************************************************************************
 * FUNCTION_PURPOSE: ADC interrupt Service Routine
 ******************************************************************************/
void ADC_ISR (void) __interrupt (11)
{
	PUSH_SFRS;

    clr_ADCCON0_ADCF;                       // Clear ADC interrupt flag
    P30 ^= 1;                                // Check the P3.0 toggle at falling edge of PWM

    POP_SFRS
}

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
    ALL_GPIO_QUASI_MODE;
/* Initial UART0 for printf */

/*-------------------------------------------------
  ADC trig initial setting
  Please modify #if value to open diffent type
--------------------------------------------------*/
#if 1
// By PWM falling edge
    PWM0_P12_OUTPUT_ENABLE;        
    ENABLE_ADC_AIN0;                            // Enable AIN0 P1.7 as ADC input
    PWM0_FALLINGEDGE_TRIG_ADC;  
#endif    
#if 0
// By PWM rising edge
    PWM0_P12_OUTPUT_ENABLE;        
    ENABLE_ADC_AIN0;                            // Enable AIN0 P1.7 as ADC input
    PWM0_RISINGEDGE_TRIG_ADC;
#endif    
#if 0
// By PWM central point
    PWM0_P12_OUTPUT_ENABLE;        
    ENABLE_ADC_AIN0;                            // Enable AIN0 P1.7 as ADC input
    PWM_CENTER_TYPE;
    PWM0_CENTRAL_TRIG_ADC;  
#endif  
#if 0
// By PWM end point
    PWM0_P12_OUTPUT_ENABLE;        
    ENABLE_ADC_AIN0;                            // Enable AIN0 P1.7 as ADC input
    PWM_CENTER_TYPE;
    PWM0_END_TRIG_ADC;
#endif  
  
// Setting PWM value
    PWMPH = 0x07;                                //Setting PWM value          
    PWMPL = 0xFF;
    PWM0H = 0x02;
    PWM0L = 0xFF;
    set_PWMCON0_LOAD;                                    // PWM run
    set_PWMCON0_PWMRUN;
// Setting ADC
    set_IE_EADC;                                    // Enable ADC interrupt (if use interrupt)
    ENABLE_GLOBAL_INTERRUPT;  
    while(1);

}


