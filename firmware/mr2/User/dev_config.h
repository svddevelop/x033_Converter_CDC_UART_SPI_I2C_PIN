#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <stdbool.h>

typedef struct __attribute__((__packed__)){
    char uart:1;
    char spi:1;
    char i2c:1;
} cfg_active_intefaces_t;

typedef struct __attribute__((__packed__)){
    uint32_t baud;

} cfg_uart_t;

typedef struct __attribute__((__packed__)){
    uint8_t crc;
    cfg_active_intefaces_t active_interfaces;
    cfg_uart_t cfg_uart;

} configuration_t;


#define CFG_CRC_SIZE    (sizeof(configuration_t)-1)

#define CONF_FILL_CRC(x)    x.crc = 
void configuration_init(configuration_t * a_inst);
bool is_conf_valid(configuration_t * a_inst);
configuration_t conf_read_from_flash();
bool conf_write_to_flash(configuration_t* a_conf);


extern configuration_t global_conf;



#ifdef __cplusplus
}
#endif
