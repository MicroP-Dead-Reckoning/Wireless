#include "all_wireless_tests.h"


void test_wireless(void){

	uint8_t res2[3];
	
	CC2500_Read(res2, CC2500_FREQ_REG, 3);
	printf("result = %x, %x, %x\n", res2[0], res2[1], res2[2]);
	uint8_t recv_buffer;
	int i,j;
	for(i = 0; i < 1000; i++){
		//CC2500_Read_SR(&num, 0x3B);
		CC2500_Read_RX(&recv_buffer, 1);
		//for(i = 0; i < num; i++){
			printf("%d\n", recv_buffer);
		//}
 		for(j = 0; j < (168000000/12); j++);
	}
	
	
}	