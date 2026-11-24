#include "project_header.h"
#include "delay_ms.c"
#include "cantx_driver.c"
#include "adc.c"
u32 TEMP;


int main()
{

CAN T;

PINSEL1|=0X05000000;
IODIR0=(1<<8)|(1<<9);
IOSET0=(1<<8)|(1<<9);

CAN_INIT();


T.ID=0x102;
T.RTR=0;
T.DLC=8;


while(1){
TEMP=ADC_CONVERSION()*10;

if(TEMP>30)
{
IOCLR0=1<<8;
IOSET0=1<<9;	 
}
else
{
IOSET0=1<<8;
IOSET0=1<<9;
}
T.TDA=TEMP;
T.TDB=0;
CAN_TX(T);
delay_ms(1000);
}
}

