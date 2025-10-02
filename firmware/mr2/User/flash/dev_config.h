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

    uint8_t prescaller:4;
    uint8_t baud:3;
    char master: 1;
    char pha: 1;
    char pol: 1;

} cfg_spi_t;

typedef struct __attribute__((__packed__)){

    uint8_t cdc_uart:1;
    uint8_t uart_cdc:1;

    uint8_t cdc_spi:1;
    uint8_t spi_cdc:1;

    uint8_t cdc_i2c:1;
    uint8_t i2c_cdc:1;

    uint8_t spi_uart:1;
    uint8_t uart_spi:1;

    uint8_t i2c_uart:1;
    uint8_t uart_i2c:1;

    uint8_t spi_i2c:1;
    uint8_t i2c_spi:1;


} transfer_t;

typedef struct __attribute__((__packed__,aligned(4))){

    uint8_t crc;
    cfg_active_intefaces_t active_interfaces;
    cfg_uart_t cfg_uart;
    cfg_spi_t cfg_spi;

    transfer_t trans;

} configuration_t;


#define CFG_CRC_SIZE    (sizeof(configuration_t)-1)

#define CONF_FILL_CRC(x)    x.crc = 
void        onfiguration_init(configuration_t * a_inst);
bool        is_conf_valid(configuration_t * a_inst);
configuration_t conf_read_from_flash();
bool        conf_write_to_flash(configuration_t* a_conf);

void        cfg_uart_init(cfg_uart_t* a_conf);
void        cfg_spi_init(cfg_spi_t* a_conf);
void        cfg_init(configuration_t * a_conf);
void        activate_cfg(configuration_t * a_conf);
uint8_t     calc_cfg_crc(configuration_t * a_conf);

extern configuration_t global_conf;

#ifdef __cplusplus
}
#endif
