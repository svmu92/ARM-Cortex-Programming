extern void SystemInit(void);
extern int __main(void);




int main()
{
	
	return 0;
}

void Reset_Handler(void)
{
		SystemInit();
		__main();
	
}
