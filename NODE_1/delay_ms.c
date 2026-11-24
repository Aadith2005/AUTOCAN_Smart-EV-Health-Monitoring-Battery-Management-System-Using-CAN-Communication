void delay_ms(u32 ms)
{
T0PR =60000-1;
T0TCR=0x1;
while(T0TC<ms);
T0TCR=0x3;
T0TCR=0x0;
}

 
  
    