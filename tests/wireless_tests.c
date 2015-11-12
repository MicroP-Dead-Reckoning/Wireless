#include "all_wireless_tests.h"

/*
 * main: initialize and start the system
 */
int main (void) {
	CC2500_SPI_INIT();
	
	test_control_read();
	//test_read_write();
	test_wireless();
	
}
