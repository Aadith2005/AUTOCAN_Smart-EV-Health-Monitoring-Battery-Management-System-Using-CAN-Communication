#include "rx_project_header.h"
#include "delay_ms.c"
#include "lcd_header.h"
#include "UART_header.h"
#include "canrx_driver.c"


f32 temp=0.0f,voltage=0.0f,current=0.0f,power=0.0f;
int main()
{
CAN M1;
CAN_INIT();
LCD_INIT();
LCD_COMMAND(0X80);
LCD_STR("AUTOCAN SMART EV    HEALTH MONITORING & BATTERY MANAGEMENT  SYSTEM USING CAN");
delay_ms(3000);
LCD_COMMAND(0X01);
//UART_CONFIG(115200);
//UART_STR("NODE TESTING CAN \r \n");
while(1)
{
CAN_RX(&M1);
if(M1.ID==0X101)
{
if(M1.RTR==0)
{
/*UART_STR("POWER DATA FRAME IS RECEIVED\r \n");
UART_HEX(M1.ID);
UART_TX(' ');
UART_HEX(M1.DLC);
UART_TX(' ');
UART_FLOAT(M1.TDA);
UART_TX(' ');
UART_FLOAT(M1.TDB);
UART_STR("\r\n");*/ 

voltage=M1.TDA;
voltage=voltage/100;
current=M1.TDB;
//current=current*100;
power=voltage*current;

}
/*else
{
UART_STR("NODE REMOTE FRAME IS RECEIVED\r\n");
UART_HEX(M1.ID);
UART_TX(' ');
UART_HEX(M1.DLC);
UART_TX(' ');
UART_STR("\r\n");
}*/}

if(M1.ID==0X102)
{
if(M1.RTR==0)
{
/*UART_STR("TEMP DATA FRAME IS RECEIVED\r \n");
UART_HEX(M1.ID);
UART_TX(' ');
UART_HEX(M1.DLC);
UART_TX(' ');
UART_FLOAT(M1.TDA);
UART_TX(' ');
UART_FLOAT(M1.TDB);
UART_STR("\r\n");  */

temp=M1.TDA;

}
/*else
{
UART_STR("NODE REMOTE FRAME IS RECEIVED\r\n");
UART_HEX(M1.ID);
UART_TX(' ');
UART_HEX(M1.DLC);
UART_TX(' ');
UART_STR("\r\n"); 
}*/
}
LCD_COMMAND(0x01);
LCD_COMMAND(0X80);
LCD_STR("TEMP:");
LCD_INTEGER(temp);
LCD_STR("C  ");

if(temp>30)
{

LCD_STR("FAN:ON");
}
else
{
LCD_STR("FAN:OFF");
}

LCD_COMMAND(0XC0);
LCD_STR("VOLTAGE:");
LCD_FLOAT(voltage);
LCD_STR("V");

LCD_COMMAND(0X94);
LCD_STR("CURRENT:");
LCD_FLOAT(current);
LCD_STR("mA");

LCD_COMMAND(0XD4);
LCD_STR("POWER:");
LCD_FLOAT(power);
LCD_STR("W");

}
}

