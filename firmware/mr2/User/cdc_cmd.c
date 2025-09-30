#include "cdc_cmd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <strings.h>
#include "usb_cdc.h"
#include "uart/uart.h"
#include "flash_userdata.h"

__code char c_cmd_save[] =              "SAVE";
__code char c_cmd_load[] =              "LOAD";
__code char c_cmd_sh_r[] =              "\r";
__code char c_val_dec[] =               "=%d";
__code char c_cmd_print[] =             "-print";
__code char c_cmd_help[] =              "-help";
__code char c_cmd_helpuart[] =          "-helpuart";
__code char c_cmd_helpspi[] =           "-helpspi";
__code char c_cmd_helpi2c[] =           "-helpi2c";
__code char c_cmd_helppin[] =           "-helppin";
__code char c_cmd_set[] =               "[SET:";
__code char c_dev_uart[] =              "UART";
__code char c_dev_spi[] =               "SPI";
__code char c_dev_i2c[] =               "I2C";
__code char c_dev_pin[] =               "PIN";
__code char c_dev_cdc[] =               "CDC";
__code char c_par_baud[] =              ".BAUD";
__code char c_par_en[] =                ".EN";
__code char c_par_dis[] =               ".DIS";
__code char c_rnt_active[] =            ":\r\n\tactive:";
__code char c_rnt[]    =                "\r\n\t";
__code char c_rn[]    =                 "\r\n";

__code char c_msg_help1[] =             "help message;\r\nver 1.1\r\n"
                                        "\t-helpuart\t- shows information about setup of uart;\r\n"
                                        "\t-helpspi\t- shows information about spi;\r\n"
                                        "\t-helpi2c\t\t- how to setup i2c;\r\n"
                                        "\t-helppin\t- how to control pins;\r\n"
                                        "\t[SAVE]\t- save current confuguration to a flash memory;\r\n"
                                        "\t[LOAD]\t- load confuguration from a flash memory.\r\n"
                                        ;
__code char c_msg_helpuart[] =
                                        "\t[SET:UART.<param>=<value>]\r\n"
                                        "\t\t<dev> - device from these list: UART, SPI, I2C, CDC, PIN.\r\n"
                                        "\t\t\tparameter for device UART:\r\n"
                                        "\t\t\t\tBAUD with numerec value(default is 115200)\r\n"
                                        "\r\n[SET:UART.BAUD=9600]\t- set up baud 9600\r\n"
                                        "\r\n[SET:UART.EN]\t- enable UART, disable pins\r\n"
                                        "\r\n[SET:UART.DIS]\t- disable UART, enable pins\r\n"
                                        " -o-o-o-o---+-T-R--- \r\n"
                                        "|\t\t    |\r\n"
                                        "]\t#\t    |\r\n"
                                        "|\t\t    |\r\n"
                                        " -o-o-o-o---o-o-o-o- \r\n"
                                        ;
__code char c_msg_helpspi[] =
                                        "\t[SET:<dev>.<param>=<value>]\r\n"
                                        "\t\t<dev> - device from these list: UART, SPI, I2C, CDC, PIN.\r\n"
                                        "\t\t\tparameter for device UART:\r\n"
                                        "\t\t\t\tBAUD with numerec value(default is 115200)\r\n"
                                        "\r\n[SET:SPI.SPEED=9600]\t- set up baud 9600\r\n"
                                        "\r\n[SET:SPI.EN]\t- enable UART, disable pins\r\n"
                                        "\r\n[SET:SPI.DIS]\t- disable UART, enable pins\r\n"
                                        " -o-o-o-o---o-o-o-o- \r\n"
                                        "|\t\t    |\r\n"
                                        "]\t#\t    |\r\n"
                                        "|\t\t    |\r\n"
                                        " _+_o_o_-___o_o_o_o_ \r\n"
                                        ;
__code char c_msg_help2[] =
                                        ""
                                        ;


#define _SIOZEOFMSG(x)      (sizeof(x)-1)
#define _MEMCMP(x)          memcmp(a_buf,x,_SIOZEOFMSG(x))

inline __attribute__((always_inline)) bool ifcmdexec(char* a_buf, configuration_t* a_conf){

    char* eoc = strstr(a_buf, c_cmd_sh_r); //end of command
    if ( eoc != NULL ){

        char* cmd_set = strstr(a_buf, c_cmd_set);
        if ( cmd_set != NULL ){

            //*cmd_set = 32;

            char* dev_uart = strstr(a_buf, c_dev_uart) ;
            if (dev_uart != NULL){

                //a_buf[dev_uart] = 32;

                char* par_baud = strstr(a_buf, c_par_baud);
                if (par_baud != NULL){

                    //a_buf[par_baud] = 32;

                    uint32_t baud = a_conf->cfg_uart.baud;
                    if (sscanf(&par_baud[5], c_val_dec, &baud) >= 0){
                        a_conf->cfg_uart.baud = baud;
                        UART2_init(a_conf->cfg_uart.baud = baud);
                        a_buf[0] = 0;
                        return true;
                    }
                }
                char* par = strstr(a_buf, c_par_en);
                if (par != NULL){
 
                        //a_buf[par] = 32;

                        UART2_enable();
                        a_buf[0] = 0;
                        return true;
                }
                par = strstr(a_buf, c_par_dis);
                if (par != NULL ){
 
                        //a_buf[par] = 32;

                        UART2_disable();
                        a_buf[0] = 0;
                        return true;
                }

                return true;

            }//if (dev_uart >= 0)

            return true;
        }//if ( cmd_set >= 0 )

        char* cmd_save = strstr(a_buf, c_cmd_save);
        if ( cmd_save != NULL ){

            //a_buf[cmd_save] = 32;

            a_conf->crc = crc8((uint8_t*)(a_conf+1), sizeof(configuration_t)-1);

            int8_t r = write_struct_to_flash((char*)a_conf, sizeof(configuration_t));
            if ( r < 0){
              //CDC_writeString("write operation:");
              //CDC_writeDec(r);
              //CDC_writeLine(c_rn);
            }

            return true;              

        }// if ( cmd_save >= 0 )

        char* cmd_load = strstr(a_buf, c_cmd_load);
        if ( cmd_load != NULL ){

            //a_buf[cmd_load] = 32;

            read_struct_from_flash((char*)a_conf, sizeof(configuration_t));

            CDC_writeString("Read flash\r\n");
            uint8_t i = 0;
            char* c_buf = (char*)a_conf; 
            for(i=0; i<sizeof(configuration_t); i++){
                //printf("adr-%08x v-%08x\r\n", Fadr +4*i, *(u32*)(Fadr +4*i));
                CDC_writeHex(c_buf[i], 2);
            }
            CDC_writeLine(c_rn);

            return true;

        }// if ( cmd_save >= 0 )


        char* cmd_print = strstr(a_buf, c_cmd_print);
        if ( cmd_print != NULL){

            //a_buf[cmd_print] = 32;

            CDC_writeString(c_dev_uart);
            CDC_writeString(c_rnt_active);
            CDC_writeString(a_conf->active_interfaces.uart ? c_par_en : c_par_dis);
            CDC_writeString(c_rnt);
            CDC_writeString(c_par_baud);
            CDC_writeString(":");
            CDC_writeDec(a_conf->cfg_uart.baud);
            CDC_writeString(c_rn);
            CDC_writeString(c_dev_spi);
            CDC_writeString(c_rnt_active);
            CDC_writeString(a_conf->active_interfaces.spi ? c_par_en : c_par_dis);
            CDC_writeString(c_rnt);

            CDC_writeString(c_rn);
            return true;
        }

        char* helpptr = strstr(a_buf, c_cmd_helpuart);
        if ( helpptr != NULL){

            CDC_writeLine(c_msg_helpuart);
            return true;
        }

        helpptr = strstr(a_buf, c_cmd_helpspi);
        if ( helpptr != NULL){

            CDC_writeLine(c_msg_helpspi);
            return true;
        }

        helpptr = strstr(a_buf, c_cmd_help);
        if ( helpptr != NULL){

            CDC_writeLine(c_msg_help1);
            return true;
        }

        return false;

    }//if ( eoc >= 0 )

    return false;
}