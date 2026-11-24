void CAN_INIT(void){
	PINSEL1|=0x00014000;//P0.23-->TD2 & P0.24-->RD2
	VPBDIV=1; //PCLK=60MHz

	C2MOD=0x1; //CAN1 into Reset  Mode 
	AFMR=0x02; //accept all receiving messages(data/remote)
	C2BTR=0x001C001E; //B125Kbps @ PLCK=60MHz
	C2MOD=0x0; //CAN1 into Normal Mode
}

void CAN_RX(CAN *M1){

   	while((C2GSR&0x1)==0);
	M1->ID=C2RID;
	M1->DLC=(C2RFS>>16)&0xF;
	M1->RTR=(C2RFS>>30)&0x1;
	if(M1->RTR==0){ //if data frame
	    M1->TDA=C2RDA;
		M1->TDB=C2RDB;
				}
	C2CMR=(1<<2);//free receiver buffer(imp)
}
