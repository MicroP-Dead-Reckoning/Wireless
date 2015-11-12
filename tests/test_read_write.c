#include "all_wireless_tests.h"


void test_read_write(void){
	uint8_t result;
	uint8_t value = 76;
	CC2500_Write(&value, 0x00, 1);
	
	CC2500_Read(&result, 0x00, 1);
	printf("result = %d\n", result);
	
	uint8_t val2[3] = {65,80,43};
	uint8_t res2[3];
	CC2500_Write(val2, 0x00, 3);
	
	CC2500_Read(res2, 0x00, 3);
	printf("result = %d, %d, %d\n", res2[0], res2[1], res2[2]);
}	
