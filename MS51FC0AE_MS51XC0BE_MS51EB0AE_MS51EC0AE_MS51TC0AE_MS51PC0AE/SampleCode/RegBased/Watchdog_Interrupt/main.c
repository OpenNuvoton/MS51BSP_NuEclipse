/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 Watchdog timer interrupt function demo                                              */
/************************************************************************************************************/
#include "ms51_32k_sdcc.h"


/************************************************************************************************************
*    WDT interrupt sub-routine
************************************************************************************************************/
void WDT_ISR (void)   __interrupt (10)
{
PUSH_SFRS;

  /* Config Enable WDT reset and not clear couter trig reset */
    WDT_COUNTER_CLEAR;                     /* Clear WDT counter */
    while(!(WDCON&=SET_BIT6));             /* Check for the WDT counter cleared */
    CLEAR_WDT_INTERRUPT_FLAG;
    P35 ^= 1;

POP_SFRS;
}

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
/* Note
  WDT timer base is LIRC 10Khz
*/
    P35_QUASI_MODE;  
/*--------------------------------------------------------
 * Notice:
 * WDT MUST enable in CONFIG 
 * only when WDT reset disable, WDT use as pure timer
 *-------------------------------------------------------- */
    WDT_TIMEOUT_800MS;                     /* Setting WDT time out */
    WDT_RUN_IN_POWERDOWN_ENABLE;           /* WDT run in POWER DOWM mode setting if needed */
    ENABLE_WDT_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;
    WDT_COUNTER_RUN;                       /* WDT start to run */
    WDT_COUNTER_CLEAR;                     /* Clear WDT counter */
    while(!(WDCON&=SET_BIT6));             /* Check for the WDT counter cleared */

    while (1)
    {
      set_PCON_PD;                         /* Keep in Power down mode excpet WDT interrupt */
    }

}
