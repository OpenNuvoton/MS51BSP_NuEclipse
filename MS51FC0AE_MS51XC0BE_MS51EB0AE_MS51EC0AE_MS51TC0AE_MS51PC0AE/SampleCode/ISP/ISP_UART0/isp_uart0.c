/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: ML51 UART0 ISP subroutine
//***********************************************************************************************************
#include "ms51_32k_sdcc.h"
#include "isp_uart0.h"

__xdata volatile uint8_t uart_rcvbuf[64];
__xdata volatile uint8_t uart_txbuf[64];
__data volatile uint8_t bufhead;
__data volatile uint16_t flash_address;
__data volatile uint16_t AP_size;
__data volatile uint8_t g_timer1Counter;
__data volatile uint8_t count;
__data volatile uint16_t g_timer0Counter;
__data volatile uint32_t g_checksum;
__data volatile uint32_t g_totalchecksum;
__bit volatile bUartDataReady;
__bit volatile g_timer0Over;
__bit volatile g_timer1Over;
__bit volatile g_programflag;

unsigned char PID_highB, PID_lowB, DID_highB, DID_lowB, CONF0, CONF1, CONF2, CONF4;
unsigned char recv_CONF0, recv_CONF1, recv_CONF2, recv_CONF4;

void MODIFY_HIRC_24(void)
{
    unsigned char __data hircmap0, hircmap1;
    /* Check if power on reset, modify HIRC */
//    set_CHPCON_IAPEN;
    IAPAH = 0x00;
    IAPAL = 0x38;
    IAPCN = READ_UID;
    set_IAPTRG_IAPGO;
    hircmap0 = IAPFD;
    IAPAL = 0x39;
    set_IAPTRG_IAPGO;
    hircmap1 = IAPFD;

    TA = 0XAA;
    TA = 0X55;
    RCTRIM0 = hircmap0;
    TA = 0XAA;
    TA = 0X55;
    RCTRIM1 = hircmap1;
//    clr_CHPCON_IAPEN;
}

void MODIFY_HIRC_16(void)
{
    unsigned char __data hircmap0, hircmap1;
//    set_CHPCON_IAPEN;
    IAPAH = 0x00;
    IAPAL = 0x30;
    IAPCN = READ_UID;
    set_IAPTRG_IAPGO;
    hircmap0 = IAPFD;
    IAPAL = 0x31;
    set_IAPTRG_IAPGO;
    hircmap1 = IAPFD;

    TA = 0xAA;
    TA = 0x55;
    RCTRIM0 = hircmap0;
    TA = 0xAA;
    TA = 0x55;
    RCTRIM1 = hircmap1;
}

void READ_ID(void)
{
//    set_CHPCON_IAPEN;
    IAPCN = READ_DID;
    IAPAH = 0x00;
    IAPAL = 0x00;
    set_IAPTRG_IAPGO;
    DID_lowB = IAPFD;
    IAPAL = 0x01;
    set_IAPTRG_IAPGO;
    DID_highB = IAPFD;
    IAPAL = 0x02;
    set_IAPTRG_IAPGO;
    PID_lowB = IAPFD;
    IAPAL = 0x03;
    set_IAPTRG_IAPGO;
    PID_highB = IAPFD;
}
void READ_CONFIG(void)
{
    IAPCN = BYTE_READ_CONFIG;
    IAPAL = 0x00;
    IAPAH = 0x00;
    set_IAPTRG_IAPGO;
    CONF0 = IAPFD;
    IAPAL = 0x01;
    set_IAPTRG_IAPGO;
    CONF1 = IAPFD;
    IAPAL = 0x02;
    set_IAPTRG_IAPGO;
    CONF2 = IAPFD;
    IAPAL = 0x04;
    set_IAPTRG_IAPGO;
    CONF4 = IAPFD;
//    clr_CHPCON_IAPEN;
}

void TM0_ini(void)
{
    TH0 = TL0 = 0; //interrupt timer 140us
    set_TCON_TR0;      //Start timer0
    set_IPH_PSH;       // Serial port 0 interrupt level2
    set_IE_ET0;
}


void UART0_ini_115200_24MHz(void)
{
    P06_QUASI_MODE;

    SCON = 0x50;            /*UART0 Mode1,REN=1,TI=1*/
    set_PCON_SMOD;          /*UART0 Double Rate Enable*/
    T3CON &= 0xF8;          /*T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1)*/
    set_T3CON_BRCK;         /*UART0 baud rate clock source = Timer3*/
    RH3    = 0xFF;          /*HIBYTE(65536 - 13)*/
    RL3    = 0xF3;          /*LOBYTE(65536 - 13)*/
    set_T3CON_TR3;          /*Trigger Timer3*/

    ES = 1;
    EA = 1;
}


void Package_checksum(void)
{
    g_checksum = 0;

    for (count = 0; count < 64; count++)
    {
        g_checksum = g_checksum + uart_rcvbuf[count];
    }

    uart_txbuf[0] = g_checksum & 0xff;
    uart_txbuf[1] = (g_checksum >> 8) & 0xff;
    uart_txbuf[4] = uart_rcvbuf[4] + 1;
    uart_txbuf[5] = uart_rcvbuf[5];

    if (uart_txbuf[4] == 0x00)
        uart_txbuf[5]++;

}


void Send_64byte_To_UART0(void)
{
    SFRS = 0;
    for (count = 0; count < 64; count++)
    {
        TI = 0;
        SBUF = uart_txbuf[count];
        while (TI == 0);
        set_WDCON_WDCLR;
    }
}

