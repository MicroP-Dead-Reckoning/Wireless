#include "cc2500.h"

/* helper functions */

/* source */
int CC2500_SPI_INIT(CC2500_InitTypeDef init) {
	GPIO_InitTypeDef gpio_init_s;
  SPI_InitTypeDef  spi_init_s;
	
	/* Enable SPI */
	//Enable the SPI periph
  RCC_APB1PeriphClockCmd(CC2500_SPI_CLK, ENABLE);

  // Enable SCK, MOSI and MISO GPIO clocks
  RCC_AHB1PeriphClockCmd(CC2500_SPI_SCK_GPIO_CLK | CC2500_SPI_MISO_GPIO_CLK | CC2500_SPI_MOSI_GPIO_CLK, ENABLE);

  // Enable CS GPIO clock
  RCC_AHB1PeriphClockCmd(CC2500_SPI_CS_GPIO_CLK, ENABLE);
  
	/* Enable Interrupts over SPI */
  //// Enable INT1 GPIO clock
  //RCC_AHB1PeriphClockCmd(CC2500_SPI_INT1_GPIO_CLK, ENABLE);
  //// Enable INT2 GPIO clock
  //RCC_AHB1PeriphClockCmd(CC2500_SPI_INT2_GPIO_CLK, ENABLE);
	
	/* GPIO Config */
	GPIO_PinAFConfig(CC2500_SPI_SCK_GPIO_PORT, CC2500_SPI_SCK_SOURCE, CC2500_SPI_SCK_AF);
  GPIO_PinAFConfig(CC2500_SPI_MISO_GPIO_PORT, CC2500_SPI_MISO_SOURCE, CC2500_SPI_MISO_AF);
  GPIO_PinAFConfig(CC2500_SPI_MOSI_GPIO_PORT, CC2500_SPI_MOSI_SOURCE, CC2500_SPI_MOSI_AF);
	GPIO_PinAFConfig(CC2500_SPI_CS_GPIO_PORT, CC2500_SPI_CS_SOURCE, CC2500_SPI_CS_AF);

	gpio_init_s.GPIO_Mode =  GPIO_Mode_AF;
  gpio_init_s.GPIO_OType = GPIO_OType_PP;
  gpio_init_s.GPIO_PuPd  = GPIO_PuPd_DOWN;
  gpio_init_s.GPIO_Speed = GPIO_Speed_50MHz;
	
	/* SPI SCK pin configuration */
  gpio_init_s.GPIO_Pin = CC2500_SPI_SCK_PIN;
  GPIO_Init(CC2500_SPI_SCK_GPIO_PORT, &gpio_init_s);

  /* SPI  MOSI pin configuration */
  gpio_init_s.GPIO_Pin =  CC2500_SPI_MOSI_PIN;
  GPIO_Init(CC2500_SPI_MOSI_GPIO_PORT, &gpio_init_s);

  /* SPI MISO pin configuration */
  gpio_init_s.GPIO_Pin = CC2500_SPI_MISO_PIN;
  GPIO_Init(CC2500_SPI_MISO_GPIO_PORT, &gpio_init_s);
	
	/* SPI CA pin configuration */
  gpio_init_s.GPIO_Pin = CC2500_SPI_CS_PIN;
  GPIO_Init(CC2500_SPI_CS_GPIO_PORT, &gpio_init_s);
	
	/* SPI configuration */
  SPI_I2S_DeInit(CC2500_SPI);
  spi_init_s.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  spi_init_s.SPI_DataSize = SPI_DataSize_8b;
  spi_init_s.SPI_CPOL = SPI_CPOL_Low;
  spi_init_s.SPI_CPHA = SPI_CPHA_1Edge;
  spi_init_s.SPI_NSS = SPI_NSS_Soft;
  spi_init_s.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;	// Reduces GPIO clock to 5.25 MHz
  spi_init_s.SPI_FirstBit = SPI_FirstBit_MSB;
  spi_init_s.SPI_CRCPolynomial = 7;
  spi_init_s.SPI_Mode = SPI_Mode_Master;
  SPI_Init(CC2500_SPI, &spi_init_s);
	
	return 0;
}


