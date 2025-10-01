#include "dev_config.h"
#include "flash_userdata.h"
#include "uart/uart.h"
#include "spi/spi.h"

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
    a_conf->active_interfaces.uart      = 0;

    cfg_uart_init( &a_conf->cfg_uart );
    cfg_spi_init( &a_conf->cfg_spi );

    a_conf->crc = calc_cfg_crc(a_conf);
    
}

inline __attribute__((always_inline)) void  activate_cfg(configuration_t * a_conf){

    if (a_conf->active_interfaces.uart != 0){

        UART2_setBAUD( a_conf->cfg_uart.baud );

        UART2_enable();
    } else {

        UART2_disable();
        // pin initialization
    }


    if (a_conf->active_interfaces.spi != 0){

        SPI_setBAUD(a_conf->cfg_spi.baud);
        SPI_init_ext( 
                a_conf->cfg_spi.master
                , a_conf->cfg_spi.prescaller
                , a_conf->cfg_spi.pha
                , a_conf->cfg_spi.pol
        );

        SPI_enable();
    } else {

        SPI_disable();
        // pin initialization
    }   
} 

/*inline __attribute__((always_inline))*/ uint8_t  calc_cfg_crc(configuration_t * a_conf){

    uint8_t *buf = (uint8_t *)a_conf;
    buf += 1;
    uint8_t crc = crc8( buf, sizeof(configuration_t)-1);
    return crc;
}
