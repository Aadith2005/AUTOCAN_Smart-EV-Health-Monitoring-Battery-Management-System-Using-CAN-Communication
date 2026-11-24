float ADC_CONVERSION(void)
{

int ab;
ADCR=0X00200D04;

delay_ms(1000);
ADCR=(ADCR|0X01000000);
while((ADDR&0X80000000)!=0X80000000);
ab=(ADDR&0X0000FFC0);
ab=ab>>6;
return((3.3*ab/1023)*100);

}

f32 Read_ADC_MCP3204(u8 channelNo)
{
  u8 hByte,lByte;
  u32 adcVal=0;
   
  //select/activate chip 
  IOCLR0 = 1<<7;
	//delay_ms(100);
	
  SPI0(0x06);
  hByte = SPI0(channelNo<<6);	//0xc0
  lByte = SPI0(0x00);
	
	//de-select/de-activate chp
	IOSET0 = 1<<7;
	//delay_ms(100);
  adcVal=((hByte&0x0f)<<8)|lByte;
  return adcVal;
}