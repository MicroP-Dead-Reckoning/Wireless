#include "all_wireless_tests.h"

void test_control_read(void) {
	uint8_t x;
	CC2500_Read(&x, CC2500_PARTNAME, 1);
	printf("%d\n", x);
	CC2500_Read(&x, CC2500_VERSION, 1);
	printf("%d\n", x);
}
