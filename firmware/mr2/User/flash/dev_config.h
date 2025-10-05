#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* pins 
 //uart
 PA2
 PA3

 //spi
 PA4
 PA5
 PA6
 PA7

 //i2c
 PA10
 PA11

 //gpio
 PC18
 PC19 //wo
 */ 

#define PIN_UART_RX         1
#define PIN_UART_TX         0

#define PIN_SPI_CS          2
#define PIN_SPI_SCK         3
#define PIN_SPI_MISO        4
#define PIN_SPI_MOSI        5

#define PIN_I2C_SCL         6
#define PIN_I2C_SDA         7

#define PIN_PIN_1           8
#define PIN_PIN_2           9


#define IS_PIN_UART(x)     ((x == 0)||(x == 1))
#define IS_PIN_SPI(x)      ((x == 2)||(x == 3)||(x == 4)||(x == 5))
#define IS_PIN_I2C(x)      ((x == 6)||(x == 7))
#define IS_PIN_PC19(x)      (x == 9)

 #define PINMODE_INP        0
 #define PINMODE_INPPD      1
 #define PINMODE_INPPU      2
 #define PINMODE_INPAN      3
 #define PINMODE_OUT        4     

#define SET_PIN_MODE(pin, mode) \
    ((mode) == 0 ? PIN_input(pin) : \
    ((mode) == 1 ? PIN_input_PD(pin) : \
    ((mode) == 2 ? PIN_input_PU(pin) : \
    ((mode) == 3 ? PIN_input_AN(pin) : \
     (mode) == 4 ? PIN_output(pin) : (void)0))))

#define GET_PIN_BY_INDEX(x) \
    ((x) == PIN_UART_TX ? PA2 : \
     (x) == PIN_UART_RX ? PA3 : \
     (x) == PIN_SPI_CS ? PA4 : \
     (x) == PIN_SPI_SCK ? PA5 : \
     (x) == PIN_SPI_MISO ? PA6 : \
     (x) == PIN_SPI_MOSI ? PA7 : \
     (x) == PIN_I2C_SCL ? PA10 : \
     (x) == PIN_I2C_SDA ? PA11 : \
     (x) == PIN_PIN_1 ? PC18 : \
     (x) == PIN_PIN_2 ? PC19 : 0)     

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
    char hw_cs: 1;
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

typedef struct __attribute__((__packed__)){
    char mode: 4;
    //char interrupt: 4;

} cfg_pin_t;

typedef struct __attribute__((__packed__)){

        cfg_pin_t pa2;
        cfg_pin_t pa3;

        //spi
        cfg_pin_t pa4;
        cfg_pin_t pa5;
        cfg_pin_t pa6;
        cfg_pin_t pa7;

        //i2c
        cfg_pin_t pa10;
        cfg_pin_t pa11;

        //gpio
        cfg_pin_t pc18;
        cfg_pin_t pc19; //wo

} cfg_pins_t;


typedef struct __attribute__((__packed__,aligned(4))){

    uint8_t crc;
    cfg_active_intefaces_t active_interfaces;
    cfg_uart_t cfg_uart;
    cfg_spi_t cfg_spi;

    transfer_t trans;
    cfg_pins_t cfg_pins;

} configuration_t;


#define CFG_CRC_SIZE    (sizeof(configuration_t)-1)

#define CONF_FILL_CRC(x)    x.crc = 
void        onfiguration_init(configuration_t * a_inst);
bool        is_conf_valid(configuration_t * a_inst);
configuration_t conf_read_from_flash();
bool        conf_write_to_flash(configuration_t* a_conf);

void        cfg_uart_init(cfg_uart_t* a_conf);
void        cfg_spi_init(cfg_spi_t* a_conf);
void        cfg_pins_init(cfg_pins_t *a_conf);
void        cfg_init(configuration_t * a_conf);
void        activate_cfg(configuration_t * a_conf);
uint8_t     calc_cfg_crc(configuration_t * a_conf);

extern configuration_t global_conf;

#ifdef __cplusplus
}
#endif
