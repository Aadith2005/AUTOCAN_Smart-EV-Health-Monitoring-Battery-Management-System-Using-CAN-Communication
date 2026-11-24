void CAN_INIT(void)
{
PINSEL1|=0x00014000;
VPBDIV = 1;
C2MOD=0X1;
AFMR=0X2;
C2BTR=0x001C001E;
C2MOD=0X0;
}
void CAN_TX(CAN M1)
{
C2TID1=M1.ID;
C2TFI1=(M1.DLC<<16);
if(M1.RTR==0)
{
C2TFI1&=~(1<<30);
C2TDA1=M1.TDA;
C2TDB1=M1.TDB;
}
else
{
C2TFI1|=(1<<30);
}

C2CMR=(1<<0)|(1<<5);
while((C2GSR&(1<<3))==0);
}
