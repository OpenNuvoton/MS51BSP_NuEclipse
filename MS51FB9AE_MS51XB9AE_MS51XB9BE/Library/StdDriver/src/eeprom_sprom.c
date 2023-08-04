/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2023 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#include "ms51_16k_sdcc.h"

unsigned char __xdata sppage_buffer[127];

/**
 * @brief       Read Dataflash
 * @param       Dataflash start address
 * @return      Dataflash Value
 * @details     None
 */
 unsigned char Read_SPROM_BYTE(const uint8_t __code *u8_addr)
{
    unsigned char rdata;
    set_IAPUEN_SPMEN;
    rdata = *(0xFF80+u8_addr);
    return rdata;
}

//-------------------------------------------------------------------------
void WriteDataToSPOnePage(unsigned char u8_addr, unsigned char *pDat, unsigned int num)
{
    unsigned char i;
    unsigned char __code *pCode;
    unsigned char __xdata xd_tmp[127];

    pCode = (unsigned char __code *)u8_addr;
    for(i=0;i<127;i++)
    {
      xd_tmp[i] = Read_SPROM_BYTE((uint8_t __code *)i);
    }
    for(i=0;i<num;i++)
    {
      xd_tmp[u8_addr+i] = pDat[i];
    }

    set_CHPCON_IAPEN;
    set_IAPUEN_SPMEN;
    set_IAPUEN_SPUEN;

      IAPCN = PAGE_ERASE_SPROM;
      IAPAL = 0x80;
      IAPAH = 0x01;

      IAPFD = 0xFF;
      set_IAPTRG_IAPGO; 
      IAPCN =BYTE_PROGRAM_SPROM;
      for(i=0;i<127;i++)
      {
        IAPFD = xd_tmp[i];
        set_IAPTRG_IAPGO;
        IAPAL++;
      }
      for(i=0;i<127;i++)
      {
        if(pCode[i]!=xd_tmp[i])break;
      }

    clr_IAPUEN_SPUEN;
    clr_CHPCON_IAPEN;
}

void Write_SPROM_DATAFLASH_ARRAY(unsigned char u8_addr, unsigned char *pDat, unsigned int num)
{
      WriteDataToSPOnePage(u8_addr,pDat,num);
}

//-------------------------------------------------------------------------
void Read_SPROM_DATAFLASH_ARRAY(unsigned int u8_addr, unsigned char *pDat, unsigned int num)
{
    unsigned int i;

    set_IAPUEN_SPMEN;
    for (i = 0; i < num; i++)
        pDat[i] = *(unsigned char __code *)(u8_addr+0xFF80 + i);
}

