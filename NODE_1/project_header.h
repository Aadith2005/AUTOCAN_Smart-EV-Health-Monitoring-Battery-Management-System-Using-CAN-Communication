#include <LPC21XX.h>


//short name for datatypes
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned char u8;
typedef signed char s8;
typedef float f32;

typedef struct CAN_FRAME
{
u32 ID;
u32 RTR;
u32 DLC;
float TDA;
float TDB;
}CAN;


void delay_ms(u32);
void SPI0_INIT(void);
f32 Read_ADC_MCP3204(u8);
void CAN_INIT(void);
void CAN_TX(CAN);
float ADC_CONVERSION(void);

