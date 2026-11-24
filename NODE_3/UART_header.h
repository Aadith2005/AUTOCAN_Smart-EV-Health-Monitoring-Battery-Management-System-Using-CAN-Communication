void UART_CONFIG(unsigned int baud)
{	PINSEL0|=0x5;
	U0LCR=0x83;
	switch(baud){	
		case 115200:U0DLL=32;	break;//PCLK=60MHz
		case 921600:U0DLL=4;	break;
		default:	U0DLL=32	;	
	}
	U0LCR=0x03;
}
void UART_TX(unsigned char txbyte)
{
while(((U0LSR>>5)&1)==0);
U0THR=txbyte;
}

unsigned char UART_RX(void)
{
while((U0LSR&1)==0);
return U0RBR;
}

void UART_STR(unsigned char *s)
{
while(*s)
{
UART_TX(*s++);
}
}


void UART_INTEGER(signed int n)
{
unsigned char arr[5];
int i=0;
if(n==0)
{
UART_TX('0');
return;
}
else
{
if(n<0)
{
UART_TX('-');
n=-n;
}
while(n>0)
{
arr[i++]=n%10;
n=n/10;
}
for(--i;i>=0;i--)
{
UART_TX(arr[i]+48);
}
}
}

void UART_FLOAT(float f)
{
int temp=f;
UART_INTEGER(temp);
UART_TX('.');
temp=(f-temp)*10;
UART_INTEGER(temp);
}

void UART_HEX(int num){
	char buf[10];
	sprintf(buf,"%X",num);
	UART_STR(buf);
}
