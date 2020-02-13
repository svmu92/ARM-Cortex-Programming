#include <stdint.h>

#define BIT_BAND_BASE_ADDR		*((volatile unsigned long*)(0x20000000))
	
#define BIT_BAND_ALIAS_BASE		*((volatile unsigned long*)(0x22000000))
	
/*bit 1, bit2 and bit3 of BIT_BAND_BASE_ADDR */

#define BIT_BAND_ALIAS_ADDR1		*((volatile unsigned long*)(BIT_BAND_ALIAS_BASE+0))
#define BIT_BAND_ALIAS_ADDR2		*((volatile unsigned long*)(BIT_BAND_ALIAS_BASE+4))
#define BIT_BAND_ALIAS_ADDR3		*((volatile unsigned long*)(BIT_BAND_ALIAS_BASE+8))


int main(void)
{
		uint32_t val;
		BIT_BAND_BASE_ADDR=0xA0;
	
		BIT_BAND_ALIAS_ADDR1=0x01;
		BIT_BAND_ALIAS_ADDR2=0x01;
		BIT_BAND_ALIAS_ADDR3=0x01;
	
		val=BIT_BAND_BASE_ADDR;
		return 0;
}
