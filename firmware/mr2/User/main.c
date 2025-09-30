// ===================================================================================
// Project:   Example for CH32X035/X034/X033
// Version:   v1.0
// Year:      2023
// Author:    Sergej Pfaffenrot, based on Stefan Wagner's code
// Github:    https://
// EasyEDA:   https://
// License:   http://creativecommons.org/licenses/by-sa/3.0/
// ===================================================================================
//
// Description:
// ------------
// Blink example.
//
// References:
// -----------
// - WCH Nanjing Qinheng Microelectronics: http://wch.cn
//
// Compilation Instructions:
// -------------------------
// - Make sure GCC toolchain (gcc-riscv64-unknown-elf, newlib) and Python3 with
//   chprog and rvprog (via pip) are installed. In addition, Linux requires access
//   rights to the USB bootloader.
// - Press the BOOT button on the MCU board and keep it pressed while connecting it
//   via USB to your PC.
// - Run 'make flash'.


// ===================================================================================
// Libraries, Definitions and Macros
// ===================================================================================

/*              PIN CONNECTION x033F8P6
 *
 * {7}          GND
 * {9}          Vdd
 *
 * {5} PC16/11  UDM
 * {6} PC17/10  UDP
 *
 * {8} PC18     SWDIO
 * {18}PC19     SWSCK
 *
 * {16}PA2      TX2
 * {17}PA3      RX2
 *
 * {2}PB0       TX4
 * {3}PB1       RX4
 *
 *
 *
 */



#include "system.h"                               // system functions
#include "gpio.h"                                 // GPIO functions
#include "usb_cdc.h"
#include "uart/uart.h"

#include "flash_userdata.h"
#include "print.h"
#include <stdlib.h>
#include "dev_config.h"
#include "cdc_cmd.h"


#define PIN_LED PB1                               // define LED pin

static char cdc_buffer[256];
static int cdc_buffer_len = 0;

#ifndef __code
#define __code const __attribute__((section(".rodata")))
#endif

configuration_t global_conf;


// ===================================================================================
// Main Function
// ===================================================================================
int main(void) {


  // Setup
  PIN_output(PIN_LED);                            // set LED pin to output
  
  CDC_init();
  //UART2_init();
  //UART4_init();

  //**************************************************************


    read_struct_from_flash((char*)&global_conf, sizeof(global_conf));

  //**************************************************************

  // Loop
  while(1) {
    //PIN_toggle(PIN_LED);                          // toggle LED
    //DLY_ms(1);                                      // wait a bit

    //DLY_ms(ud2.boot_count);

    int count = CDC_available();
    if (count ){

        if ( count > sizeof(cdc_buffer))
            count = sizeof(cdc_buffer);


        for (int i = 0; i < count; i++){
            cdc_buffer[i] = CDC_read();

        }
        cdc_buffer_len = count;

        if ( ifcmdexec(cdc_buffer, &global_conf ) ){

            count = 0;
            for(int i = 0; i < sizeof(cdc_buffer); i++ )
                cdc_buffer[i] = 0;

        }

        if ( count > 0 )
            for (int i = 0; i < count; i++){


                char ch = cdc_buffer[i];
                UART2_write( ch );
                //CDC_write( ch ); // for test of buffer

                //UART4_write( ch );
            }
        CDC_flush();

    }

    if ( UART2_available() ){

        CDC_write( UART2_read() );
        CDC_flush();
    }
    /*
    if ( UART4_available() ){

        CDC_write( UART4_read() );
        CDC_flush();
    }
    */

  }
}
