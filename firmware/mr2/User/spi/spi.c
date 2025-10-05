// ===================================================================================
// Basic SPI Master Functions for CH32X035/CH32X034/CH32X033                    v1.0 *
// ===================================================================================
// 2023 by Stefan Wagner:   https://github.com/wagiminator

#include"spi.h"

/*

SPI_CTLR1_MSTR (Master Configuration)
c
// ���ڧ� �ӧ�ҧ��� ��֧اڧާ� Master/Slave
// 1 = Master mode - �ܧ�ߧ���ݧݧ֧� �ԧ֧ߧ֧�ڧ��֧� ��ѧܧ��ӧ�� ��ڧԧߧѧ� SCK
// 0 = Slave mode - �ܧ�ߧ���ݧݧ֧� ���ڧߧڧާѧ֧� ��ѧܧ��ӧ�� ��ڧԧߧѧ� SCK

// �� Master mode:
// - ���֧ߧ֧�ѧ�ڧ� ��ѧܧ��ӧ�� ��ѧ����� SCK
// - �����ѧӧݧ֧ߧڧ� ��ڧԧߧѧݧ�� NSS (CS) �էݧ� �ӧ֧է�ާ�� ������ۧ���
// - ���ߧڧ�ڧѧ�ڧ� ��֧�֧էѧ�� �էѧߧߧ��
SPI_CTLR1_SSM (Software Slave Management)
c
// ���ڧ� ����ԧ�ѧާާߧ�ԧ� ����ѧӧݧ֧ߧڧ� ��ڧԧߧѧݧ�� NSS (Slave Select)
// 1 = NSS ����ѧӧݧ�֧��� ����ԧ�ѧާާߧ� ��֧�֧� �ҧڧ� SSI
// 0 = NSS ����ѧӧݧ�֧��� �ѧ��ѧ�ѧ�ߧ� (�ӧߧ֧�ߧڧ� �ӧ�ӧ��)

// ����ԧէ� SSM = 1:
// - ����ӧ�� NSS �ާ�اߧ� �ڧ���ݧ�٧�ӧѧ�� �էݧ� �է��ԧڧ� ���ߧܧ�ڧ�
// - ��������ߧڧ� NSS ����֧է֧ݧ�֧��� �ҧڧ��� SSI
// - ����ݧ֧٧ߧ� �էݧ� multi-master ��ڧ��֧�
SPI_CTLR1_SSI (Internal Slave Select)
c
// ���ߧ���֧ߧߧڧ� ��ڧԧߧѧ� NSS (��ѧҧ��ѧ֧� ���ݧ�ܧ� �ܧ�ԧէ� SSM = 1)
// 1 = ���ߧ���֧ߧߧڧ� NSS ����ѧߧ�ӧݧ֧� �� �ӧ���ܧڧ� ����ӧ֧ߧ� (������ۧ��ӧ� �ߧ� selected)
// 0 = ���ߧ���֧ߧߧڧ� NSS ����ѧߧ�ӧݧ֧� �� �ߧڧ٧ܧڧ� ����ӧ֧ߧ� (������ۧ��ӧ� selected)

// ������ݧ�٧�ӧѧߧڧ�:
// - �� Master mode: �է�ݧا֧� �ҧ��� ����ѧߧ�ӧݧ֧� �� 1
// - �� Slave mode: ����֧է֧ݧ�֧� ���ڧ�ѧ֧��� �ݧ� ������ۧ��ӧ� selected
SPI_CTLR1_SPE (SPI Enable)
c
// ���ڧ� �ӧܧݧ��֧ߧڧ� SPI
// 1 = SPI �ӧܧݧ��֧� �� �ԧ���� �� ��ѧҧ���
// 0 = SPI �ӧ�ܧݧ��֧� �էݧ� ��ܧ�ߧ�ާڧ� ��ߧ֧�ԧڧ�

// ���ѧاߧ�:
// - ���֧�֧� �ߧѧ����ۧܧ�� �է��ԧڧ� ��֧ԧڧ����� SPE �է�ݧا֧� �ҧ��� 0
// - �����ݧ� �ߧѧ����ۧܧ� ����ѧߧ�ӧڧ�� SPE = 1 �էݧ� �ѧܧ�ڧӧѧ�ڧ�
����ڧާ֧� ���ݧߧ�� �ߧѧ����ۧܧ� Master mode:
c
void SPI_Master_Init(void) {
    // 1. ���ߧѧ�ѧݧ� ���ܧݧ��ѧ֧� SPI �էݧ� �ߧѧ����ۧܧ�
    SPI1->CTLR1 &= ~SPI_CTLR1_SPE;
    
    // 2. ���ѧ���ѧڧӧѧ֧� ��ѧ�ѧާ֧���
    SPI1->CTLR1 = SPI_CTLR1_MSTR |   // Master mode
                  SPI_CTLR1_SSM  |   // �����ԧ�ѧާާߧ�� ����ѧӧݧ֧ߧڧ� NSS
                  SPI_CTLR1_SSI  |   // ���ߧ���֧ߧߧڧ� NSS = 1 (�ߧ� selected)
                  SPI_CTLR1_SPE;     // ���ܧݧ��ѧ֧� SPI
    
    // ������ݧߧڧ�֧ݧ�ߧ�� �ߧѧ����ۧܧ�:
    SPI1->CTLR1 |= SPI_CTLR1_BR_0;   // ����֧էէ֧ݧڧ�֧ݧ� ��ѧ�����
}
���֧اڧާ� ��ѧҧ��� NSS:
�����ѧ�ѧ�ߧ�� ����ѧӧݧ֧ߧڧ� (SSM = 0):
c
// NSS ����ѧӧݧ�֧��� �ӧߧ֧�ߧڧ� �ӧ�ӧ�է��
// - �� Slave mode: NSS input ����֧է֧ݧ�֧� selected �������ߧڧ�
// - �� Master mode: NSS output �ѧӧ��ާѧ�ڧ�֧�ܧ� ����ѧӧݧ�֧� �ӧ֧է�ާ�ާ�
�����ԧ�ѧާާߧ�� ����ѧӧݧ֧ߧڧ� (SSM = 1, SSI = 1):
c
// NSS ����ѧӧݧ�֧��� ����ԧ�ѧާާߧ�
// - �� Slave mode: ������ۧ��ӧ� �ӧ�֧ԧէ� ���ڧ�ѧ֧��� �ߧ� selected
// - �� Master mode: ���ݧߧ�� �ܧ�ߧ���ݧ� �ߧѧ� ��֧�֧էѧ�֧�
���ڧ�ڧ�ߧ�� �ܧ�ߧ�ڧԧ��ѧ�ڧ�:
Master �� �ѧ��ѧ�ѧ�ߧ�� NSS:
c
SPI1->CTLR1 = SPI_CTLR1_MSTR |   // Master
              SPI_CTLR1_SPE;     // Enable
// SSM = 0 - �ѧ��ѧ�ѧ�ߧ�� ����ѧӧݧ֧ߧڧ�
Master �� ����ԧ�ѧާާߧ�� NSS:
c
SPI1->CTLR1 = SPI_CTLR1_MSTR |   // Master
              SPI_CTLR1_SSM  |   // �����ԧ�ѧާާߧ�� ����ѧӧݧ֧ߧڧ�
              SPI_CTLR1_SSI  |   // NSS = 1
              SPI_CTLR1_SPE;     // Enable
Slave ��֧اڧ�:
c
SPI1->CTLR1 = SPI_CTLR1_SSM  |   // �����ԧ�ѧާާߧ�� ����ѧӧݧ֧ߧڧ�  
              SPI_CTLR1_SSI  |   // NSS = 1 (�ߧ� selected)
              SPI_CTLR1_SPE;     // Enable
// MSTR = 0 - Slave mode
����� �ҧڧ�� ��ҧ֧��֧�ڧӧѧ�� �ԧڧҧܧ�� �ߧѧ����ۧܧ� ��֧اڧާ�� ��ѧҧ��� SPI �� �٧ѧӧڧ�ڧާ���� ��� ���֧ҧ�ӧѧߧڧ� ���ڧݧ�ا֧ߧڧ�.

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
