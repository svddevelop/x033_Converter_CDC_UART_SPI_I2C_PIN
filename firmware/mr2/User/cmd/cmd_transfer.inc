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
