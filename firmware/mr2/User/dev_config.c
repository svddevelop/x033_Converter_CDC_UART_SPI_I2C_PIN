#include "dev_config.h"
#include "flash_userdata.h"
#include "uart/uart.h"

void configuration_init(configuration_t * a_inst){

    a_inst->active_interfaces.uart = true;
    a_inst->active_interfaces.spi = true;
    a_inst->active_interfaces.i2c = true;

    a_inst->cfg_uart.baud = (uint32_t)115200;
}

inline __attribute__((always_inline)) uint8_t conf_calc_crc(configuration_t* a_conf){

    uint8_t* inst = (uint8_t * )a_conf;
    inst++;
    return crc8(inst, CFG_CRC_SIZE);
}

bool is_conf_valid(configuration_t * a_inst){


    uint8_t crc = conf_calc_crc(a_inst);
    return ( a_inst->crc == crc);
}
