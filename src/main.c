/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"
#include <stdio.h>

#include "cc2500.h"

/*
 * main: initialize and start the system
 */
int main (void) {
	CC2500_SPI_INIT();
	
	uint8_t x[4];
	CC2500_Read(x, CC2500_PARTNAME, 2);
	printf("%d %d %d %d\n", x[0], x[1], x[2], x[3]);
	CC2500_Read(x, CC2500_VERSION, 2);
	printf("%d %d %d %d\n", x[0], x[1], x[2], x[3]);
}


