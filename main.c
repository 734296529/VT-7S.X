/**
  Generated Main Source File

  File Name:
    main.c
  
  Device:  
    PIC16LF15354
*/

#include "mcc_generated_files/mcc.h"
#include "soft_timer.h"
#include "fun.h"
#include "stdio.h"

/*
                         Main application
 */

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    SYS_PWR_EN_LAT = 1;     //模块供电
    //ACC映射脚电平初始化
    __delay_ms(10);
    CLRWDT();
    PWRKEY_LAT = 1;     //PWRKEY拉低
    __delay_ms(1000);   //延时1s左右  
    CLRWDT();
    MCU_PWR_ON_LAT = 1; //单片机电源自锁
    __delay_ms(1000);    //延时1s左右
    CLRWDT();
    PWRKEY_LAT = 0;
    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable();      //全局中断使能

    // Enable the Peripheral Interrupts 
    INTERRUPT_PeripheralInterruptEnable();  //外围中断使能  
    
    TMR2_StartTimer();              //开启硬件定时器2
    TIMERS_Add(0,2000,0,SYS_DownDet);   //添加软件定时器0，模块断电延时检测
    //TIMERS_Add(1,3000,0,SYS_DownDet);  //添加软件定时器1，模块断电延时检测
    TIMERS_Add(2,1000,1,USB_Handler);  //添加软件定时器2，USB切换
    TIMERS_Add(3,4000,0,KEY_Up);
    TIMERS_Add(4,9000,0,Force_Reboot);
    USB_Init();
    while (1)
    {
        LED_Manage();
        GPIO_MAP();
        CLRWDT();
    }
}

/**
 End of File
*/


