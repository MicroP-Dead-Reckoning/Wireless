#include "all_wireless_tests.h"


void test_wireless(void){

	uint8_t res2[3];
	
	CC2500_Read(res2, CC2500_FREQ_REG, 3);
	printf("result = %x, %x, %x\n", res2[0], res2[1], res2[2]);
	uint8_t recv_buffer[10];
	
//	CC2500_Read_RX(recv_buffer, sizeof(recv_buffer));
//	printf("buffer received:\n");
//	int i;
//	for(i = 0; i < 10; i++){
//		printf("%d\n", recv_buffer[i]);
//	}

//	CC2500_Read_RX(recv_buffer, sizeof(recv_buffer));
//	printf("buffer received:\n");
//	for(i = 0; i < 10; i++){
//		printf("%d\n", recv_buffer[i]);
//	}
	uint8_t num;
	int i,j;
	for(i = 0; i < 1000; i++){
		CC2500_Read_RX(recv_buffer, sizeof(recv_buffer));
		CC2500_Read_SR(&num, 0x3B);
		printf("num_bytes = %d\n", num);
		printf("buffer received:\n");
		for(i = 0; i < 10; i++){
			printf("%d\n", recv_buffer[i]);
		}
		for(j = 0; j < 16800000; j++);
	}
	
	
}	
