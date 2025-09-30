// ===================================================================================
// Basic SPI Master Functions for CH32X035/CH32X034/CH32X033                    v1.0 *
// ===================================================================================
// 2023 by Stefan Wagner:   https://github.com/wagiminator

#include"spi.h"

// Init SPI
void SPI_init(void) {
  // Enable GPIO and SPI module clock
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPAEN | RCC_SPI1EN;
  
  // Setup GPIO pins PA5 (SCK), PA6 (MISO), PA7 (MOSI)
  GPIOA->CFGLR  = (GPIOA->CFGLR & ~(((uint32_t)0b1111<<(5<<2)) | ((uint32_t)0b1111<<(6<<2)) | ((uint32_t)0b1111<<(7<<2)) ))
                                |  (((uint32_t)0b1011<<(5<<2)) | ((uint32_t)0b1000<<(6<<2)) | ((uint32_t)0b1011<<(7<<2)) );
  GPIOA->BSHR   = (uint32_t)1<<6;

  // Setup and enable SPI master, standard configuration
  SPI1->CTLR1 = (SPI_PRESC << 3)      // set prescaler
              | SPI_CTLR1_MSTR        // master configuration
              | SPI_CTLR1_SSM         // software control of NSS
              | SPI_CTLR1_SSI         // set internal NSS high
              | SPI_CTLR1_SPE;        // enable SPI
}

// Init SPI
void SPI_init_ext(char a_master, uint16_t a_prescaller, char a_pha, char a_pol ) {

  // Enable GPIO and SPI module clock
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPAEN | RCC_SPI1EN;
  
  // Setup GPIO pins PA5 (SCK), PA6 (MISO), PA7 (MOSI)
  GPIOA->CFGLR  = (GPIOA->CFGLR & ~(((uint32_t)0b1111<<(5<<2)) | ((uint32_t)0b1111<<(6<<2)) | ((uint32_t)0b1111<<(7<<2)) ))
                                |  (((uint32_t)0b1011<<(5<<2)) | ((uint32_t)0b1000<<(6<<2)) | ((uint32_t)0b1011<<(7<<2)) );
  GPIOA->BSHR   = (uint32_t)1<<6;

  uint16_t ctlr1 = (a_prescaller << 3)      // set prescaler
              //| SPI_CTLR1_MSTR        // master configuration
              | SPI_CTLR1_SSM         // software control of NSS
              | SPI_CTLR1_SSI         // set internal NSS high
              | SPI_CTLR1_SPE;        // enable SPI
    ;

  if ( a_master != 0)
    ctlr1 |= SPI_CTLR1_MSTR;
  if ( a_pha != 0)
    ctlr1 |= SPI_CTLR1_CPHA;
    //SPI_setCPHA(a_pha);
  if ( a_pol != 0)
    ctlr1 |= SPI_CTLR1_CPOL;
    //SPI_setCPOL(a_pol);

  // Setup and enable SPI master, standard configuration
  SPI1->CTLR1 = ctlr1;
}

// Transfer one data byte (read and write)
uint8_t SPI_transfer(uint8_t data) {
  SPI1->DATAR = data;                 // send data byte
  while(!SPI_available());            // wait for reply
  return SPI1->DATAR;                 // return received data byte
}
