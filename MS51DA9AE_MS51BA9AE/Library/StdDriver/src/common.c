/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#include "ms51_8k_sdcc.h"

__bit BIT_TMP;
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
 * @brief       Software loop delay by HIRC, about 3ms
 * @param       None
 * @return      None
 * @details     None
 */
void _nopDelay_(void)
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
