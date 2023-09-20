/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************************/
/*  File Function: MS51 UART0 receive and transmit loop test                                               */
/***********************************************************************************************************/
#include "ms51_32k_sdcc.h"

void Serial_ISR(void) __interrupt (4)
{
    PUSH_SFRS;
    if (RI)
    {
        uart0_receive_flag = 1;
        uart0_receive_data = SBUF;
        clr_SCON_RI;                                         // Clear RI (Receive Interrupt).
    }

    if (TI)
    {
        if (!PRINTFG)
        {
            TI = 0;
        }
    }
    POP_SFRS;
}

/************************************************************************************************************/
/*  Main function                                                                                           */
/************************************************************************************************************/
 void main(void)
{
    P35_PUSHPULL_MODE;
/* Modify HIRC to 24MHz for UART baud rate */
    MODIFY_HIRC(HIRC_24);
    P06_QUASI_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_INTERRUPT;                                   /* Enable UART0 interrupt */
    ENABLE_GLOBAL_INTERRUPT;                                  /* Global interrupt enable */
  
/* while receive data from RXD, send this data to TXD */
  while(1)
  {
    if (uart0_receive_flag)
    {
      DISABLE_UART0_INTERRUPT;
      P35 ^= 1;
      UART_Send_Data(UART0,uart0_receive_data);
      uart0_receive_flag = 0;
      ENABLE_UART0_INTERRUPT;
    }
  }
}
