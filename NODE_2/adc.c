float ADC_CONVERSION(void)
{

int ab;
ADCR=0X00200D04;

delay_ms(1000);
ADCR=(ADCR|0X01000000);
while((ADDR&0X80000000)!=0X80000000);											   
ab=(ADDR&0X0000FFC0);
ab=ab>>6;
return((3.3*ab/1023)*10);

}

