#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "dev_config.h"

#ifndef __code
#define __code const __attribute__((section(".rodata")))
#endif

bool ifcmdexec(char* a_buf, configuration_t* a_conf);


#ifdef __cplusplus
}
#endif
