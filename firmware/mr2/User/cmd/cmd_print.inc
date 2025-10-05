
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
            CDC_writeString(c_rn);
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