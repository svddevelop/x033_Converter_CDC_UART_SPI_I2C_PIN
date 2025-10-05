            ///////////////////////   SPI ////////////////////////////////////////

            dev = strstr(a_buf, c_dev_spi) ;
            if (dev != NULL){

                int val = 0;

                par = strstr(a_buf, c_par_baud);
                if (par != NULL){

                    val = a_conf->cfg_spi.baud;
                    if (sscanf(&par[5], c_val_dec, &val) >= 0){
                        if ((val >= 0) & (val <= 7)){

//§­§µ§¹§º§ª§« §£§¡§²§ª§¡§¯§´: §ã§Õ§Ö§Ý§Ñ§ä§î §Ó§ã§Ö §Ó §ã§à§ç§â§Ñ§ß§Ö§ß§Ú§Ú §Ü§à§ß§æ§Ú§Ô§Ñ §Ú §Ù§Ñ§ä§Ö§Þ §Ó§í§Ù§Ó§Ñ§ä§î activate_cfg()
                            


                            //CS must be as comfigured for master and slave separate



                            a_conf->cfg_spi.baud = val;

                            activate_cfg(a_conf);

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
