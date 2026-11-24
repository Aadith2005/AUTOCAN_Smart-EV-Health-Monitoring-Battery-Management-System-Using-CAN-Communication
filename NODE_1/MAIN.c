#include "project_header.h"
#include "delay_ms.c"
#include "cantx_driver.c"
#include "spi.c"
#include "adc.c"
int V;
float C=0.0f;

int main()
{

CAN P;

PINSEL1|=0X05000000;

CAN_INIT();
SPI0_INIT();

P.ID=0x101;
P.RTR=0;
P.DLC=8;


while(1){
V=ADC_CONVERSION();
C=Read_ADC_MCP3204(3);

V= V*((30000+7500)/7500);	    //voltage
C=((((C*5)/4096)-2.45)/(0.185));	//current
C=C*10;
P.TDA=V;
P.TDB=C;
CAN_TX(P);
delay_ms(1000);
}
}

