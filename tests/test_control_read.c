#include "all_wireless_tests.h"

const uint8_t PARTNUM = 128, VERSION = 3;

void test_control_read(void) {
	uint8_t x;
	uint8_t errct = 0;
	CC2500_Read_SR(&x, CC2500_PARTNAME);
	
	if (x != PARTNUM) {
		printf("Error reading PARTNUM!\n"
						"Read %d instead of %d\n", x, PARTNUM);
		errct++;
	}
	
	CC2500_Read_SR(&x, CC2500_VERSION);
	if (x != VERSION) {
		printf("Error reading VERSION!\n"
						"Read %d instead of %d\n", x, VERSION);
		errct++;
	}
}
