#include "all_wireless_tests.h"


void test_wireless(void){

	uint8_t res2[3];
	
	CC2500_Read(res2, CC2500_FREQ_REG, 3);
	printf("result = %x, %x, %x\n", res2[0], res2[1], res2[2]);
	uint8_t recv_buffer[20];
	int i,j;
	uint8_t num;

	for(i = 0; i < 1000; i++){
		CC2500_Read_SR(&num, 0x3B);
		CC2500_Read_RX(recv_buffer, num);
		for(i = 0; i < num; i++){
			printf("%d, ", recv_buffer[i]);
		}
		if (num == 0) {
			printf("empty!");
		}
		printf("\n");
 		for(j = 0; j < (168000000/4); j++);
	}
	
	
}	

uint8_t recv_buffer;
uint8_t num;
int TEST_VALUE = 0;
void EXTI15_10_IRQHandler() {
	if (EXTI_GetITStatus(CC2500_SPI_INT1_EXTI_LINE) != RESET){
		EXTI_ClearITPendingBit(CC2500_SPI_INT1_EXTI_LINE);
	}
}
