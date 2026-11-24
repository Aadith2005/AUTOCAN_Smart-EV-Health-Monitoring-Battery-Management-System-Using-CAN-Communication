#include <LPC21XX.h>
#include<stdio.h>
#include <string.h>

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
u32 TDA;
u32 TDB;
}CAN;


void delay_ms(u32);
void CAN_INIT(void);
void CAN_TX(CAN);
float ADC_CONVERSION(void);

