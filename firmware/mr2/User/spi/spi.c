// ===================================================================================
// Basic SPI Master Functions for CH32X035/CH32X034/CH32X033                    v1.0 *
// ===================================================================================
// 2023 by Stefan Wagner:   https://github.com/wagiminator

#include"spi.h"

/*

SPI_CTLR1_MSTR (Master Configuration)
c
// §¢§Ú§ä §Ó§í§Ò§à§â§Ñ §â§Ö§Ø§Ú§Þ§Ñ Master/Slave
// 1 = Master mode - §Ü§à§ß§ä§â§à§Ý§Ý§Ö§â §Ô§Ö§ß§Ö§â§Ú§â§å§Ö§ä §ä§Ñ§Ü§ä§à§Ó§í§Û §ã§Ú§Ô§ß§Ñ§Ý SCK
// 0 = Slave mode - §Ü§à§ß§ä§â§à§Ý§Ý§Ö§â §á§â§Ú§ß§Ú§Þ§Ñ§Ö§ä §ä§Ñ§Ü§ä§à§Ó§í§Û §ã§Ú§Ô§ß§Ñ§Ý SCK

// §£ Master mode:
// - §¤§Ö§ß§Ö§â§Ñ§è§Ú§ñ §ä§Ñ§Ü§ä§à§Ó§à§Û §é§Ñ§ã§ä§à§ä§í SCK
// - §µ§á§â§Ñ§Ó§Ý§Ö§ß§Ú§Ö §ã§Ú§Ô§ß§Ñ§Ý§à§Þ NSS (CS) §Õ§Ý§ñ §Ó§Ö§Õ§à§Þ§í§ç §å§ã§ä§â§à§Û§ã§ä§Ó
// - §ª§ß§Ú§è§Ú§Ñ§è§Ú§ñ §á§Ö§â§Ö§Õ§Ñ§é§Ú §Õ§Ñ§ß§ß§í§ç
SPI_CTLR1_SSM (Software Slave Management)
c
// §¢§Ú§ä §á§â§à§Ô§â§Ñ§Þ§Þ§ß§à§Ô§à §å§á§â§Ñ§Ó§Ý§Ö§ß§Ú§ñ §ã§Ú§Ô§ß§Ñ§Ý§à§Þ NSS (Slave Select)
// 1 = NSS §å§á§â§Ñ§Ó§Ý§ñ§Ö§ä§ã§ñ §á§â§à§Ô§â§Ñ§Þ§Þ§ß§à §é§Ö§â§Ö§Ù §Ò§Ú§ä SSI
// 0 = NSS §å§á§â§Ñ§Ó§Ý§ñ§Ö§ä§ã§ñ §Ñ§á§á§Ñ§â§Ñ§ä§ß§à (§Ó§ß§Ö§ê§ß§Ú§Û §Ó§í§Ó§à§Õ)

// §¬§à§Ô§Õ§Ñ SSM = 1:
// - §£§í§Ó§à§Õ NSS §Þ§à§Ø§ß§à §Ú§ã§á§à§Ý§î§Ù§à§Ó§Ñ§ä§î §Õ§Ý§ñ §Õ§â§å§Ô§Ú§ç §æ§å§ß§Ü§è§Ú§Û
// - §³§à§ã§ä§à§ñ§ß§Ú§Ö NSS §à§á§â§Ö§Õ§Ö§Ý§ñ§Ö§ä§ã§ñ §Ò§Ú§ä§à§Þ SSI
// - §±§à§Ý§Ö§Ù§ß§à §Õ§Ý§ñ multi-master §ã§Ú§ã§ä§Ö§Þ
SPI_CTLR1_SSI (Internal Slave Select)
c
// §£§ß§å§ä§â§Ö§ß§ß§Ú§Û §ã§Ú§Ô§ß§Ñ§Ý NSS (§â§Ñ§Ò§à§ä§Ñ§Ö§ä §ä§à§Ý§î§Ü§à §Ü§à§Ô§Õ§Ñ SSM = 1)
// 1 = §£§ß§å§ä§â§Ö§ß§ß§Ú§Û NSS §å§ã§ä§Ñ§ß§à§Ó§Ý§Ö§ß §Ó §Ó§í§ã§à§Ü§Ú§Û §å§â§à§Ó§Ö§ß§î (§å§ã§ä§â§à§Û§ã§ä§Ó§à §ß§Ö selected)
// 0 = §£§ß§å§ä§â§Ö§ß§ß§Ú§Û NSS §å§ã§ä§Ñ§ß§à§Ó§Ý§Ö§ß §Ó §ß§Ú§Ù§Ü§Ú§Û §å§â§à§Ó§Ö§ß§î (§å§ã§ä§â§à§Û§ã§ä§Ó§à selected)

// §ª§ã§á§à§Ý§î§Ù§à§Ó§Ñ§ß§Ú§Ö:
// - §£ Master mode: §Õ§à§Ý§Ø§Ö§ß §Ò§í§ä§î §å§ã§ä§Ñ§ß§à§Ó§Ý§Ö§ß §Ó 1
// - §£ Slave mode: §à§á§â§Ö§Õ§Ö§Ý§ñ§Ö§ä §ã§é§Ú§ä§Ñ§Ö§ä§ã§ñ §Ý§Ú §å§ã§ä§â§à§Û§ã§ä§Ó§à selected
SPI_CTLR1_SPE (SPI Enable)
c
// §¢§Ú§ä §Ó§Ü§Ý§ð§é§Ö§ß§Ú§ñ SPI
// 1 = SPI §Ó§Ü§Ý§ð§é§Ö§ß §Ú §Ô§à§ä§à§Ó §Ü §â§Ñ§Ò§à§ä§Ö
// 0 = SPI §Ó§í§Ü§Ý§ð§é§Ö§ß §Õ§Ý§ñ §ï§Ü§à§ß§à§Þ§Ú§Ú §ï§ß§Ö§â§Ô§Ú§Ú

// §£§Ñ§Ø§ß§à:
// - §±§Ö§â§Ö§Õ §ß§Ñ§ã§ä§â§à§Û§Ü§à§Û §Õ§â§å§Ô§Ú§ç §â§Ö§Ô§Ú§ã§ä§â§à§Ó SPE §Õ§à§Ý§Ø§Ö§ß §Ò§í§ä§î 0
// - §±§à§ã§Ý§Ö §ß§Ñ§ã§ä§â§à§Û§Ü§Ú §å§ã§ä§Ñ§ß§à§Ó§Ú§ä§î SPE = 1 §Õ§Ý§ñ §Ñ§Ü§ä§Ú§Ó§Ñ§è§Ú§Ú
§±§â§Ú§Þ§Ö§â §á§à§Ý§ß§à§Û §ß§Ñ§ã§ä§â§à§Û§Ü§Ú Master mode:
c
void SPI_Master_Init(void) {
    // 1. §³§ß§Ñ§é§Ñ§Ý§Ñ §à§ä§Ü§Ý§ð§é§Ñ§Ö§Þ SPI §Õ§Ý§ñ §ß§Ñ§ã§ä§â§à§Û§Ü§Ú
    SPI1->CTLR1 &= ~SPI_CTLR1_SPE;
    
    // 2. §¯§Ñ§ã§ä§â§Ñ§Ú§Ó§Ñ§Ö§Þ §á§Ñ§â§Ñ§Þ§Ö§ä§â§í
    SPI1->CTLR1 = SPI_CTLR1_MSTR |   // Master mode
                  SPI_CTLR1_SSM  |   // §±§â§à§Ô§â§Ñ§Þ§Þ§ß§à§Ö §å§á§â§Ñ§Ó§Ý§Ö§ß§Ú§Ö NSS
                  SPI_CTLR1_SSI  |   // §£§ß§å§ä§â§Ö§ß§ß§Ú§Û NSS = 1 (§ß§Ö selected)
                  SPI_CTLR1_SPE;     // §£§Ü§Ý§ð§é§Ñ§Ö§Þ SPI
    
    // §¥§à§á§à§Ý§ß§Ú§ä§Ö§Ý§î§ß§í§Ö §ß§Ñ§ã§ä§â§à§Û§Ü§Ú:
    SPI1->CTLR1 |= SPI_CTLR1_BR_0;   // §±§â§Ö§Õ§Õ§Ö§Ý§Ú§ä§Ö§Ý§î §é§Ñ§ã§ä§à§ä§í
}
§²§Ö§Ø§Ú§Þ§í §â§Ñ§Ò§à§ä§í NSS:
§¡§á§á§Ñ§â§Ñ§ä§ß§à§Ö §å§á§â§Ñ§Ó§Ý§Ö§ß§Ú§Ö (SSM = 0):
c
// NSS §å§á§â§Ñ§Ó§Ý§ñ§Ö§ä§ã§ñ §Ó§ß§Ö§ê§ß§Ú§Þ §Ó§í§Ó§à§Õ§à§Þ
// - §£ Slave mode: NSS input §à§á§â§Ö§Õ§Ö§Ý§ñ§Ö§ä selected §ã§à§ã§ä§à§ñ§ß§Ú§Ö
// - §£ Master mode: NSS output §Ñ§Ó§ä§à§Þ§Ñ§ä§Ú§é§Ö§ã§Ü§Ú §å§á§â§Ñ§Ó§Ý§ñ§Ö§ä §Ó§Ö§Õ§à§Þ§í§Þ§Ú
§±§â§à§Ô§â§Ñ§Þ§Þ§ß§à§Ö §å§á§â§Ñ§Ó§Ý§Ö§ß§Ú§Ö (SSM = 1, SSI = 1):
c
// NSS §å§á§â§Ñ§Ó§Ý§ñ§Ö§ä§ã§ñ §á§â§à§Ô§â§Ñ§Þ§Þ§ß§à
// - §£ Slave mode: §å§ã§ä§â§à§Û§ã§ä§Ó§à §Ó§ã§Ö§Ô§Õ§Ñ §ã§é§Ú§ä§Ñ§Ö§ä§ã§ñ §ß§Ö selected
// - §£ Master mode: §á§à§Ý§ß§í§Û §Ü§à§ß§ä§â§à§Ý§î §ß§Ñ§Õ §á§Ö§â§Ö§Õ§Ñ§é§Ö§Û
§´§Ú§á§Ú§é§ß§í§Ö §Ü§à§ß§æ§Ú§Ô§å§â§Ñ§è§Ú§Ú:
Master §ã §Ñ§á§á§Ñ§â§Ñ§ä§ß§í§Þ NSS:
c
SPI1->CTLR1 = SPI_CTLR1_MSTR |   // Master
              SPI_CTLR1_SPE;     // Enable
// SSM = 0 - §Ñ§á§á§Ñ§â§Ñ§ä§ß§à§Ö §å§á§â§Ñ§Ó§Ý§Ö§ß§Ú§Ö
Master §ã §á§â§à§Ô§â§Ñ§Þ§Þ§ß§í§Þ NSS:
c
SPI1->CTLR1 = SPI_CTLR1_MSTR |   // Master
              SPI_CTLR1_SSM  |   // §±§â§à§Ô§â§Ñ§Þ§Þ§ß§à§Ö §å§á§â§Ñ§Ó§Ý§Ö§ß§Ú§Ö
              SPI_CTLR1_SSI  |   // NSS = 1
              SPI_CTLR1_SPE;     // Enable
Slave §â§Ö§Ø§Ú§Þ:
c
SPI1->CTLR1 = SPI_CTLR1_SSM  |   // §±§â§à§Ô§â§Ñ§Þ§Þ§ß§à§Ö §å§á§â§Ñ§Ó§Ý§Ö§ß§Ú§Ö  
              SPI_CTLR1_SSI  |   // NSS = 1 (§ß§Ö selected)
              SPI_CTLR1_SPE;     // Enable
// MSTR = 0 - Slave mode
§¿§ä§Ú §Ò§Ú§ä§í §à§Ò§Ö§ã§á§Ö§é§Ú§Ó§Ñ§ð§ä §Ô§Ú§Ò§Ü§å§ð §ß§Ñ§ã§ä§â§à§Û§Ü§å §â§Ö§Ø§Ú§Þ§à§Ó §â§Ñ§Ò§à§ä§í SPI §Ó §Ù§Ñ§Ó§Ú§ã§Ú§Þ§à§ã§ä§Ú §à§ä §ä§â§Ö§Ò§à§Ó§Ñ§ß§Ú§Û §á§â§Ú§Ý§à§Ø§Ö§ß§Ú§ñ.

================================================================================================

MASTER with HW CS:

SPI1->CTLR1 = SPI_CTLR1_MSTR |   // Master mode
              SPI_CTLR1_SPE;     // Enable SPI

MASTER with SW CS:

SPI1->CTLR1 = SPI_CTLR1_MSTR |   // Master
              SPI_CTLR1_SSM  |   // Software SS
              SPI_CTLR1_SSI  |   // Internal SS high
              SPI_CTLR1_SPE;     // Enable



SLAVE with HW CS:

SPI1->CTLR1 = SPI_CTLR1_SPE;     // Enable SPI only

SLAVE with SW CS:

SPI1->CTLR1 = SPI_CTLR1_SSM  |   // Software SS
              SPI_CTLR1_SSI  |   // Internal SS (0 = selected, 1 = not selected)
              SPI_CTLR1_SPE;     // Enable SPI

*/

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
void SPI_init_ext(char a_master, char a_hw_cs, uint16_t a_prescaller, char a_pha, char a_pol ) {

  // Enable GPIO and SPI module clock
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPAEN | RCC_SPI1EN;
  
  // Setup GPIO pins PA5 (SCK), PA6 (MISO), PA7 (MOSI)
  GPIOA->CFGLR  = (GPIOA->CFGLR & ~(((uint32_t)0b1111<<(5<<2)) | ((uint32_t)0b1111<<(6<<2)) | ((uint32_t)0b1111<<(7<<2)) ))
                                |  (((uint32_t)0b1011<<(5<<2)) | ((uint32_t)0b1000<<(6<<2)) | ((uint32_t)0b1011<<(7<<2)) );
  GPIOA->BSHR   = (uint32_t)1<<6;

//a_hw_cs ????????


  uint16_t ctlr1 = (a_prescaller << 3)      // set prescaler
              //| SPI_CTLR1_MSTR        // master configuration
              | SPI_CTLR1_SSM         // software control of NSS
              | SPI_CTLR1_SSI         // set internal NSS high
              | SPI_CTLR1_SPE         // enable SPI
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
