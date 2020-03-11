#include "fun.h"
#include "soft_timer.h"
#include "stdio.h"

void USB_Idle(void);
void LED_Manage(void)
{
    LED_GREEN_LAT = !STAT_IN_PORT;//LED灯切换
}

void SYS_DownDet(void){
    /* GPIO_28为模块开关机通讯脚*/
    /* 若为低电平则表示模块是关机状态，关闭模块电源和单片机自锁  */
    if(!GPIO_28_PORT && (IO_RB7_PORT)){
        SYS_PWR_EN_LAT = 0;
        MCU_PWR_ON_LAT = 0;
        __delay_ms(20);
    } 
}

void KEY_Up(void)
{
    PWRKEY_LAT = 0;     //PWRKEY拉高
}

//等待看门狗复位
void Force_Reboot(void)
{


    SYS_PWR_EN_LAT = 0;
    __delay_ms(10);
    SYS_PWR_EN_LAT = 1;
    
    PWRKEY_LAT = 1;     //PWRKEY拉低

    __delay_ms(1000);   //延时2s左右
    CLRWDT();
    __delay_ms(1000);
    
    PWRKEY_LAT = 0;

}

void GPIO_MAP(void)
{
    if(USB1_ID_PORT) //支架移除
    {
        GPIO_3_LAT = 0;
        GPIO_24_LAT = 1;//ACC映射高电平
    }
    else //支架接入
    {
        GPIO_3_LAT = 1;
        GPIO_24_LAT = ACC_IN_PORT;//ACC直接映射
    }
}

u8 typeC_state = 0;
void USB_Init(void)
{
    unsigned char reg = 0x00;

//    CC1_low_LAT = 0;
//    CC1_high_LAT = 0;
//    CC2_low_LAT = 0;
//    CC2_high_LAT = 0;
//    CC1_Ra_LAT = 0;
//    CC2_Ra_LAT = 0;
//    ID_SW_LAT = 0;
//    S_NX3DV221GM_LAT = 1;

    write_nbyte(0x18,&reg,1);
    TIMERS_Start(2);
}
void USB_Handler()
{
    u8 reg = 0;
    
//    read_nbyte(0x04,&reg,1);
//    printf("REG04=%02x\r\n",reg);
    
    if(!TypeC_DET_INT_PORT)//TypeC中断
    {
        USB_Switch();
        read_nbyte(0x03,&reg,1);
        read_nbyte(0x19,&reg,1); 
    }
    else if(!typeC_state)
    {
        if(!USB1_ID_PORT)//尾巴线2.0_ID脚拉低
        {
            CC1_low_LAT = 0;
            CC1_high_LAT = 0;
            CC2_low_LAT = 1;
            CC2_high_LAT = 0;
            CC1_Ra_LAT = 0;
            CC2_Ra_LAT = 0;
            S_NX3DV221GM_LAT = 0;
            ID_SW_LAT = 1;
            typeC_state = 0;
            //printf("USB2.0 \r\n\r\n");
        }
        else
        {
            CC1_low_LAT = 0;
            CC1_high_LAT = 0;
            CC2_low_LAT = 0;
            CC2_high_LAT = 0;
            CC1_Ra_LAT = 0;
            CC2_Ra_LAT = 0;
            S_NX3DV221GM_LAT = 1;
            ID_SW_LAT = 0;
            typeC_state = 0;
            //printf("USB Not Used\r\n\r\n");
        }
    }
}

void USB_Switch(void)
{
    u8 reg = 0;
    u8 Port_Status = 0,CC_Polarity = 0;

//    read_nbyte(0x03,&reg,1);
    read_nbyte(0x04,&reg,1);

    Port_Status =(reg>>2) & 7;
    CC_Polarity = reg & 3;
    ID_SW_LAT = 0;
    CC1_low_LAT = 0;
    CC1_high_LAT = 0;
    CC2_low_LAT = 0;
    CC2_high_LAT = 0;
    __delay_ms(50);
    switch(Port_Status)
    {
        case 1: //001:DFP attached
        {
            if(CC_Polarity ==1)
            {
                CC1_low_LAT = 0;
                CC1_high_LAT = 1;
                CC2_low_LAT = 0;
                CC2_high_LAT = 0;
                CC1_Ra_LAT = 0;
                CC2_Ra_LAT = 0;
                S_NX3DV221GM_LAT = 1;
                ID_SW_LAT = 0;
                //printf("DFP CC1\r\n\r\n");
            }
            else if(CC_Polarity ==2)
            {
                CC1_low_LAT = 0;
                CC1_high_LAT = 0;
                CC2_low_LAT = 0;
                CC2_high_LAT = 1;
                CC1_Ra_LAT = 0;
                CC2_Ra_LAT = 0;
                S_NX3DV221GM_LAT = 1;
                ID_SW_LAT = 0;
                //printf("DFP CC2\r\n\r\n");
            }
            typeC_state = 1;
        }
        break;

        case 2: //010:UFP attached
        {
            if(CC_Polarity ==1)
            {
                CC1_low_LAT = 1;
                CC1_high_LAT = 0;
                CC2_low_LAT = 0;
                CC2_high_LAT = 0;
                CC1_Ra_LAT = 0;
                CC2_Ra_LAT = 0;
                S_NX3DV221GM_LAT = 1;
                ID_SW_LAT = 1;
                //printf("UFP CC1\r\n\r\n");
            }
            else if(CC_Polarity ==2)
            {
                CC1_low_LAT = 0;
                CC1_high_LAT = 0;
                CC2_low_LAT = 1;
                CC2_high_LAT = 0;
                CC1_Ra_LAT = 0;
                CC2_Ra_LAT = 0;
                S_NX3DV221GM_LAT = 1;
                ID_SW_LAT = 1;
                //printf("UFP CC2\r\n\r\n");
            }  
            typeC_state = 1;
        }
        break;

        case 3: //011:Analog Audio Accessory attached
        {
            CC1_low_LAT = 0;
            CC1_high_LAT = 0;
            CC2_low_LAT = 0;
            CC2_high_LAT = 0;
            CC1_Ra_LAT = 1;
            CC2_Ra_LAT = 1;
            S_NX3DV221GM_LAT = 1;
            ID_SW_LAT = 0;
            typeC_state = 1;
            //printf("Audio Device\r\n\r\n");
        }
        break;

        case 4: //100: Debug Accessory attached
        {
            CC1_low_LAT = 1;
            CC1_high_LAT = 0;
            CC2_low_LAT = 1;
            CC2_high_LAT = 0;
            CC1_Ra_LAT = 0;
            CC2_Ra_LAT = 0;
            S_NX3DV221GM_LAT = 1;
            ID_SW_LAT = 0;
            typeC_state = 1;
            //printf("Debug Devices\r\n\r\n");
        }
        break;

        default:
        {
            if(!USB1_ID_PORT)//尾巴线2.0_ID脚拉低
            {
                CC1_low_LAT = 0;
                CC1_high_LAT = 0;
                CC2_low_LAT = 1;
                CC2_high_LAT = 0;
                CC1_Ra_LAT = 0;
                CC2_Ra_LAT = 0;
                S_NX3DV221GM_LAT = 0;
                ID_SW_LAT = 1;
                //printf("USB2.0 \r\n\r\n");
            }
            else
            {
                CC1_low_LAT = 0;
                CC1_high_LAT = 0;
                CC2_low_LAT = 0;
                CC2_high_LAT = 0;
                CC1_Ra_LAT = 0;
                CC2_Ra_LAT = 0;
                S_NX3DV221GM_LAT = 1;
                ID_SW_LAT = 0;
                //printf("USB Not Used\r\n\r\n");
            }
            typeC_state = 0;
        }
        break;
    }   

}

