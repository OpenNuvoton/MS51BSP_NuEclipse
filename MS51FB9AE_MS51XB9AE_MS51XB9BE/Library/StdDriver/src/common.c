/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k_sdcc.h"

BIT BIT_TMP;
unsigned char __data  TA_REG_TMP,BYTE_TMP,SFRS_TMP;

/**
 * @brief       Read Dataflash
 * @param       Dataflash start address
 * @return      Dataflash Value
 * @details     None
**/
unsigned char Read_APROM_BYTE(const uint16_t __code *u16_addr)
{
    unsigned char rdata;
    rdata = *u16_addr >> 8;
    return rdata;
}

/**
 * @brief       Software reset API
 * @param       Run in APROM/LDROM after reset
 *                       - \ref BOOT_APROM: Run in APROM after reset .
 *                       - \ref BOOT_LDROM: Run in LDROM after reset.
 * @return      None
 * @details     None
 */
void Software_Reset(unsigned char u8Bootarea)
{
    unsigned char boottemp;
    boottemp = (0x80|u8Bootarea);
    TA = 0xAA;
    TA = 0x55;
    CHPCON = boottemp;                   //software reset enable
}

/**
 * @brief       MCU power down mode enable API
 * @param       Enable power down mode
 *                       - \ref ENABLE: Run into power down mode .
 * @return      None
 * @details     None
 */
void PowerDown_Mode(unsigned char PDStatus)
{
    if (PDStatus)
    {
       ENABLE_POWERDOWN_MODE;
       CALL_NOP;
       CALL_NOP;
    }
}

/**
 * @brief       MCU idle mode enable API
 * @param       Enable idle mode
 *                       - \ref ENABLE: Run into idle mode .
 * @return      None
 * @details     None
 */
void Idle_Mode(unsigned char IdleStatus)
{
    if (IdleStatus)
    {
       ENABLE_IDLE_MODE;
       CALL_NOP;
       CALL_NOP;
    }
}


/**
 * @brief       Software loop delay by HIRC, about 3ms
 * @param       None
 * @return      None
 * @details     None
 */
void _delay_(void)
{
  unsigned char t1,t2;

    for (t2=0;t2<0x1A;t2++)
    {
       for (t1=0;t1<0x7f;t1++)
       {
          CALL_NOP;
       }
    }
}
