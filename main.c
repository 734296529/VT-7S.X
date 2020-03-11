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
    SYS_PWR_EN_LAT = 1;     //ģ�鹩��
    //ACCӳ��ŵ�ƽ��ʼ��
    __delay_ms(10);
    CLRWDT();
    PWRKEY_LAT = 1;     //PWRKEY����
    __delay_ms(1000);   //��ʱ1s����  
    CLRWDT();
    MCU_PWR_ON_LAT = 1; //��Ƭ����Դ����
    __delay_ms(1000);    //��ʱ1s����
    CLRWDT();
    PWRKEY_LAT = 0;
    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable();      //ȫ���ж�ʹ��

    // Enable the Peripheral Interrupts 
    INTERRUPT_PeripheralInterruptEnable();  //��Χ�ж�ʹ��  
    
    TMR2_StartTimer();              //����Ӳ����ʱ��2
    TIMERS_Add(0,2000,0,SYS_DownDet);   //��������ʱ��0��ģ��ϵ���ʱ���
    //TIMERS_Add(1,3000,0,SYS_DownDet);  //��������ʱ��1��ģ��ϵ���ʱ���
    TIMERS_Add(2,1000,1,USB_Handler);  //��������ʱ��2��USB�л�
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


