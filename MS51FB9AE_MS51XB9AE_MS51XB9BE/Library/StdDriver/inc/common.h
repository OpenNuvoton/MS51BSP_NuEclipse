#define  GPIO_LED                P12               /* NuMaker LED define */
#define  GPIO_LED_QUASI_MODE     P12_QUASI_MODE
#define  GPIO_PRINTF             P06

#define  BOOT_APROM     0
#define  BOOT_LDROM     2

extern BIT BIT_TMP;
extern unsigned char __data  TA_REG_TMP,BYTE_TMP,SFRS_TMP;

extern unsigned char Read_APROM_BYTE(const uint16_t __code *u16_addr);
void Software_Reset(unsigned char u8Bootarea);
void PowerDown_Mode(unsigned char PDStatus);
void Idle_Mode(unsigned char IdleStatus);
void _delay_(void);
