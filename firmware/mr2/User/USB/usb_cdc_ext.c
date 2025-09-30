#include "usb_cdc_ext.h"

// Write buffer to OUT buffer
void CDC_writeBuffer(const char *buffer, uint16_t size) {
    for (uint16_t i = 0; i < size; i++) {
        while(CDC_writeBusyFlag);                             // wait for ready to write
        EP2_buffer[64 + CDC_writePointer++] = buffer[i];      // write character
        
        if(CDC_writePointer == EP2_SIZE) {
            CDC_flush();                                      // flush if buffer full
        }
    }
}

// ���ݧ��֧�ߧѧ�ڧӧߧѧ� ����ڧާڧ٧ڧ��ӧѧߧߧѧ� �ӧ֧��ڧ� �� ��ѧܧ֧�ߧ�� �٧ѧ�ڧ���
void CDC_writeBufferOptimized(const char *buffer, uint16_t size) {
    uint16_t bytes_written = 0;
    
    while (bytes_written < size) {
        // Calculate available space in current buffer
        uint16_t available = EP2_SIZE - CDC_writePointer;
        uint16_t to_write = (size - bytes_written) < available ? 
                           (size - bytes_written) : available;
        
        // Wait if buffer is busy
        while(CDC_writeBusyFlag);
        
        // Copy data to buffer
        for (uint16_t i = 0; i < to_write; i++) {
            EP2_buffer[64 + CDC_writePointer++] = buffer[bytes_written + i];
        }
        
        bytes_written += to_write;
        
        // Flush if buffer is full
        if (CDC_writePointer == EP2_SIZE) {
            CDC_flush();
        }
    }
}