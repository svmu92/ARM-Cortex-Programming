#include "stm32f407xx.h"
#include<stdint.h>


extern void do_stack_operations(void);

int main(void)
{
		
	/* Function implemented in Assembly */
	do_stack_operations();
	return 0;
}

