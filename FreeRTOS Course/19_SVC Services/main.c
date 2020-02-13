


int __svc(0x00) svc_service_add(int x,int y);
int __svc(0x01) svc_service_sub(int x,int y);
int __svc(0x02) svc_service_mul(int x,int y);
int __svc(0x03) svc_service_div(int x,int y);
void SVC_Handler_C (unsigned int *svc_args);

int x,y,z;

int main()
{
	x=1;
	y=5;
	z=svc_service_add(x,y);
	
	x=9;
	y=2;
	z=svc_service_sub(x,y);
	
	x=4;
	y=3;
	z=svc_service_mul(x,y);
	
	x=8;
	y=4;
	z=svc_service_div(x,y);
	
	
}



__asm void SVC_Handler(void)
{
	TST LR,#4 //Bit two 0b 0100
	ITE EQ
	MRSEQ	R0,MSP // if equal copy Main Stack Pointer
	MRSNE	R0,PSP // if not equal copy Program Stack Pointer
	B		__cpp(SVC_Handler_C)
}


void SVC_Handler_C (unsigned int *svc_args)
{
	unsigned int svc_number;
	svc_number = ((char *)svc_args[6])[-2]; //1st byte of the SVC instruction - the SVC number
	switch(svc_number)
	{
		case 0: svc_args[0]=svc_args[0]+svc_args[1];
						break;
		case 1: svc_args[0]=svc_args[0]-svc_args[1];
						break;
		case 2: svc_args[0]=svc_args[0]*svc_args[1];
						break;
		case 3: svc_args[0]=svc_args[0]/svc_args[1];
						break;
		default:break;		
	}
}
