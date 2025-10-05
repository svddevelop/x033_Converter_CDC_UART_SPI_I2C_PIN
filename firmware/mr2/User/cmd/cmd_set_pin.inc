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
