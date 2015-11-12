#include "cc2500.h"

/* defines */
/* Read/Write command */
#define READWRITE_CMD              ((uint8_t)0x80) 
/* Multiple byte read/write command */ 
#define MULTIPLEBYTE_CMD           ((uint8_t)0x40)
/* Dummy Byte Send by the SPI Master device in order to generate the Clock to the Slave device */
#define DUMMY_BYTE                 ((uint8_t)0x00)

/* macros */
#define CC2500_CS_LOW()       GPIO_ResetBits(CC2500_SPI_CS_GPIO_PORT, CC2500_SPI_CS_PIN)
#define CC2500_CS_HIGH()      GPIO_SetBits(CC2500_SPI_CS_GPIO_PORT, CC2500_SPI_CS_PIN)

/* helper functions */
static uint8_t CC2500_SendByte(uint8_t byte);

/* source */
int CC2500_SPI_INIT() {
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
  RCC_AHB1PeriphClockCmd(CC2500_SPI_INT1_GPIO_CLK, ENABLE);
  //// Enable INT2 GPIO clock
  RCC_AHB1PeriphClockCmd(CC2500_SPI_INT2_GPIO_CLK, ENABLE);
	
	/* GPIO Config */
	GPIO_PinAFConfig(CC2500_SPI_SCK_GPIO_PORT, CC2500_SPI_SCK_SOURCE, CC2500_SPI_SCK_AF);
  GPIO_PinAFConfig(CC2500_SPI_MISO_GPIO_PORT, CC2500_SPI_MISO_SOURCE, CC2500_SPI_MISO_AF);
  GPIO_PinAFConfig(CC2500_SPI_MOSI_GPIO_PORT, CC2500_SPI_MOSI_SOURCE, CC2500_SPI_MOSI_AF);
	//GPIO_PinAFConfig(CC2500_SPI_CS_GPIO_PORT, CC2500_SPI_CS_SOURCE, CC2500_SPI_CS_AF);

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
	
	/* SPI CS pin configuration */
  //gpio_init_s.GPIO_Pin = CC2500_SPI_CS_PIN;
  //GPIO_Init(CC2500_SPI_CS_GPIO_PORT, &gpio_init_s);
	
	/* SPI configuration */
  SPI_I2S_DeInit(CC2500_SPI);
  spi_init_s.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  spi_init_s.SPI_DataSize = SPI_DataSize_8b;
  spi_init_s.SPI_CPOL = SPI_CPOL_Low;
  spi_init_s.SPI_CPHA = SPI_CPHA_1Edge;
  spi_init_s.SPI_NSS = SPI_NSS_Soft;
  spi_init_s.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;	// Reduces GPIO clock to 5.25 MHz
  spi_init_s.SPI_FirstBit = SPI_FirstBit_MSB;
  spi_init_s.SPI_CRCPolynomial = 7;
  spi_init_s.SPI_Mode = SPI_Mode_Master;
  SPI_Init(CC2500_SPI, &spi_init_s);
	
	/* Enable SPI */
	SPI_Cmd(CC2500_SPI, ENABLE);
	
	/* Configure GPIO PIN for Lis Chip select */
  gpio_init_s.GPIO_Pin = CC2500_SPI_CS_PIN;
  gpio_init_s.GPIO_Mode = GPIO_Mode_OUT;
  gpio_init_s.GPIO_OType = GPIO_OType_PP;
  gpio_init_s.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(CC2500_SPI_CS_GPIO_PORT, &gpio_init_s);
	
	/* Deselect : Chip Select high */
  GPIO_SetBits(CC2500_SPI_CS_GPIO_PORT, CC2500_SPI_CS_PIN);
	
	/* Configure GPIO PINs to detect Interrupts 
  gpio_init_s.GPIO_Pin = CC2500_SPI_INT1_PIN;
  gpio_init_s.GPIO_Mode = GPIO_Mode_IN;
  gpio_init_s.GPIO_OType = GPIO_OType_PP;
  gpio_init_s.GPIO_Speed = GPIO_Speed_50MHz;
  gpio_init_s.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(LIS3DSH_SPI_INT1_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = LIS3DSH_SPI_INT2_PIN;
  GPIO_Init(LIS3DSH_SPI_INT2_GPIO_PORT, &GPIO_InitStructure);
	*/
	return 0;
}
static uint8_t CC2500_SendByte(uint8_t byte)
{
	uint32_t  CC2500Timeout;
	
  /* Loop while DR register in not emplty */
  CC2500Timeout = CC2500_FLAG_TIMEOUT;
  while (SPI_I2S_GetFlagStatus(CC2500_SPI, SPI_I2S_FLAG_TXE) == RESET)
  {
    if((CC2500Timeout--) == 0) return 69;	// TODO
  }
  
  /* Send a Byte through the SPI peripheral */
  SPI_I2S_SendData(CC2500_SPI, byte);
  
  /* Wait to receive a Byte */
  CC2500Timeout = CC2500_FLAG_TIMEOUT;
  while (SPI_I2S_GetFlagStatus(CC2500_SPI, SPI_I2S_FLAG_RXNE) == RESET)
  {
    if((CC2500Timeout--) == 0) return 69;
  }
  
  /* Return the Byte read from the SPI bus */
  return (uint8_t)SPI_I2S_ReceiveData(CC2500_SPI);
}

void CC2500_Read(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead)
{  
  if(NumByteToRead > 0x01)
  {
    ReadAddr |= (uint8_t)(READWRITE_CMD | MULTIPLEBYTE_CMD);
  }
  else
  {
    ReadAddr |= (uint8_t)READWRITE_CMD;
  }
  /* Set chip select Low at the start of the transmission */
  CC2500_CS_LOW();
  
  /* Send the Address of the indexed register */
  CC2500_SendByte(ReadAddr);
  
  /* Receive the data that will be read from the device (MSB First) */
  while(NumByteToRead > 0x00)
  {
    /* Send dummy byte (0x00) to generate the SPI clock to LIS3DSH (Slave device) */
    *pBuffer = CC2500_SendByte(DUMMY_BYTE);
    NumByteToRead--;
    pBuffer++;
  }
  
  /* Set chip select High at the end of the transmission */ 
  CC2500_CS_HIGH();
}

