/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/************************************************************************************************************/
/*  File Function: MS51 ADC / Bandgap input demo code                                                       */
/************************************************************************************************************/
#include "ms51_8k_sdcc.h"

/************************************************************************************************************/
/*   PWM interrupt subroutine                                                                               */
/************************************************************************************************************/
void PWM_ISR (void) __interrupt (13)
{
    PUSH_SFRS;
  
    clr_PWMCON0_PWMF;               // clear PWM interrupt flag

    POP_SFRS;
}	

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main(void)
{
    P05_PUSHPULL_MODE;
/**********************************************************************
  PWM frequency = Fpwm/((PWMPH,PWMPL) + 1) <Fpwm = Fsys/PWM_CLOCK_DIV> 
                = (16MHz/8)/(0x3FF + 1)
                = 2.7KHz
***********************************************************************/
    ENABLE_PWM0_CH2_P05_OUTPUT;
    ENABLE_PWM0_FALLING_INT;          /*Setting Interrupt happen when PWM0 falling signal */
    ENABLE_PWM0_CH2_INT;    

    PWM0_CLOCK_DIV_8;
    PWMPH = 0x03;                     /*Setting PWM period  */
    PWMPL = 0xFF;
    PWM2H = 0x0;                      /*PWM0 high duty = 1/2 PWM period */
    PWM2L = 0xFF;  

    set_EIE_EPWM;                     /*Enable PWM interrupt  */
    ENABLE_GLOBAL_INTERRUPT;
    set_PWMCON0_LOAD;
    set_PWMCON0_PWMRUN;
    while(1);
}
