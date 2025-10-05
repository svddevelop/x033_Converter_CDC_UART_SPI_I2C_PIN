#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "flash/dev_config.h"

#ifndef __code
#define __code const __attribute__((section(".rodata")))
#endif

bool ifcmdexec(char* a_buf, configuration_t* a_conf);

void process_cdc(configuration_t * a_conf, char * a_cdc_buf, uint16_t * a_len);
void process_uart(configuration_t * a_conf );

int parse_hex_config(const char* dev, const char* ek, char * hex_buf, int hex_buf_size);


#ifdef __cplusplus
}
#endif
