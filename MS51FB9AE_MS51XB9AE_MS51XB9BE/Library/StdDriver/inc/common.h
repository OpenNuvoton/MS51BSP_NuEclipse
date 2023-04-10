#define  BOOT_APROM     0
#define  BOOT_LDROM     2

extern __bit BIT_TMP;
extern unsigned char __data SFRTEMP;
extern unsigned char Read_APROM_BYTE(const uint16_t __code *u16_addr_apread);
void Software_Reset(unsigned char u8Bootarea);
