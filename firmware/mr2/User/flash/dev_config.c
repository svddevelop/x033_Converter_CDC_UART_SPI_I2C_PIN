#include "dev_config.h"
#include "flash_userdata.h"
#include "uart/uart.h"
#include "spi/spi.h"
#include "gpio/gpio.h"

void configuration_init(configuration_t * a_inst){

    a_inst->active_interfaces.uart = true;
    a_inst->active_interfaces.spi = true;
    a_inst->active_interfaces.i2c = true;

    a_inst->cfg_uart.baud = (uint32_t)115200;
}

/*
inline __attribute__((always_inline)) uint8_t conf_calc_crc(configuration_t* a_conf){

    uint8_t* inst = (uint8_t * )a_conf;
    inst++;
    return crc8(inst, CFG_CRC_SIZE);
}
*/
/*
bool is_conf_valid(configuration_t * a_inst){


    uint8_t crc = conf_calc_crc(a_inst);
    return ( a_inst->crc == crc);
}
*/
inline __attribute__((always_inline)) void  cfg_uart_init(cfg_uart_t* a_conf){

    a_conf->baud = 115200;

}

inline __attribute__((always_inline)) void  cfg_spi_init(cfg_spi_t* a_conf){

    a_conf->baud            = 2;
    a_conf->master          = 1;
    a_conf->pha             = 0;
    a_conf->pol             = 0;
    a_conf->prescaller      = SPI_PRESC;
    
}

inline __attribute__((always_inline)) void  cfg_init(configuration_t * a_conf){

    a_conf->active_interfaces.i2c       = 0;
    a_conf->active_interfaces.spi       = 0;
    a_conf->active_interfaces.uart      = 1;

    cfg_uart_init( &a_conf->cfg_uart );
    cfg_spi_init( &a_conf->cfg_spi );

    a_conf->trans.cdc_i2c               = 1;
    a_conf->trans.cdc_spi               = 1;
    a_conf->trans.cdc_uart              = 1;
    a_conf->trans.uart_cdc              = 1;
    a_conf->trans.uart_i2c              = 0;
    a_conf->trans.uart_spi              = 0;
    a_conf->trans.spi_uart              = 0;
    a_conf->trans.spi_cdc               = 1;
    a_conf->trans.spi_i2c               = 0;
    a_conf->trans.i2c_cdc               = 1;
    a_conf->trans.i2c_spi               = 0;
    a_conf->trans.i2c_uart              = 0;

    cfg_pins_init( &a_conf->cfg_pins );

    a_conf->crc = calc_cfg_crc(a_conf);
    
}


void  activate_cfg_pin(uint8_t a_idx, uint32_t a_mode){

    
    SET_PIN_MODE( GET_PIN_BY_INDEX(a_idx), a_mode) ;

}


inline __attribute__((always_inline)) void  activate_cfg(configuration_t * a_conf){

    if (a_conf->active_interfaces.uart != 0){

        #ifdef UART_WITH_IRQ
        
        UART2_Init2( a_conf->cfg_uart.baud );

        #endif

        #ifndef UART_WITH_IRQ

        UART2_setBAUD( a_conf->cfg_uart.baud );

        UART2_enable();
        
        #endif

    } else {

        UART2_disable();
        activate_cfg_pin(PIN_UART_TX, a_conf->cfg_pins.pa2.mode );
        activate_cfg_pin(PIN_UART_RX, a_conf->cfg_pins.pa3.mode );
    }


    if (a_conf->active_interfaces.spi != 0){

        SPI_disable(); //befor changes for any flags, need to deactivate SPI

        SPI_setBAUD(a_conf->cfg_spi.baud);
        SPI_init_ext( 
                  a_conf->cfg_spi.master
                , a_conf->cfg_spi.hw_cs
                , a_conf->cfg_spi.prescaller
                , a_conf->cfg_spi.pha
                , a_conf->cfg_spi.pol
        );

        SPI_enable();
    } else {

        SPI_disable();
        activate_cfg_pin(PIN_SPI_CS, a_conf->cfg_pins.pa4.mode );
        activate_cfg_pin(PIN_SPI_SCK, a_conf->cfg_pins.pa5.mode );
        activate_cfg_pin(PIN_SPI_MISO, a_conf->cfg_pins.pa6.mode );
        activate_cfg_pin(PIN_SPI_MOSI, a_conf->cfg_pins.pa7.mode );

    }   


} 

 uint8_t  calc_cfg_crc(configuration_t * a_conf){

    uint8_t *buf = (uint8_t *)a_conf;
    buf += 1;
    uint8_t crc = crc8( buf, sizeof(configuration_t)-1);
    return crc;
}


inline __attribute__((always_inline)) void  cfg_pin_init(cfg_pin_t * a_conf){

    a_conf->mode            = PINMODE_INP;
    //a_conf->interrupt       = PIN_INT_OFF;

}

inline __attribute__((always_inline)) void  cfg_pins_init(cfg_pins_t *a_conf){

    cfg_pin_init( &a_conf->pa10);
    cfg_pin_init( &a_conf->pa11 );
    cfg_pin_init( &a_conf->pa2 );
    cfg_pin_init( &a_conf->pa3 );
    cfg_pin_init( &a_conf->pa4 );
    cfg_pin_init( &a_conf->pa5 );
    cfg_pin_init( &a_conf->pa6 );
    cfg_pin_init( &a_conf->pa7 );
    cfg_pin_init( &a_conf->pc18 );
   
    a_conf->pc19.mode = PINMODE_OUT;

}