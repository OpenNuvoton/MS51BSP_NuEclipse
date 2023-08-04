
//extern unsigned char Read_SPROM_BYTE(unsigned char *u8_addr);
extern unsigned char Read_SPROM_BYTE(const uint8_t __code *u8_addr);
void Write_SPROM_DATAFLASH_ARRAY(unsigned char u8_addr, unsigned char *pDat, unsigned int num);
void Read_SPROM_DATAFLASH_ARRAY(unsigned int u16_addr, unsigned char *pDat, unsigned int num);

