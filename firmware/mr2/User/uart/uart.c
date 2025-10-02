// ===================================================================================
// Basic UART Functions for CH32X035/X034/X033  (no buffer/interrupt/DMA)     * v1.0 *
// ===================================================================================
// 2023 by Stefan Wagner:   https://github.com/wagiminator

#include "uart.h"

// ===================================================================================
// UART1
// ===================================================================================

// Init UART
void UART1_init(void) {
#if UART1_REMAP == 0
  // Enable GPIO port B and UART
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPBEN | RCC_USART1EN;

  // Set pin PB10 (TX) to output, push-pull, alternate
  // Set pin PB11 (RX) to input, pullup
  GPIOB->CFGHR = (GPIOB->CFGHR & ~(((uint32_t)0b1111<<(2<<2)) | ((uint32_t)0b1111<<(3<<2))))
                               |  (((uint32_t)0b1011<<(2<<2)) | ((uint32_t)0b1000<<(3<<2)));
  GPIOB->BSHR  = (uint32_t)1<<11;
#elif UART1_REMAP == 1
  // Enable GPIO port A and UART
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPAEN | RCC_USART1EN;

  // Set pin PA10 (TX) to output, push-pull, alternate
  // Set pin PA11 (RX) to input, pullup
  GPIOA->CFGHR = (GPIOA->CFGHR & ~(((uint32_t)0b1111<<(2<<2)) | ((uint32_t)0b1111<<(3<<2))))
                               |  (((uint32_t)0b1011<<(2<<2)) | ((uint32_t)0b1000<<(3<<2)));
  GPIOA->BSHR  = (uint32_t)1<<11;
  AFIO->PCFR1 |= (uint32_t)0b01<<5;
#elif UART1_REMAP == 2
  // Enable GPIO port B and UART
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPBEN | RCC_USART1EN;

  // Set pin PB10 (TX) to output, push-pull, alternate
  // Set pin PB11 (RX) to input, pullup
  GPIOB->CFGHR = (GPIOB->CFGHR & ~(((uint32_t)0b1111<<(2<<2)) | ((uint32_t)0b1111<<(3<<2))))
                               |  (((uint32_t)0b1011<<(2<<2)) | ((uint32_t)0b1000<<(3<<2)));
  GPIOB->BSHR  = (uint32_t)1<<11;
  AFIO->PCFR1 |= (uint32_t)0b10<<5;
#elif UART1_REMAP == 3
  // Enable GPIO port A/B and UART
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPAEN | RCC_IOPBEN | RCC_USART1EN;

  // Set pin PA7 (TX) to output, push-pull, alternate
  // Set pin PB2 (RX) to input, pullup
  GPIOA->CFGLR = (GPIOA->CFGLR & ~((uint32_t)0b1111<<(7<<2))) | ((uint32_t)0b1011<<(7<<2));
  GPIOB->CFGLR = (GPIOB->CFGLR & ~((uint32_t)0b1111<<(2<<2))) | ((uint32_t)0b1000<<(2<<2));
  GPIOB->BSHR  = (uint32_t)1<<2;
  AFIO->PCFR1 |= (uint32_t)0b11<<5;
#else
  #warning No USART1 REMAP
#endif
	
  // Setup and start UART (8N1, RX/TX, default BAUD rate)
  USART1->BRR   = ((2 * F_CPU / UART1_BAUD) + 1) / 2;
  USART1->CTLR1 = USART_CTLR1_RE | USART_CTLR1_TE | USART_CTLR1_UE;
}

// Read byte via UART
char UART1_read(void) {
  while(!UART1_available());
  return USART1->DATAR;
}

// Send byte via UART
void UART1_write(const char c) {
  while(!UART1_ready());
  USART1->DATAR = c;
}

// ===================================================================================
// UART2
// ===================================================================================

// Init UART

void UART2_init(uint16_t a_baud) {

#if UART2_REMAP == 0
  // Set pin PA2 (TX) to output, push-pull, alternate
  // Set pin PA3 (RX) to input, pullup
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPAEN;
  GPIOA->CFGLR    = (GPIOA->CFGLR & ~(((uint32_t)0b1111<<(2<<2)) | ((uint32_t)0b1111<<(3<<2))))
                                  |  (((uint32_t)0b1011<<(2<<2)) | ((uint32_t)0b1000<<(3<<2)));
  GPIOA->BSHR     = (uint32_t)1<<3;
#elif UART2_REMAP == 1 
  // Set pin PA20 (TX) to output, push-pull, alternate
  // Set pin PA19 (RX) to input, pullup
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPAEN;
  GPIOA->CFGXR    = (GPIOA->CFGXR & ~(((uint32_t)0b1111<<(4<<2)) | ((uint32_t)0b1111<<(3<<2))))
                                  |  (((uint32_t)0b1011<<(4<<2)) | ((uint32_t)0b1000<<(3<<2)));
  GPIOA->BSXR     = (uint32_t)1<<3;
  AFIO->PCFR1    |= (uint32_t)0b001<<7;
#elif UART2_REMAP == 2 
  // Set pin PA15 (TX) to output, push-pull, alternate
  // Set pin PA16 (RX) to input, pullup
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPAEN;
  GPIOA->CFGHR    = (GPIOA->CFGHR & ~((uint32_t)0b1111<<(7<<2))) | ((uint32_t)0b1011<<(7<<2)));
  GPIOA->CFGXR    = (GPIOA->CFGXR & ~((uint32_t)0b1111<<(0<<2))) | ((uint32_t)0b1000<<(0<<2)));
  GPIOA->BSXR     = (uint32_t)1<<0;
  AFIO->PCFR1    |= (uint32_t)0b010<<7;
#elif UART2_REMAP == 3
  // Set pin PC0 (TX) to output, push-pull, alternate
  // Set pin PC1 (RX) to input, pullup
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPCEN;
  GPIOC->CFGLR    = (GPIOC->CFGLR & ~(((uint32_t)0b1111<<(0<<2)) | ((uint32_t)0b1111<<(1<<2))))
                                  |  (((uint32_t)0b1011<<(0<<2)) | ((uint32_t)0b1000<<(1<<2)));
  GPIOC->BSHR     = (uint32_t)1<<1;
  AFIO->PCFR1    |= (uint32_t)0b011<<7;
#elif UART2_REMAP == 4 
  // Set pin PA15 (TX) to output, push-pull, alternate
  // Set pin PA16 (RX) to input, pullup
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPAEN;
  GPIOA->CFGHR    = (GPIOA->CFGHR & ~((uint32_t)0b1111<<(7<<2))) | ((uint32_t)0b1011<<(7<<2)));
  GPIOA->CFGXR    = (GPIOA->CFGXR & ~((uint32_t)0b1111<<(0<<2))) | ((uint32_t)0b1000<<(0<<2)));
  GPIOA->BSXR     = (uint32_t)1<<0;
  AFIO->PCFR1    |= (uint32_t)0b100<<7;
#else
  #warning No USART2 REMAP
#endif
	
  // Setup and start UART (8N1, RX/TX, default BAUD rate)
  RCC->APB1PCENR |= RCC_USART2EN;
  //USART2->BRR     = ((2 * F_CPU / UART2_BAUD) + 1) / 2;
  USART2->BRR     = ((2 * F_CPU / a_baud) + 1) / 2;
  USART2->CTLR1   = USART_CTLR1_RE | USART_CTLR1_TE | USART_CTLR1_UE;

}// UART2_init()

#ifdef UART_WITH_IRQ

void UART2_Init2(uint32_t a_baud) {

#if UART2_REMAP == 0
  // Set pin PA2 (TX) to output, push-pull, alternate
  // Set pin PA3 (RX) to input, pullup
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPAEN;
  GPIOA->CFGLR    = (GPIOA->CFGLR & ~(((uint32_t)0b1111<<(2<<2)) | ((uint32_t)0b1111<<(3<<2))))
                                  |  (((uint32_t)0b1011<<(2<<2)) | ((uint32_t)0b1000<<(3<<2)));
  GPIOA->BSHR     = (uint32_t)1<<3;
#else
  #warning No USART2 REMAP
#endif	
  // Setup and start UART (8N1, RX/TX, default BAUD rate)
  RCC->APB1PCENR |= RCC_USART2EN;
  //#define FCPU  (8000000)
  #define FCPU  (F_CPU)
  USART2->BRR     = ((2*FCPU/(a_baud))+1)/2;

  USART2->CTLR1   = USART_CTLR1_RE | USART_CTLR1_TE | USART_CTLR1_UE;

  // Enable interrupts for RX and TX
  USART2->CTLR1 |= USART_CTLR1_RXNEIE | USART_CTLR1_TXEIE;
  
  // Configure NVIC for USART2 interrupts
  NVIC_EnableIRQ(USART2_IRQn);
  NVIC_SetPriority(USART2_IRQn, 2);

 


}// UART2_Init2()

uint8_t uart2_rx_buf[256];
uint8_t uart2_tx_buf[256];
uart_handler_t uart2_handler = {
    .rx_buf = uart2_rx_buf,
    .rx_len = 0,
    .tx_buf = uart2_tx_buf,
    .tx_len = 0,
    .tx_pos = 0,
    .rx_transaction = 0,
    .tx_transaction = 0,
    .uart = USART2
};

void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART2_IRQHandler(void) {

    
    if (USART2->STATR & USART_STATR_RXNE) {

        uart2_handler.rx_transaction = 1; 
        
        uint8_t data = USART2->DATAR;
        if (uart2_handler.rx_len < sizeof(uart2_rx_buf)) {
            uart2_handler.rx_buf[uart2_handler.rx_len++] = data;
        }
        
        uart2_handler.rx_transaction = 0; 
        USART2->STATR &= ~USART_STATR_RXNE;

    }
    
    
    if (USART2->STATR & USART_STATR_TXE) {

        uart2_handler.tx_transaction = 1; 
        
        if (uart2_handler.tx_pos < uart2_handler.tx_len) {
            USART2->DATAR = uart2_handler.tx_buf[uart2_handler.tx_pos++];
        } else {
            
            USART2->CTLR1 &= ~USART_CTLR1_TXEIE;
            uart2_handler.tx_len = 0;
            uart2_handler.tx_pos = 0;
        }
        
        uart2_handler.tx_transaction = 0; 
        USART2->STATR &= ~USART_STATR_TXE;

    }
}


void uart_start_tx(volatile uart_handler_t *handler, char *data, uint16_t len) {

    while (handler->tx_transaction);     
   
    for (uint16_t i = 0; i < len && i < sizeof(uart2_tx_buf); i++) {
        handler->tx_buf[i] = data[i];
    }
    
    handler->tx_len = len;
    handler->tx_pos = 0;    
    
    handler->uart->CTLR1 |= USART_CTLR1_TXEIE;
}


uint16_t uart_get_rx_data(volatile uart_handler_t *handler, char *buffer, uint16_t max_len) {

    while (handler->rx_transaction); 
    
    uint16_t copy_len = (handler->rx_len < max_len) ? handler->rx_len : max_len;
    for (uint16_t i = 0; i < copy_len; i++) {
        buffer[i] = handler->rx_buf[i];
    }
    
    uint16_t ret_len = handler->rx_len;
    handler->rx_len = 0; 
    
    return ret_len;
}


void uart_clear_rx_buffer(volatile uart_handler_t *handler) {

    while (handler->rx_transaction); 
    handler->rx_len = 0;
}

#endif

//////////////////////////////////////////////////////////////////////////////////

//*******************************************************************************
#ifdef UART_WITH_IRQ_DMA

// UART2 interrupt handler - RX only
void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART2_IRQHandler(void) {
    // Handle RX interrupt
    if (USART2->STATR & USART_STATR_RXNE) {
        uart2_handler.rx_transaction = 1; // Start RX transaction
        
        uint8_t data = USART2->DATAR;
        if (uart2_handler.rx_len < sizeof(uart2_rx_buf)) {
            uart2_handler.rx_buf[uart2_handler.rx_len++] = data;
        }
        
        uart2_handler.rx_transaction = 0; // End RX transaction
        USART2->STATR &= ~USART_STATR_RXNE;
    }
}

// Initialize DMA for UART2 TX
void UART2_DMA_Init(void) {
    // Enable DMA clock
    RCC->AHBPCENR |= RCC_DMA1EN;
    
    // DMA configuration for UART2 TX (Channel 7 for USART2_TX)
    DMA1_Channel7->PADDR = (uint32_t)&USART2->DATAR;  // Peripheral address
    DMA1_Channel7->MADDR = (uint32_t)uart2_tx_buf;    // Memory address
    DMA1_Channel7->CNTR = 0;                          // Data counter
    DMA1_Channel7->CFGR = 0;                          // Reset config
    
    // Configure DMA
    DMA1_Channel7->CFGR = DMA_CFGR1_MEM2MEM   |  // Memory to memory disabled
                          DMA_CFGR1_PL        |  // High priority
                          DMA_CFGR1_MSIZE_0   |  // Memory data size: 8-bit
                          DMA_CFGR1_PSIZE_0   |  // Peripheral data size: 8-bit
                          DMA_CFGR1_MINC      |  // Memory increment
                          DMA_CFGR1_PINC      |  // Peripheral increment disabled
                          DMA_CFGR1_CIRC      |  // Circular mode disabled
                          DMA_CFGR1_DIR;         // Direction: memory to peripheral
    
    // Enable DMA transfer complete interrupt
    DMA1_Channel7->CFGR |= DMA_CFGR1_TCIE;
    
    // Enable DMA channel
    DMA1_Channel7->CFGR |= DMA_CFGR1_EN;
    
    // Enable DMA interrupt in NVIC
    NVIC_EnableIRQ(DMA1_Channel7_IRQn);
    NVIC_SetPriority(DMA1_Channel7_IRQn, 1);
    
    // Enable DMA for USART2 TX
    USART2->CTLR3 |= USART_CTLR3_DMAT;
}

// Start TX transmission using DMA
void uart_start_tx_dma(volatile uart_handler_t *handler, const uint8_t *data, uint16_t len) {
    // Wait for previous DMA transfer to complete
    while (DMA1_Channel7->CFGR & DMA_CFGR1_EN);
    
    // Copy data to transmit buffer
    uint16_t copy_len = (len < sizeof(uart2_tx_buf)) ? len : sizeof(uart2_tx_buf);
    for (uint16_t i = 0; i < copy_len; i++) {
        handler->tx_buf[i] = data[i];
    }
    
    handler->tx_len = copy_len;
    
    // Configure DMA transfer
    DMA1_Channel7->MADDR = (uint32_t)handler->tx_buf;  // Set memory address
    DMA1_Channel7->CNTR = copy_len;                    // Set data count
    DMA1_Channel7->CFGR |= DMA_CFGR1_EN;               // Enable DMA channel
}

// DMA1 Channel7 interrupt handler (TX complete)
void DMA1_Channel7_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void DMA1_Channel7_IRQHandler(void) {
    // Check for transfer complete interrupt
    if (DMA1->INTFR & DMA_FLAG_TC7) {
        // Clear transfer complete flag
        DMA1->INTFR &= ~DMA_FLAG_TC7;
        
        // Disable DMA channel after transfer complete
        DMA1_Channel7->CFGR &= ~DMA_CFGR1_EN;
        
        // Optional: Add callback or flag for TX complete
        // uart2_handler.tx_complete = 1;
    }
}

// Get received data from RX buffer
uint16_t uart_get_rx_data(volatile uart_handler_t *handler, uint8_t *buffer, uint16_t max_len) {
    while (handler->rx_transaction); // Wait for RX transaction to complete
    
    uint16_t copy_len = (handler->rx_len < max_len) ? handler->rx_len : max_len;
    for (uint16_t i = 0; i < copy_len; i++) {
        buffer[i] = handler->rx_buf[i];
    }
    
    uint16_t ret_len = handler->rx_len;
    handler->rx_len = 0; // Reset counter
    
    return ret_len;
}

// Clear RX buffer
void uart_clear_rx_buffer(volatile uart_handler_t *handler) {
    while (handler->rx_transaction); // Wait for RX transaction to complete
    handler->rx_len = 0;
}

// Check if DMA TX is in progress
uint8_t uart_tx_busy(void) {
    return (DMA1_Channel7->CFGR & DMA_CFGR1_EN) ? 1 : 0;
}

#endif

//*******************************************************************************

// Read byte via UART
char UART2_read(void) {
  while(!UART2_available());
  return USART2->DATAR;
}

// Send byte via UART
void UART2_write(const char c) {
  while(!UART2_ready());
  USART2->DATAR = c;
}

// ===================================================================================
// UART3
// ===================================================================================

// Init UART
void UART3_init(void) {
#if UART3_REMAP == 0
  // Set pin PB3 (TX) to output, push-pull, alternate
  // Set pin PB4 (RX) to input, pullup
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPBEN;
  GPIOB->CFGLR    = (GPIOB->CFGLR & ~(((uint32_t)0b1111<<(3<<2)) | ((uint32_t)0b1111<<(4<<2))))
                                  |  (((uint32_t)0b1011<<(3<<2)) | ((uint32_t)0b1000<<(4<<2)));
  GPIOB->BSHR     = (uint32_t)1<<4;
#elif UART3_REMAP == 1 
  // Set pin PC18 (TX) to output, push-pull, alternate
  // Set pin PC19 (RX) to input, pullup
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPCEN;
  GPIOC->CFGXR    = (GPIOC->CFGXR & ~(((uint32_t)0b1111<<(2<<2)) | ((uint32_t)0b1111<<(3<<2))))
                                  |  (((uint32_t)0b1011<<(2<<2)) | ((uint32_t)0b1000<<(3<<2)));
  GPIOC->BSXR     = (uint32_t)1<<3;
  AFIO->PCFR1    |= (uint32_t)0b01<<10;
#elif UART3_REMAP == 2 
  // Set pin PA18 (TX) to output, push-pull, alternate
  // Set pin PB14 (RX) to input, pullup
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPAEN | RCC_IOPBEN;
  GPIOA->CFGXR    = (GPIOA->CFGXR & ~((uint32_t)0b1111<<(2<<2))) | ((uint32_t)0b1011<<(2<<2)));
  GPIOB->CFGHR    = (GPIOB->CFGHR & ~((uint32_t)0b1111<<(6<<2))) | ((uint32_t)0b1000<<(6<<2)));
  GPIOB->BSHR     = (uint32_t)1<<14;
  AFIO->PCFR1    |= (uint32_t)0b10<<10;
#else
  #warning No USART3 REMAP
#endif
	
  // Setup and start UART (8N1, RX/TX, default BAUD rate)
  RCC->APB1PCENR |= RCC_USART3EN;
  USART3->BRR     = ((2 * F_CPU / UART3_BAUD) + 1) / 2;
  USART3->CTLR1   = USART_CTLR1_RE | USART_CTLR1_TE | USART_CTLR1_UE;
}

// Read byte via UART
char UART3_read(void) {
  while(!UART3_available());
  return USART3->DATAR;
}

// Send byte via UART
void UART3_write(const char c) {
  while(!UART3_ready());
  USART3->DATAR = c;
}

// ===================================================================================
// UART4
// ===================================================================================

// Init UART
void UART4_init(uint16_t a_baud) {

#if UART4_REMAP == 0
  // Set pin PB0 (TX) to output, push-pull, alternate
  // Set pin PB1 (RX) to input, pullup
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPBEN;
  GPIOB->CFGLR    = (GPIOB->CFGLR & ~(((uint32_t)0b1111<<(0<<2)) | ((uint32_t)0b1111<<(1<<2))))
                                  |  (((uint32_t)0b1011<<(0<<2)) | ((uint32_t)0b1000<<(1<<2)));
  GPIOB->BSHR     = (uint32_t)1<<1;
#elif UART4_REMAP == 1 
  // Set pin PA5 (TX) to output, push-pull, alternate
  // Set pin PA9 (RX) to input, pullup
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPAEN;
  GPIOA->CFGLR    = (GPIOA->CFGLR & ~((uint32_t)0b1111<<(5<<2))) | ((uint32_t)0b1011<<(5<<2)));
  GPIOA->CFGHR    = (GPIOA->CFGHR & ~((uint32_t)0b1111<<(1<<2))) | ((uint32_t)0b1000<<(1<<2)));
  GPIOA->BSHR     = (uint32_t)1<<9;
  AFIO->PCFR1    |= (uint32_t)0b001<<12;
#elif UART4_REMAP == 2 
  // Set pin PC16 (TX) to output, push-pull, alternate
  // Set pin PC17 (RX) to input, pullup
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPCEN;
  GPIOC->CFGXR    = (GPIOC->CFGXR & ~(((uint32_t)0b1111<<(0<<2)) | ((uint32_t)0b1111<<(1<<2))))
                                  |  (((uint32_t)0b1011<<(0<<2)) | ((uint32_t)0b1000<<(1<<2)));
  GPIOC->BSXR     = (uint32_t)1<<1;
  AFIO->PCFR1    |= (uint32_t)0b010<<12;
#elif UART4_REMAP == 3
  // Set pin PB9  (TX) to output, push-pull, alternate
  // Set pin PA10 (RX) to input, pullup
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPAEN | RCC_IOPBEN;
  GPIOB->CFGHR    = (GPIOB->CFGHR & ~((uint32_t)0b1111<<(1<<2))) | ((uint32_t)0b1011<<(1<<2)));
  GPIOA->CFGHR    = (GPIOA->CFGHR & ~((uint32_t)0b1111<<(2<<2))) | ((uint32_t)0b1000<<(2<<2)));
  GPIOA->BSHR     = (uint32_t)1<<10;
  AFIO->PCFR1    |= (uint32_t)0b011<<12;
#elif UART4_REMAP == 4 
  // Set pin PB13 (TX) to output, push-pull, alternate
  // Set pin PC19 (RX) to input, pullup
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPBEN | RCC_IOPCEN;
  GPIOB->CFGHR    = (GPIOB->CFGHR & ~((uint32_t)0b1111<<(5<<2))) | ((uint32_t)0b1011<<(5<<2)));
  GPIOC->CFGXR    = (GPIOC->CFGXR & ~((uint32_t)0b1111<<(3<<2))) | ((uint32_t)0b1000<<(3<<2)));
  GPIOC->BSXR     = (uint32_t)1<<3;
  AFIO->PCFR1    |= (uint32_t)0b100<<12;
#elif UART4_REMAP == 5 
  // Set pin PC17 (TX) to output, push-pull, alternate
  // Set pin PC16 (RX) to input, pullup
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPCEN;
  GPIOC->CFGXR    = (GPIOC->CFGXR & ~(((uint32_t)0b1111<<(1<<2)) | ((uint32_t)0b1111<<(0<<2))))
                                  |  (((uint32_t)0b1011<<(1<<2)) | ((uint32_t)0b1000<<(0<<2)));
  GPIOC->BSXR     = (uint32_t)1<<0;
  AFIO->PCFR1    |= (uint32_t)0b101<<12;
#else
  #warning No USART4 REMAP
#endif
	
  // Setup and start UART (8N1, RX/TX, default BAUD rate)
  RCC->APB1PCENR |= RCC_USART4EN;
  //USART4->BRR     = ((2 * F_CPU / UART4_BAUD) + 1) / 2;
  USART4->BRR     = ((2 * F_CPU / a_baud) + 1) / 2;
  USART4->CTLR1   = USART_CTLR1_RE | USART_CTLR1_TE | USART_CTLR1_UE;

}//void UART4_init(void)

// Read byte via UART
char UART4_read(void) {
  while(!UART4_available());
  return USART4->DATAR;
}

// Send byte via UART
void UART4_write(const char c) {
  while(!UART4_ready());
  USART4->DATAR = c;
}
