#include "cdc_cmd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <strings.h>
#include "usb_cdc.h"
#include "uart/uart.h"
#include "i2c/i2c_soft.h"
#include "spi/spi.h"
#include "flash/flash_userdata.h"
#include "buildvers.h"

__code char c_cmd_save[] =              "SAVE";
__code char c_cmd_load[] =              "LOAD";
__code char c_cmd_trns[] =              "TRN";
__code char c_cmd_sh_r[] =              "\r";
__code char c_cmd_cfghex[] =            "CFGHEX";
__code char c_val_dec[] =               "=%d";
__code char c_cmd_print[] =             "[print]";
__code char c_cmd_help[] =              "[help]";
__code char c_cmd_helpuart[] =          "[helpuart]";
__code char c_cmd_helpspi[] =           "[helpspi]";
__code char c_cmd_helpi2c[] =           "[helpi2c]";
__code char c_cmd_helppin[] =           "[helppin]";
__code char c_cmd_set[] =               "[SET:";
__code char c_dev_uart[] =              "UART";
__code char c_dev_spi[] =               "SPI";
__code char c_dev_i2c[] =               "I2C";
__code char c_dev_pin[] =               "PIN";
__code char c_dev_cdc[] =               "CDC";
__code char c_par_baud[] =              ".BAUD";
__code char c_par_presc[] =             ".PRESC";
__code char c_par_cpol[] =              ".CPOL";
__code char c_par_cpha[] =              ".CPHA";
__code char c_par_en[] =                ".EN";
__code char c_par_dis[] =               ".DIS";
__code char c_par_master[] =            ".MASTER";
__code char c_rnt_active[] =            ":\r\n\tactive:";
__code char c_rnt[]    =                "\r\n\t";
__code char c_rn[]    =                 "\r\n";
__code char c_eq[]    =                 " = ";
__code char c_msg_readflash[] =         "Read flash\r\n";
__code char c_msg_ver[] =               "ver: ";
__code char c_msg_fromto[] =            " > ";


__code char c_msg_help1[] =             "help message;\r\nver 1.1\r\n"
                                        "\t-helpuart\t- shows information about setup of uart;\r\n"
                                        "\t-helpspi\t- shows information about spi;\r\n"
                                        "\t-helpi2c\t\t- how to setup i2c;\r\n"
                                        "\t-helppin\t- how to control pins;\r\n"
                                        "\t[TRN:<dev src>-<dev dst>.EN/DIS]\t- transwer between interfaces where <dev src> and <dev dst> is:\r\n"
                                        "\t\tCDC, UART, SPI or I2C;\r\n"
                                        "\t[SAVE]\t- save current confuguration to a flash memory;\r\n"
                                        "\t[LOAD]\t- load confuguration from a flash memory.\r\n"
                                        ;
__code char c_msg_helpuart[] =
                                        "\t[SET:UART.<param>=<value>]\r\n"
                                        "\t\t<dev> - device from these list: UART, SPI, I2C, CDC, PIN.\r\n"
                                        "\t\t\tparameter for device UART:\r\n"
                                        "\t\t\t\tBAUD with numerec value(default is 115200)\r\n"
                                        "\t\t[SET:UART.BAUD=9600]\t- set up baud 9600\r\n"
                                        "\t\t[SET:UART.EN]\t- enable UART, disable pins\r\n"
                                        "\t\t[SET:UART.DIS]\t- disable UART, enable pins\r\n"
                                        " -o-o-o-o---+-T-R--- \r\n"
                                        "|\t\t    |\r\n"
                                        "]\t#\t    |\r\n"
                                        "|\t\t    |\r\n"
                                        " -o-o-o-o---o-o-o-o- \r\n"
                                        ;
__code char c_msg_helpspi[] =
                                        "\t[SET:<dev>.<param>=<value>]\r\n"
                                        "\t\t<dev> - device from these list: UART, SPI, I2C, CDC, PIN.\r\n"
                                        //"\t\t\tparameter for device UART:\r\n"
                                        //"\t\t\t\tBAUD with numerec value(default is 115200)\r\n"
                                        "\r\n[SET:SPI.MASTER=<char val>]\t- set up the mode of SPI (0 or 1);"
                                        "\r\n[SET:SPI.PRESC=<char val>]\t- prescaller for CLOCK_RATE = 48000000 / (2 << PRESC);"
                                        "\r\n[SET:SPI.BAUD=<char val>]\t- set up speed with value:"
                                        "\r\n\t\t\t- 0 - CLOCK_RATE /2 ;"
                                        "\r\n\t\t\t- 1 - CLOCK_RATE /4 ;"
                                        "\r\n\t\t\t- 2 - CLOCK_RATE /8 ;"
                                        "\r\n\t\t\t- 3 - CLOCK_RATE /16 ;"
                                        "\r\n\t\t\t- 4 - CLOCK_RATE /32 ;"
                                        "\r\n\t\t\t- 5 - CLOCK_RATE /64 ;"
                                        "\r\n\t\t\t- 6 - CLOCK_RATE /128 ;"
                                        "\r\n\t\t\t- 7 - CLOCK_RATE /256 ;"
<<<<<<< HEAD
                                        "\r\n[SET:SPI.CPOL=<char val>]\t- set up the clock polarity (0 or 1);"
                                        "\r\n[SET:SPI.CPHA=<char val>]\t- set up the clock phase (0 or 1);"
=======
                                        "\r\n[SET:SPI.CPOL=<val>]\t- set up the clock polarity (0 or 1);"
                                        "\r\n[SET:SPI.CPHA=<val>]\t- set up the clock phase (0 or 1);"
>>>>>>> develop
                                        "\r\n[SET:SPI.EN]\t- enable SPI, disable pins;"
                                        "\r\n[SET:SPI.DIS]\t- disable SPI, enable pins;\r\n"
                                        " -o-o-o-o---o-o-o-o- \r\n"
                                        "|\t\t    |\r\n"
                                        "]\t\t#  |\r\n"
                                        "|\t\t    |\r\n"
                                        " -+-D-C-----o-o-o-o- \r\n"
                                        ;
__code char c_msg_helpi2c[] =
                                        "\t[SET:<dev>.<param>=<value>]\r\n"
                                        "\t\t<dev> - device from these list: UART, SPI, I2C, CDC, PIN.\r\n"
                                        //"\t\t\tparameter for device UART:\r\n"
                                        //"\t\t\t\tBAUD with numerec value(default is 115200)\r\n"
                                        //"\r\n[SET:SPI.SPEED=2000000]\t- set up baud 9600\r\n"
                                        "\r\n[SET:I2C.EN]\t- enable I2C, disable pins"
                                        "\r\n[SET:I2C.DIS]\t- disable I2C, enable pins\r\n"
                                        " -o-o-o-o---o-o-o-o- \r\n"
                                        "|\t\t    |\r\n"
                                        "]\t\t#  |\r\n"
                                        "|\t\t    |\r\n"
                                         " -o-o-o-o---o-o-o-o- \r\n"
                                        ;
__code char c_msg_helppin[] =
                                        "\t[SET:PIN.<pin>=<mode>]\r\n"
                                        "\t\twhere <pin> is apossible pin from the list:\r\n"
                                        "\t\t\tPA2, PA3, PA4, PA5, PA6, PA7, PA10, PA11, PC18 PC19;\r\n\n"
                                        "\t\tmode:\r\n"
                                        "\t\t\t0 - input,\r\n"
                                        "\t\t\t1 - input pull-down,\r\n"
                                        "\t\t\t2 - input pull-up,\r\n"
                                        "\t\t\t3 - input analog,\r\n"
                                        "\t\t\t4 - output.\r\n\n"
                                        "\t[<pin>=0/1] - setup 0 or 1 to the pin;"
                                        "\t\tExample:\r\n\t\t\t[PA3=1]\r\n\t\t\t[PA3=0]\r\n"
                                        "\t[<pin>?] - print the value from pin;\r\n"
                                        ;

__code char c_msg_spibaseclock[]        = "Base SPI clock: ";                                        
__code char c_msg_spi_hz[]              = " Hz\n";                                        
__code char c_msg_spispeed[]            = "SPI speed: ";
__code char* const c_pins_list[]        = {"PA2","PA3","PA4","PA5","PA6","PA7","PA10","PA11","PC18","PC19"}  ;     
__code int c_pins_count                 = sizeof(c_pins_list) / sizeof(c_pins_list[0]);                  


inline __attribute__((always_inline)) void calculate_spi_speeds(configuration_t* a_conf) {

    uint32_t f_cpu = F_CPU; // 48 MHz
    uint8_t spi_presc = a_conf->cfg_spi.prescaller;
    
    uint32_t base_clock = f_cpu / (2 << spi_presc); //§¢§Ñ§Ù§à§Ó§Ñ§ñ §é§Ñ§ã§ä§à§ä§Ñ
    CDC_writeString(c_msg_spibaseclock);
    CDC_writeDec(base_clock);
    CDC_writeLine(c_msg_spi_hz);
    CDC_writeString(c_msg_spispeed);
    CDC_writeDec(base_clock / a_conf->cfg_spi.baud);
    CDC_writeLine(c_msg_spi_hz);

}                                        


void print_conf_hex(configuration_t * a_conf){

    char* c_buf = (char*)a_conf; 
    for(int i=0; i<sizeof(configuration_t); i++){
                //printf("adr-%08x v-%08x\r\n", Fadr +4*i, *(u32*)(Fadr +4*i));
        CDC_writeHex(c_buf[i], 2);
    }
    CDC_writeLine(c_rn);
}

#define _SIOZEOFMSG(x)      (sizeof(x)-1)
#define _MEMCMP(x)          memcmp(a_buf,x,_SIOZEOFMSG(x))

inline __attribute__((always_inline)) bool ifcmdexec(char* a_buf, configuration_t* a_conf){


    char *dev, *par;

    char *bk = strstr(a_buf, "[")
        , *ek = strstr(a_buf, "]");
    
    char* eoc = NULL;
    if (( bk != NULL) && ( ek != NULL ))
        if ( bk < ek)
            eoc = strstr(a_buf, c_cmd_sh_r); //end of command
<<<<<<< HEAD

    if ((eoc != NULL ) && ( ek < eoc )){

        char* cmd = strstr(a_buf, c_cmd_set);
        if ( cmd != NULL ){
=======

    if ((eoc != NULL ) && ( ek < eoc )){

        char* cmd = strstr(a_buf, c_cmd_set); ///   CMD 'SET'
        if ( cmd != NULL ){

            ////////////////////////////// PIN //////////////////////////////////
            uint8_t pin_idx = 0;
            char* pin = NULL;
            for(pin_idx = 0; pin_idx < c_pins_count; pin_idx++){

                pin = strstr(a_buf, c_pins_list[pin_idx]);
                if ( pin != NULL)
                    break;
            }
            if (( pin != NULL) && ( ! IS_PIN_PC19( pin_idx ) )){ // exept PC19

                uint32_t val = 0;
                pin = strstr(pin, "=");
                if ( pin != NULL){
                    if (sscanf(pin, c_val_dec, &val) >= 0){

                    }
                }
                
                bool is_type_device = IS_PIN_UART(pin_idx);
                if ( is_type_device ) {
                    switch (pin_idx){
                        case PIN_UART_RX:
                            //SET_PIN_MODE()
                            a_conf->cfg_pins.pa3.mode = val;
                            break;
                        case PIN_UART_TX:
                            a_conf->cfg_pins.pa2.mode = val;
                            break;
                    }
                };

                is_type_device = IS_PIN_I2C(pin_idx);
                if ( is_type_device ) {
                    switch (pin_idx) {
                        case PIN_I2C_SCL:
                            //SET_PIN_MODE()
                            a_conf->cfg_pins.pa10.mode = val;
                            break;
                        case PIN_I2C_SDA:
                            a_conf->cfg_pins.pa11.mode = val;
                            break;
                    }
                };

                is_type_device = IS_PIN_SPI(pin_idx);
                if ( is_type_device ) {
                    switch (pin_idx){
                        case PIN_SPI_CS:
                            //SET_PIN_MODE()
                            a_conf->cfg_pins.pa4.mode = val;
                            break;
                        case PIN_SPI_SCK:
                            a_conf->cfg_pins.pa5.mode = val;
                            break;
                        case PIN_SPI_MISO:
                            //SET_PIN_MODE()
                            a_conf->cfg_pins.pa6.mode = val;
                            break;
                        case PIN_SPI_MOSI:
                            a_conf->cfg_pins.pa7.mode = val;
                            break;
                    }
                };

           
                if ( (pin_idx == PIN_PIN_1) ) {
                   a_conf->cfg_pins.pc18.mode = val; 
                }

                return true;

            }// if ( pin != NULL)
            //*******************************************************************


>>>>>>> develop


            //////////////////////////////   UART    ///////////////////////////

            dev = strstr(a_buf, c_dev_uart) ;
            if (dev != NULL){

                //a_buf[dev_uart] = 32;

                par = strstr(a_buf, c_par_baud);
                if (par != NULL){

                    //a_buf[par_baud] = 32;

                    uint32_t baud = a_conf->cfg_uart.baud;
                    if (sscanf(&par[5], c_val_dec, &baud) >= 0){
                        a_conf->cfg_uart.baud = baud;
                        #ifdef UART_WITH_IRQ
                        UART2_Init2( baud );
                        //UART2_setBAUD( baud );
                        #endif
                        #ifndef UART_WITH_IRQ
                        UART2_init(  baud );
                        #endif
                        a_buf[0] = 0;
                        return true;
                    }
                    return true;
                }
                par = strstr(a_buf, c_par_en);
                if (par != NULL){
 
                        //a_buf[par] = 32;
                        a_conf->active_interfaces.uart = 1;

                        UART2_enable();
                        a_buf[0] = 0;
                        return true;
                }
                par = strstr(a_buf, c_par_dis);
                if (par != NULL ){
 
                        //a_buf[par] = 32;
                        a_conf->active_interfaces.uart = 0;

                        UART2_disable();
                        a_buf[0] = 0;
                        return true;
                }

                return true;

            }//if (dev != NULL)  c_dev_uart

            dev = strstr(a_buf, c_dev_i2c) ;
            if (dev != NULL){

                par = strstr(a_buf, c_par_baud);
                if (par != NULL){

                    //a_buf[par_baud] = 32;

                    uint32_t baud = a_conf->cfg_uart.baud;
                    if (sscanf(&par[5], c_val_dec, &baud) >= 0){

                        a_conf->cfg_uart.baud = baud;
                        
                        UART2_init( baud);
                        a_buf[0] = 0;
                        return true;
                    }
                    return true;
                }

                //*************************************************************************

                //////////////////////////  I2C  ////////////////////////////////////

                par = strstr(a_buf, c_par_en);
                if (par != NULL){
 
                        //a_buf[par] = 32;
                        a_conf->active_interfaces.i2c = 1;

                        //UART2_enable();
                        //it must be  I2C
                        a_buf[0]    = 0;
                        par[0]      = 0;
                        return true;
                }
                par = strstr(a_buf, c_par_dis);
                if (par != NULL ){
 
                        //a_buf[par] = 32;
                        a_conf->active_interfaces.i2c = 0;

                        //UART2_disable();
                        //it must be  I2C
                        a_buf[0]    = 0;
                        par[0]      = 0;
                        return true;
                }

                return true;
            }//if (dev != NULL)  c_dev_i2c

            //********************************************************************

            ///////////////////////   SPI ////////////////////////////////////////

            dev = strstr(a_buf, c_dev_spi) ;
            if (dev != NULL){

                int val = 0;

                par = strstr(a_buf, c_par_baud);
                if (par != NULL){

                    val = a_conf->cfg_spi.baud;
                    if (sscanf(&par[5], c_val_dec, &val) >= 0){
                        if ((val >= 0) & (val <= 7)){

                            a_conf->cfg_spi.baud = val;
                            SPI_setBAUD(a_conf->cfg_spi.baud = val);

                        }
                        a_buf[0] = 0;
                        return true;
                    }
                    return true;
                }
               par = strstr(a_buf, c_par_presc);
                if (par != NULL){

                    val = a_conf->cfg_spi.prescaller;
                    if (sscanf(&par[6], c_val_dec, &val) >= 0){
                        if ((val >= 0) & (val <= 7)){

                            a_conf->cfg_spi.prescaller = val;
                            activate_cfg(a_conf); 

                        }
                        a_buf[0] = 0;
                        return true;
                    }
                    return true;
                }
                par = strstr(a_buf, c_par_master);
                if (par != NULL){

                    val = a_conf->cfg_spi.master;
                    if (sscanf(&par[7], c_val_dec, &val) >= 0){

                        if ((val == 0) )
                            a_conf->cfg_spi.master = 0;
                        else 
                          a_conf->cfg_spi.master = 1;

                        activate_cfg(a_conf);                            
                        
                        a_buf[0] = 0;
                        return true;
                    }
                    return true;
                }
                par = strstr(a_buf, c_par_cpol);
                if (par != NULL){

                    val = a_conf->cfg_spi.pol;
                    if (sscanf(&par[5], c_val_dec, &val) >= 0){

                        if ((val == 0) )
                            a_conf->cfg_spi.pol = 0;
                        else 
                          a_conf->cfg_spi.pol = 1;

                        activate_cfg(a_conf);                            
                        
                        a_buf[0] = 0;
                        return true;
                    }
                    return true;
                }
                par = strstr(a_buf, c_par_cpha);
                if (par != NULL){

                    val = a_conf->cfg_spi.pha;
                    if (sscanf(&par[5], c_val_dec, &val) >= 0){

                        if ((val == 0) )
                            a_conf->cfg_spi.pha = 0;
                        else 
                          a_conf->cfg_spi.pha = 1;

                        activate_cfg(a_conf);                            
                        
                        a_buf[0] = 0;
                        return true;
                    }
                    return true;
                }
               


                par = strstr(a_buf, c_par_en);
                if (par != NULL){
 
                        //a_buf[par] = 32;
                        a_conf->active_interfaces.spi = 1;

                        SPI_enable();

                        a_buf[0]    = 0;
                        par[0]      = 0;
                        return true;
                }
                par = strstr(a_buf, c_par_dis);
                if (par != NULL ){
 
                        //a_buf[par] = 32;
                        a_conf->active_interfaces.spi = 0;

                        SPI_disable();

                        a_buf[0]    = 0;
                        par[0]      = 0;
                        return true;
                }

                return true;
            }//if (dev != NULL)  c_dev_spi


            //*****************************************************************

            return true;
        }//if ( cmd_set >= 0 )  


        cmd = strstr(a_buf, c_cmd_trns);
        if ( cmd != NULL ){

            char * devCDC  = strstr(a_buf, c_dev_cdc)
               , * devUART = strstr(a_buf, c_dev_uart)
               , * devSPI  = strstr(a_buf, c_dev_spi)
               , * devI2C  = strstr(a_buf, c_dev_i2c)
               , * tEn     = strstr(a_buf, c_par_en) 
               , * tDis    = strstr(a_buf, c_par_dis) 
               ; 

            // CDC ->>
            if (( devCDC != NULL ) && ( devUART != NULL )){

                if(devCDC < devUART ){
                  if (tEn  != NULL) a_conf->trans.cdc_uart = 1;
                  if (tDis != NULL) a_conf->trans.cdc_uart = 0;
                }
                if(devUART < devCDC ){
                  if (tEn  != NULL) a_conf->trans.uart_cdc = 1;
                  if (tDis != NULL) a_conf->trans.uart_cdc = 0;
                }
            }
            if (( devCDC != NULL ) && ( devSPI != NULL )){

                if(devCDC < devSPI ){
                  if (tEn  != NULL) a_conf->trans.cdc_spi = 1;
                  if (tDis != NULL) a_conf->trans.cdc_spi = 0;
                }
                if(devSPI < devCDC ){
                  if (tEn  != NULL) a_conf->trans.spi_cdc = 1;
                  if (tDis != NULL) a_conf->trans.spi_cdc = 0;
                }
            }
            if (( devCDC != NULL ) && ( devI2C != NULL )){

                if(devCDC < devI2C ){
                  if (tEn  != NULL) a_conf->trans.cdc_i2c = 1;
                  if (tDis != NULL) a_conf->trans.cdc_i2c = 0;
                }
                if(devI2C < devCDC ){
                  if (tEn  != NULL) a_conf->trans.i2c_cdc = 1;
                  if (tDis != NULL) a_conf->trans.i2c_cdc = 0;
                }
            }

            //UART ->>
            if (( devUART != NULL ) && ( devSPI != NULL )){

                if(devUART < devSPI ){
                  if (tEn  != NULL) a_conf->trans.uart_spi = 1;
                  if (tDis != NULL) a_conf->trans.uart_spi = 0;
                }
                if(devSPI < devUART ){
                  if (tEn  != NULL) a_conf->trans.spi_uart = 1;
                  if (tDis != NULL) a_conf->trans.spi_uart = 0;
                }
            }

            if (( devUART != NULL ) && ( devI2C != NULL )){

                if(devUART < devI2C ){
                  if (tEn  != NULL) a_conf->trans.uart_i2c = 1;
                  if (tDis != NULL) a_conf->trans.uart_i2c = 0;
                }
                if(devI2C < devUART ){
                  if (tEn  != NULL) a_conf->trans.i2c_uart = 1;
                  if (tDis != NULL) a_conf->trans.i2c_uart = 0;
                }
            }
            // SPI ->>
            if (( devSPI != NULL ) && ( devI2C != NULL )){

                if(devSPI < devI2C ){
                  if (tEn  != NULL) a_conf->trans.spi_i2c = 1;
                  if (tDis != NULL) a_conf->trans.spi_i2c = 0;
                }
                if(devI2C < devSPI ){
                  if (tEn  != NULL) a_conf->trans.i2c_spi = 1;
                  if (tDis != NULL) a_conf->trans.i2c_spi = 0;
                }
            }




        } // if c_cmd_trns

        cmd = strstr(a_buf, c_cmd_save);
        if ( cmd != NULL ){

            //a_buf[cmd_save] = 32;

            a_conf->crc = calc_cfg_crc(a_conf);

            int8_t r = write_struct_to_flash((char*)a_conf, sizeof(configuration_t));
            if ( r < 0){
              //CDC_writeString("write operation:");
              //CDC_writeDec(r);
              //CDC_writeLine(c_rn);
            }

            print_conf_hex(a_conf);

            return true;              

        }// if ( cmd_save >= 0 )

        cmd = strstr(a_buf, c_cmd_load);
        if ( cmd != NULL ){

            read_struct_from_flash((char*)a_conf, sizeof(configuration_t));

            CDC_writeString(c_msg_readflash);

            a_conf->crc = calc_cfg_crc(a_conf);

            print_conf_hex(a_conf);

            activate_cfg(a_conf);

            return true;

        }// if ( cmd_save >= 0 )

<<<<<<< HEAD
=======
        cmd = strstr(a_buf, c_dev_pin); // ACHTUNG !!! hier cmd == dev !!!
        if ( cmd != NULL ){

            //pin 

            activate_cfg(a_conf);

            return true;

        }// if ( c_cmd_pin >= 0 )

>>>>>>> develop
        cmd = strstr(a_buf, c_cmd_cfghex);
        if ( cmd != NULL ){
            
            a_conf->crc = calc_cfg_crc(a_conf);

            print_conf_hex(a_conf);

            return true;

        }// if ( cmd_cfghex >= 0 )

        cmd = strstr(a_buf, c_cmd_print);
        if ( cmd != NULL){

            //a_buf[cmd_print] = 32;

            uint32_t rcc_cr   = RCC->CTLR;   // §Ú§Ý§Ú RCC->CR, §Ó §Ù§Ñ§Ó§Ú§ã§Ú§Þ§à§ã§ä§Ú §à§ä §Ù§Ñ§Ô§à§Ý§à§Ó§Ü§à§Ó CH32
            uint32_t rcc_cfgr = RCC->CFGR0;
            CDC_writeString("RCC CTLR = 0x");CDC_writeHex(rcc_cr,8);CDC_writeString(" CFGR = 0x");CDC_writeHex(rcc_cfgr,8);CDC_writeString(c_rn);

            CDC_writeString(c_dev_uart);
            CDC_writeString(c_rnt_active);
            CDC_writeString(a_conf->active_interfaces.uart ? c_par_en : c_par_dis);
            CDC_writeString(c_rnt);
            CDC_writeString(c_par_baud);
            CDC_writeString(c_eq);
            CDC_writeDec(a_conf->cfg_uart.baud);
            CDC_writeString(c_rn);
            CDC_writeString(c_dev_spi);
            CDC_writeString(c_rnt_active);
            CDC_writeString(a_conf->active_interfaces.spi ? c_par_en : c_par_dis);

            CDC_writeString(c_rnt);
            CDC_writeString(c_par_master);
            CDC_writeString(c_eq);
            CDC_writeDec(a_conf->cfg_spi.master);

            CDC_writeString(c_rnt);
            CDC_writeString(c_par_cpha);
            CDC_writeString(c_eq);
            CDC_writeDec(a_conf->cfg_spi.pha);

            CDC_writeString(c_rnt);
            CDC_writeString(c_par_cpol);
            CDC_writeString(c_eq);
            CDC_writeDec(a_conf->cfg_spi.pol);

            CDC_writeString(c_rnt);
            CDC_writeString(c_par_baud);
            CDC_writeString(c_eq);
            CDC_writeDec(a_conf->cfg_spi.baud);
 
            CDC_writeString(c_rnt);
            CDC_writeString(c_par_presc);
            CDC_writeString(c_eq);
            CDC_writeDec(a_conf->cfg_spi.prescaller);
            //CDC_writeString(c_rn);
            calculate_spi_speeds(a_conf);

            CDC_writeString(c_rnt);CDC_writeString(c_cmd_trns);CDC_writeString(c_rnt);

            CDC_writeString(c_dev_cdc);CDC_writeString(c_msg_fromto);CDC_writeString(c_dev_uart); 
            CDC_writeString(c_eq); CDC_writeDec(a_conf->trans.cdc_uart);CDC_writeString(c_rn);

            CDC_writeString(c_dev_cdc);CDC_writeString(c_msg_fromto);CDC_writeString(c_dev_spi); 
            CDC_writeString(c_eq); CDC_writeDec(a_conf->trans.cdc_spi);CDC_writeString(c_rn);

            CDC_writeString(c_dev_cdc);CDC_writeString(c_msg_fromto);CDC_writeString(c_dev_i2c); 
            CDC_writeString(c_eq); CDC_writeDec(a_conf->trans.cdc_i2c);CDC_writeString(c_rn);

            CDC_writeString(c_dev_uart);CDC_writeString(c_msg_fromto);CDC_writeString(c_dev_cdc); 
            CDC_writeString(c_eq); CDC_writeDec(a_conf->trans.uart_cdc);CDC_writeString(c_rn);

            CDC_writeString(c_dev_uart);CDC_writeString(c_msg_fromto);CDC_writeString(c_dev_spi); 
            CDC_writeString(c_eq); CDC_writeDec(a_conf->trans.uart_spi);CDC_writeString(c_rn);

            CDC_writeString(c_dev_uart);CDC_writeString(c_msg_fromto);CDC_writeString(c_dev_i2c); 
            CDC_writeString(c_eq); CDC_writeDec(a_conf->trans.uart_i2c);CDC_writeString(c_rn);

            CDC_writeString(c_dev_spi);CDC_writeString(c_msg_fromto);CDC_writeString(c_dev_cdc); 
            CDC_writeString(c_eq); CDC_writeDec(a_conf->trans.spi_cdc);CDC_writeString(c_rn);

            CDC_writeString(c_dev_spi);CDC_writeString(c_msg_fromto);CDC_writeString(c_dev_uart); 
            CDC_writeString(c_eq); CDC_writeDec(a_conf->trans.spi_uart);CDC_writeString(c_rn);

            CDC_writeString(c_dev_spi);CDC_writeString(c_msg_fromto);CDC_writeString(c_dev_i2c); 
            CDC_writeString(c_eq); CDC_writeDec(a_conf->trans.spi_i2c);CDC_writeString(c_rn);

            CDC_writeString(c_dev_i2c);CDC_writeString(c_msg_fromto);CDC_writeString(c_dev_cdc); 
            CDC_writeString(c_eq); CDC_writeDec(a_conf->trans.i2c_cdc);CDC_writeString(c_rn);

            CDC_writeString(c_dev_i2c);CDC_writeString(c_msg_fromto);CDC_writeString(c_dev_uart); 
            CDC_writeString(c_eq); CDC_writeDec(a_conf->trans.i2c_uart);CDC_writeString(c_rn);

            CDC_writeString(c_dev_i2c);CDC_writeString(c_msg_fromto);CDC_writeString(c_dev_spi); 
            CDC_writeString(c_eq); CDC_writeDec(a_conf->trans.i2c_spi);CDC_writeString(c_rn);

           a_conf->crc = calc_cfg_crc(a_conf);
            CDC_writeString(c_rn);
            print_conf_hex(a_conf);
            CDC_writeString(c_rn);
           return true;
        }

<<<<<<< HEAD
=======
        cmd = strstr(a_buf, c_cmd_helpi2c);
        if ( cmd != NULL){

            CDC_writeLine(c_msg_helpi2c);
            return true;
        }

        cmd = strstr(a_buf, c_cmd_helppin);
        if ( cmd != NULL){

            CDC_writeLine(c_msg_helppin);
            return true;
        }

>>>>>>> develop
        cmd = strstr(a_buf, c_cmd_helpuart);
        if ( cmd != NULL){

            CDC_writeLine(c_msg_helpuart);
            return true;
        }

        cmd = strstr(a_buf, c_cmd_helpspi);
        if ( cmd != NULL){

            CDC_writeLine(c_msg_helpspi);
            return true;
        }

        cmd = strstr(a_buf, c_cmd_help);
        if ( cmd != NULL){

                uint32_t ver = 
                (TOBYTE(BUILD_YEAR_CH2,BUILD_YEAR_CH3)<< 24) |
                (TOBYTE(BUILD_MONTH_CH0,BUILD_MONTH_CH1) << 16) |
                (TOBYTE(BUILD_DAY_CH0,BUILD_DAY_CH1) << 8) |
                (TOBYTE(BUILD_HOUR_CH0,BUILD_HOUR_CH1));
<<<<<<< HEAD
=======
                
>>>>>>> develop
            CDC_writeString(c_msg_ver);
            CDC_writeHex(ver, 8);
            CDC_writeString(c_rn);
            CDC_writeLine(c_msg_help1);
            return true;
        }

        return false;

    }//if ( eoc >= 0 )

    return false;
}

void process_cdc(configuration_t * a_conf, char * a_cdc_buf, uint16_t * a_len){

    if ( * a_len > 0 ){

        if (( a_conf->trans.cdc_uart ) && ( a_conf->active_interfaces.uart)){

            #ifdef UART_WITH_IRQ

            uart_start_tx( &uart2_handler, a_cdc_buf, *a_len );

            #endif

            #ifndef UART_WITH_IRQ

            uart_start_tx( &uart2_handler, a_cdc_buf, *a_len );

            #endif
        }

        *a_len = 0;
    }

}

void process_uart(configuration_t * a_conf){

    if (a_conf->active_interfaces.uart)
    if ( ! uart2_handler.rx_transaction ){

        if ( uart2_handler.rx_len > 0) {

            if ( a_conf->trans.uart_cdc ){

                for(uint8_t i = 0; i < uart2_handler.rx_len; i++)
                    CDC_write( uart2_handler.rx_buf[i] );

                CDC_flush();

            }
            if ( a_conf->trans.uart_spi ){

                for(uint8_t i = 0; i < uart2_handler.rx_len; i++)
                    //SPI_write(uart2_handler.rx_buf[i])
                    ;
            }

            uart2_handler.rx_len = 0;
        }


        
    }

}