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

  
//*************************************************************************
