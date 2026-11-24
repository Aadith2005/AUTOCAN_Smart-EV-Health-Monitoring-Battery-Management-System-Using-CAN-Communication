void SPI0_INIT(void)
{
	
	PINSEL0 |=0X00001500;
    S0SPCCR  = 150;// to set 100kbps(The SPI rate may be 
	               //calculated as: PCLK rate / SPI_RATE
	S0SPCR  = 0X20; //spi module in master mode,
                                  //CPOL =1,CCPHA = 1. MSB first
	IODIR0 = 1<<7;
	

}

u8 SPI0(u8 data)
{
   u8 stat;
   stat = S0SPSR;    //clear SPIF 
   S0SPDR = data;   // load spi tx reg
   while(((S0SPSR>>7)&1)==0); // wait for transmission to complete
   return S0SPDR;    // read data from SPI data reg, place into buffer 
}