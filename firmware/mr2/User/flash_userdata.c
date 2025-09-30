#include "flash_userdata.h"

/* Flash Access Control Register bits */
#define ACR_LATENCY_Mask           ((uint32_t)0xFFFFFFFC)

/* Flash Control Register bits */
#define CR_PER_Set                 ((uint32_t)0x00000002)
#define CR_PER_Reset               ((uint32_t)0xFFFFFFFD)
#define CR_MER_Set                 ((uint32_t)0x00000004)
#define CR_MER_Reset               ((uint32_t)0xFFFFFFFB)
#define CR_OPTER_Set               ((uint32_t)0x00000020)
#define CR_OPTER_Reset             ((uint32_t)0xFFFFFFDF)
#define CR_STRT_Set                ((uint32_t)0x00000040)
#define CR_LOCK_Set                ((uint32_t)0x00000080)
#define CR_FLOCK_Set               ((uint32_t)0x00008000)
#define CR_PAGE_PG                 ((uint32_t)0x00010000)
#define CR_PAGE_ER                 ((uint32_t)0x00020000)
#define CR_PAGE_ER_Reset           ((uint32_t)0xFFFDFFFF)
#define CR_BUF_LOAD                ((uint32_t)0x00040000)
#define CR_BUF_RST                 ((uint32_t)0x00080000)
#define CR_BER32                   ((uint32_t)0x00800000)

#define CR_OPTPG_Set               ((uint32_t)0x00000010)
#define CR_OPTPG_Reset             ((uint32_t)0xFFFFFFEF)


/* FLASH Status Register bits */
#define SR_BSY                     ((uint32_t)0x00000001)
#define SR_WRPRTERR                ((uint32_t)0x00000010)
#define SR_EOP                     ((uint32_t)0x00000020)

/* FLASH Mask */
#define RDPRT_Mask                 ((uint32_t)0x00000002)
#define WRP0_Mask                  ((uint32_t)0x000000FF)
#define WRP1_Mask                  ((uint32_t)0x0000FF00)
#define WRP2_Mask                  ((uint32_t)0x00FF0000)
#define WRP3_Mask                  ((uint32_t)0xFF000000)

/* FLASH Keys */
#define RDP_Key                    ((uint16_t)0x00A5)
#define FLASH_KEY1                 ((uint32_t)0x45670123)
#define FLASH_KEY2                 ((uint32_t)0xCDEF89AB)

/* FLASH BANK address */
#define FLASH_BANK1_END_ADDRESS    ((uint32_t)0x807FFFF)

/* Delay definition */
#define EraseTimeout               ((uint32_t)0x000B0000)
#define ProgramTimeout             ((uint32_t)0x00005000)

/* Flash Program Valid Address */
#define ValidAddrStart             (FLASH_BASE)
#define ValidAddrEnd               (FLASH_BASE + 0xF800)

/* FLASH Size */
#define Size_256B                  0x100
#define Size_1KB                   0x400
#define Size_32KB                  0x8000

/* Global define */
#define u32     uint32_t
#define u8      uint8_t
#define Fadr    0x08003000
#define Fsize   (256>>2)

/*********************************************************************
 * @fn      FLASH_GetBank1Status
 *
 * @brief   Returns the FLASH Bank1 Status.
 *
 * @return  FLASH Status - The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 *        FLASH_ERROR_WRP or FLASH_COMPLETE.
 */
 
FLASH_Status FLASH_GetBank1Status(void)
{
    FLASH_Status flashstatus = FLASH_COMPLETE;

    if((FLASH->STATR & FLASH_FLAG_BANK1_BSY) == FLASH_FLAG_BSY)
    {
        flashstatus = FLASH_BUSY;
    }
    else
    {
        if((FLASH->STATR & FLASH_FLAG_BANK1_WRPRTERR) != 0)
        {
            flashstatus = FLASH_ERROR_WRP;
        }
        else
        {
            flashstatus = FLASH_COMPLETE;
        }
    }
    return flashstatus;
}


/*********************************************************************
 * @fn      FLASH_WaitForLastOperation
 *
 * @brief   Waits for a Flash operation to complete or a TIMEOUT to occur.
 *
 * @param   Timeout - FLASH programming Timeout
 *
 * @return  FLASH Status - The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 *        FLASH_ERROR_WRP or FLASH_COMPLETE.
 */
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout)
{
    FLASH_Status status = FLASH_COMPLETE;

    status = FLASH_GetBank1Status();
    while((status == FLASH_BUSY) && (Timeout != 0x00))
    {
        status = FLASH_GetBank1Status();
        Timeout--;
    }
    if(Timeout == 0x00)
    {
        status = FLASH_TIMEOUT;
    }
    return status;
}


/*********************************************************************
 * @fn      ROM_ERASE
 *
 * @brief   Select erases a specified FLASH .
 *
 * @param   StartAddr - Erases Flash start address(StartAddr%256 == 0).
 *          Cnt - Erases count.
 *          Erase_Size - Erases size select.The returned value can be:
 *          Size_32KB, Size_1KB, Size_256B.
 *
 * @return  none.
 */
static void ROM_ERASE(uint32_t StartAddr, uint32_t Cnt, uint32_t Erase_Size)
{
	FLASH->CTLR &= (CR_OPTER_Reset & CR_PAGE_ER_Reset);

    do{
        if(Erase_Size == Size_32KB)
        {
            FLASH->CTLR |= CR_BER32;
        }
        else if(Erase_Size == Size_1KB)
        {
            FLASH->CTLR |= CR_PER_Set;
        }
        else if(Erase_Size == Size_256B)
        {
            FLASH->CTLR |= CR_PAGE_ER;
        }

        FLASH->ADDR = StartAddr;
        FLASH->CTLR |= CR_STRT_Set;
        while(FLASH->STATR & SR_BSY)
            ;

        if(Erase_Size == Size_32KB)
        {
            FLASH->CTLR &= ~CR_BER32;
            StartAddr += Size_32KB;
        }
        else if(Erase_Size == Size_1KB)
        {
            FLASH->CTLR &= ~CR_PER_Set;
            StartAddr += Size_1KB;
        }
        else if(Erase_Size == Size_256B)
        {
            FLASH->CTLR &= ~CR_PAGE_ER;
            StartAddr += Size_256B;
        }
    }while(--Cnt);
}

/*********************************************************************
 * @fn      FLASH_ROM_ERASE
 *
 * @brief   Erases a specified FLASH .
 *
 * @param   StartAddr - Erases Flash start address(StartAddr%256 == 0).
 *          Length - Erases Flash start Length(Length%256 == 0).
 *
 * @return  FLASH Status - The returned value can be: FLASH_ADR_RANGE_ERROR,
 *        FLASH_ALIGN_ERROR, FLASH_OP_RANGE_ERROR or FLASH_COMPLETE.
 */
 
FLASH_Status FLASH_ROM_ERASE(uint32_t StartAddr, uint32_t Length)
{
    uint32_t Addr0 = 0, Addr1 = 0, Length0 = 0, Length1 = 0;

    FLASH_Status status = FLASH_COMPLETE;

    if((StartAddr < ValidAddrStart) || (StartAddr >= ValidAddrEnd))
    {
        return FLASH_ADR_RANGE_ERROR;
    }

    if((StartAddr + Length) > ValidAddrEnd)
    {
        return FLASH_OP_RANGE_ERROR;
    }

    if((StartAddr & (Size_256B-1)) || (Length & (Size_256B-1)) || (Length == 0))
    {
        return FLASH_ALIGN_ERROR;
    }

    /* Authorize the FPEC of Bank1 Access */
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;

    /* Fast mode unlock */
    FLASH->MODEKEYR = FLASH_KEY1;
    FLASH->MODEKEYR = FLASH_KEY2;

    Addr0 = StartAddr;

    if(Length >= Size_32KB)
    {
        Length0 = Size_32KB - (Addr0 & (Size_32KB - 1));
        Addr1 = StartAddr + Length0;
        Length1 = Length - Length0;
    }
    else if(Length >= Size_1KB)
    {
        Length0 = Size_1KB - (Addr0 & (Size_1KB - 1));
        Addr1 = StartAddr + Length0;
        Length1 = Length - Length0;
    }
    else if(Length >= Size_256B)
    {
        Length0 = Length;
    }

    /* Erase 32KB */
    if(Length0 >= Size_32KB)//front
    {
        Length = Length0;
        if(Addr0 & (Size_32KB - 1))
        {
            Length0 = Size_32KB - (Addr0 & (Size_32KB - 1));
        }
        else
        {
            Length0 = 0;
        }

        ROM_ERASE((Addr0 + Length0), ((Length - Length0) >> 15), Size_32KB);
    }

    if(Length1 >= Size_32KB)//back
    {
        StartAddr = Addr1;
        Length = Length1;

        if((Addr1 + Length1) & (Size_32KB - 1))
        {
            Addr1 = ((StartAddr + Length1) & (~(Size_32KB - 1)));
            Length1 = (StartAddr + Length1) & (Size_32KB - 1);
        }
        else
        {
            Length1 = 0;
        }

        ROM_ERASE(StartAddr, ((Length - Length1) >> 15), Size_32KB);
    }

    /* Erase 1KB */
    if(Length0 >= Size_1KB) //front
    {
        Length = Length0;
        if(Addr0 & (Size_1KB - 1))
        {
            Length0 = Size_1KB - (Addr0 & (Size_1KB - 1));
        }
        else
        {
            Length0 = 0;
        }

        ROM_ERASE((Addr0 + Length0), ((Length - Length0) >> 10), Size_1KB);
    }

    if(Length1 >= Size_1KB) //back
    {
        StartAddr = Addr1;
        Length = Length1;

        if((Addr1 + Length1) & (Size_1KB - 1))
        {
            Addr1 = ((StartAddr + Length1) & (~(Size_1KB - 1)));
            Length1 = (StartAddr + Length1) & (Size_1KB - 1);
        }
        else
        {
            Length1 = 0;
        }

        ROM_ERASE(StartAddr, ((Length - Length1) >> 10), Size_1KB);
    }

    /* Erase 256B */
    if(Length0)//front
    {
        ROM_ERASE(Addr0, (Length0 >> 8), Size_256B);
    }

    if(Length1)//back
    {
        ROM_ERASE(Addr1, (Length1 >> 8), Size_256B);
    }

    FLASH->CTLR |= CR_FLOCK_Set;
    FLASH->CTLR |= CR_LOCK_Set;

    return status;
}


/*********************************************************************
 * @fn      FLASH_ROM_WRITE
 *
 * @brief   Writes a specified FLASH .
 *
 * @param   StartAddr - Writes Flash start address(StartAddr%256 == 0).
 *          Length - Writes Flash start Length(Length%256 == 0).
 *          pbuf - Writes Flash value buffer.
 *
 * @return  FLASH Status - The returned value can be: FLASH_ADR_RANGE_ERROR,
 *        FLASH_ALIGN_ERROR, FLASH_OP_RANGE_ERROR or FLASH_COMPLETE.
 */
FLASH_Status FLASH_ROM_WRITE(uint32_t StartAddr, uint32_t *pbuf, uint32_t Length)
{
    uint32_t i, adr;
    uint8_t size;

    FLASH_Status status = FLASH_COMPLETE;

    if((StartAddr < ValidAddrStart) || (StartAddr >= ValidAddrEnd))
    {
        return FLASH_ADR_RANGE_ERROR;
    }

    if((StartAddr + Length) > ValidAddrEnd)
    {
        return FLASH_OP_RANGE_ERROR;
    }

    if((StartAddr & (Size_256B-1)) || (Length & (Size_256B-1)) || (Length == 0))
    {
        return FLASH_ALIGN_ERROR;
    }
    adr = StartAddr;
    i = Length >> 8;

    /* Authorize the FPEC of Bank1 Access */
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;

    /* Fast program mode unlock */
    FLASH->MODEKEYR = FLASH_KEY1;
    FLASH->MODEKEYR = FLASH_KEY2;
	
	FLASH->CTLR &= (CR_OPTER_Reset & CR_PAGE_ER_Reset);

    do{
        FLASH->CTLR |= CR_PAGE_PG;
        FLASH->CTLR |= CR_BUF_RST;
        while(FLASH->STATR & SR_BSY)
            ;
        size = 64;
        while(size)
        {
            *(uint32_t *)StartAddr = *(uint32_t *)pbuf;
            FLASH->CTLR |= CR_BUF_LOAD;
            while(FLASH->STATR & SR_BSY)
                ;
            StartAddr += 4;
            pbuf += 1;
            size -= 1;
        }

        FLASH->ADDR = adr;
        FLASH->CTLR |= CR_STRT_Set;
        while(FLASH->STATR & SR_BSY)
            ;
        FLASH->CTLR &= ~CR_PAGE_PG;
        adr += 256;
    }while(--i);

    FLASH->CTLR |= CR_FLOCK_Set;
    FLASH->CTLR |= CR_LOCK_Set;

    return status;
}

////////////////////////////////////////////////////////////////////////////



/*********************************************************************
 * @fn      FLASH_Lock_Fast
 *
 * @brief   Locks the Fast Program Erase Mode.
 *
 * @return  none
 */
void FLASH_Lock_Fast(void)
{
    FLASH->CTLR |= CR_FLOCK_Set;
}

/*********************************************************************
 * @fn      FLASH_ProgramPage_Fast
 *
 * @brief   Program a specified FLASH page (1page = 256Byte).
 *
 * @param   Page_Address - The page address to be programed.
 *
 * @return  none
 */
void FLASH_ProgramPage_Fast(uint32_t Page_Address)
{
    FLASH->CTLR |= CR_PAGE_PG;
    FLASH->ADDR = Page_Address;
    FLASH->CTLR |= CR_STRT_Set;
    while(FLASH->STATR & SR_BSY)
        ;
    FLASH->CTLR &= ~CR_PAGE_PG;
}

/*********************************************************************
 * @fn      FLASH_BufLoad
 *
 * @brief   Flash Buffer load(4Byte).
 *
 * @param   Address - specifies the address to be programmed.
 *          Data0 - specifies the data0 to be programmed.
 *
 * @return  none
 */
void FLASH_BufLoad(uint32_t Address, uint32_t Data0)
{
    FLASH->CTLR |= CR_PAGE_PG;
    *(__IO uint32_t *)(Address) = Data0;
    FLASH->CTLR |= CR_BUF_LOAD;
    while(FLASH->STATR & SR_BSY)
        ;
    FLASH->CTLR &= ~CR_PAGE_PG;
}

/*********************************************************************
 * @fn      FLASH_BufReset
 *
 * @brief   Flash Buffer reset.
 *
 * @return  none
 */
void FLASH_BufReset(void)
{
    FLASH->CTLR |= CR_PAGE_PG;
    FLASH->CTLR |= CR_BUF_RST;
    while(FLASH->STATR & SR_BSY)
        ;
    FLASH->CTLR &= ~CR_PAGE_PG;
}

/*********************************************************************
 * @fn      FLASH_Unlock_Fast
 *
 * @brief   Unlocks the Fast Program Erase Mode.
 *
 * @return  none
 */
void FLASH_Unlock_Fast(void)
{
    /* Authorize the FPEC of Bank1 Access */
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;

    /* Fast program mode unlock */
    FLASH->MODEKEYR = FLASH_KEY1;
    FLASH->MODEKEYR = FLASH_KEY2;
}

/********************************************************************************
 * @fn             FLASH_Unlock
 *
 * @brief          Unlocks the FLASH Program Erase Controller.
 *
 * @return         None
 */
void FLASH_Unlock(void)
{
    /* Authorize the FPEC of Bank1 Access */
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;
}

/********************************************************************************
 * @fn             FLASH_Lock
 *
 * @brief          Locks the FLASH Program Erase Controller.
 *
 * @return         None
 */
void FLASH_Lock(void)
{
    FLASH->CTLR |= CR_LOCK_Set;
}

/********************************************************************************
 * @fn             FLASH_EraseOptionBytes
 *
 * @brief          Erases the FLASH option bytes.
 *
 * @return         FLASH Status - The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 *                 FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_EraseOptionBytes(void)
{
    FLASH_Status status = FLASH_COMPLETE;

    status = FLASH_WaitForLastOperation(EraseTimeout);
    if(status == FLASH_COMPLETE)
    {
        FLASH_Unlock();

        FLASH->OBKEYR = FLASH_KEY1;
        FLASH->OBKEYR = FLASH_KEY2;

        FLASH->CTLR |= CR_OPTER_Set;
        FLASH->CTLR |= CR_STRT_Set;
        status = FLASH_WaitForLastOperation(EraseTimeout);

        FLASH->CTLR &= CR_OPTER_Reset;

        FLASH_Lock();
    }
    return status;
}


/*********************************************************************
 * @fn        FLASH_OptionBytePR
 *
 * @brief     Programs option bytes.
 *
 * @param     pbuf - data.
 *
 * @return    none
 */
void FLASH_OptionBytePR(u32* pbuf)
{
    uint8_t i;

    FLASH_EraseOptionBytes();
    FLASH_Unlock_Fast();
    FLASH_BufReset();

    for(i=0; i<4; i++)
    {
        FLASH_BufLoad((OB_BASE + 4*i), *pbuf++);
    }

    FLASH_ProgramPage_Fast(OB_BASE);
    FLASH_Lock_Fast();
}

/*********************************************************************
 * @fn      FLASH_UserOptionByteConfig
 *
 * @brief   Programs the FLASH User Option Byte - IWDG_SW / RST_STOP / RST_STDBY.
 *
 * @param   OB_IWDG - Selects the IWDG mode
 *            OB_IWDG_SW - Software IWDG selected
 *            OB_IWDG_HW - Hardware IWDG selected
 *          OB_STOP - Reset event when entering STOP mode.
 *            OB_STOP_NoRST - No reset generated when entering in STOP
 *            OB_STOP_RST - Reset generated when entering in STOP
 *          OB_STDBY - Reset event when entering Standby mode.
 *            OB_STDBY_NoRST - No reset generated when entering in STANDBY
 *            OB_STDBY_RST - Reset generated when entering in STANDBY
 *          OB_RST - Selects the reset IO mode and Ignore delay time
 *            OB_RST_NoEN - Reset IO disable
 *            OB_RST_EN_DT12ms - Reset IO enable and  Ignore delay time 12ms
 *            OB_RST_EN_DT1ms - Reset IO enable and  Ignore delay time 1ms
 *            OB_RST_EN_DT128us - Reset IO enable and  Ignore delay time 128us
 *
 * @return  FLASH Status - The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 *        FLASH_ERROR_WRP, FLASH_COMPLETE , FLASH_TIMEOUT or FLASH_RDP.
 */
FLASH_Status FLASH_UserOptionByteConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY, uint8_t OB_RST)
{
    FLASH_Status status = FLASH_COMPLETE;
    uint8_t UserByte;
    uint32_t buf[4];
    uint8_t i;

    if((FLASH->OBR & RDPRT_Mask) != (uint32_t)RESET)
    {
        status = FLASH_RDP;
    }
    else{
        UserByte = OB_IWDG | (uint8_t)(OB_STOP | (uint8_t)(OB_STDBY | (uint8_t)(OB_RST | (uint8_t)0xE0)));

        for(i=0; i<4; i++){
            buf[i] = *(uint32_t*)(OB_BASE + 4*i);
        }
        buf[0] = ((uint32_t)((((uint32_t)(UserByte) & 0x00FF) << 16) + (((uint32_t)(~UserByte) & 0x00FF) << 24))) + 0x00005AA5;

        FLASH_OptionBytePR(buf);
    }

    return status;
}


// CRC-8 calculation (standard polynomial 0x07)
uint8_t crc8(const uint8_t *data, uint16_t length) {
    uint8_t crc = 0x00;
    uint8_t polynomial = 0x07;  // x^8 + x^2 + x + 1
    
    for (uint16_t i = 0; i < length; i++) {
        crc ^= data[i];
        
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ polynomial;
            } else {
                crc = crc << 1;
            }
        }
    }
    
    return crc;
}

int8_t read_struct_from_flash(char * a_struct, size_t a_size){

    uint32_t i = 0;

    uint32_t buf_size = 1 + a_size / 4;
    if (buf_size > Fsize)
        buf_size = Fsize;

    u32* buf_struct = (u32*)a_struct;

    for(i = 0; i < buf_size; i++){
        buf_struct[i] = *(u32 *)(Fadr + 4 * i);
    }

    return 0;

}

int8_t write_struct_to_flash(char * a_struct, size_t a_size){

    uint32_t i = 0;

    FLASH_Status s;

    //uint8_t b = 0;

    u32 buf[Fsize];
    for (i = 0 ; i < Fsize; i++)
      buf[i] = (u32)-1;

    uint8_t* buf_char = (uint8_t*) &buf;


    s = FLASH_ROM_ERASE(Fadr, Fsize*4);
    if(s != FLASH_COMPLETE)
    {
        //printf("check FLASH_ADR_RANGE_ERROR FLASH_ALIGN_ERROR or FLASH_OP_RANGE_ERROR\r\n");
        return -1;
    }

    memcpy(buf_char, a_struct, a_size);

    s = FLASH_ROM_WRITE(Fadr,  buf, Fsize*4);
    if(s != FLASH_COMPLETE)
    {
        //printf("check FLASH_ADR_RANGE_ERROR FLASH_ALIGN_ERROR or FLASH_OP_RANGE_ERROR\r\n");
        return -2;
    }


}

