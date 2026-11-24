#define LCD_D 0xff << 0
#define RS 1<<8
#define E  1<<9
void LCD_INIT(void);
void LCD_COMMAND( unsigned char);
void LCD_DATA(unsigned char);
void LCD_STR(unsigned char*);
void LCD_FLOAT(float );

void LCD_INIT()
{
PINSEL0=0;
IODIR0=LCD_D|RS|E;
LCD_COMMAND(0X01);
LCD_COMMAND(0X02);
LCD_COMMAND(0X0C);
LCD_COMMAND(0X38);
}
void LCD_COMMAND(unsigned char cmd)
{
IOCLR0=LCD_D;
IOSET0=cmd;
IOCLR0=RS;
IOSET0=E;
delay_ms(2);
IOCLR0=E;
}



void LCD_DATA(unsigned char d)
{
IOCLR0=LCD_D;
IOSET0=d;
IOSET0=RS;
IOSET0=E;
delay_ms(2);
IOCLR0=E;
}

void LCD_STR(unsigned char *s)
{
int pos=0;
while(*s)
{
LCD_DATA(*s++);
pos++;
if(pos==20)
    LCD_COMMAND(0XC0);
else if(pos==40)
    LCD_COMMAND(0X94);
else if(pos==60)
    LCD_COMMAND(0XD4);
	}

}
void LCD_INTEGER(signed int n)
{
unsigned char arr[5];
signed char i=0;
if(n==0)
LCD_DATA('0');

else
{
if(n<0)
{
LCD_DATA('-');
n=-n;
}
while(n>0)
{
arr[i++]=n%10;
n=n/10;
}
for(--i;i>=0;i--)
{
LCD_DATA(arr[i]+48);
}
}
}

void LCD_FLOAT(float f)

{
 int temp;

 temp=f;

 LCD_INTEGER(temp);

 LCD_DATA('.');

 temp=(f-temp)*10;

 LCD_INTEGER(temp);
}
