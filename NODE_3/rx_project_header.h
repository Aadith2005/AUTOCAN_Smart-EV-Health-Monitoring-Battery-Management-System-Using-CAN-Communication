#include <LPC21XX.h>
#include<stdio.h>
#include<string.h> 

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

void UART_CONFIG(unsigned int);
void UART_TX(unsigned char);
unsigned char UART_RX(void);
void UART_STR(unsigned char*);
void UART_INTEGER(signed int);
void UART_FLOAT(float);
void UART_HEX(int);

void CAN_INIT(void);
void CAN_RX(CAN *);

