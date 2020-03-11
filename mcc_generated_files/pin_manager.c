/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC16LF15354
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB             :  MPLAB X 4.15

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include <xc.h>
#include "pin_manager.h"
#include "stdbool.h"
#include "../soft_timer.h"
#include "mcc.h"
#include "stdio.h"
#include "../PTN5150/ptn5150.h"




void (*IOCAF0_InterruptHandler)(void);
void (*IOCAF1_InterruptHandler)(void);
void (*IOCAF2_InterruptHandler)(void);
void (*IOCAF3_InterruptHandler)(void);
void (*IOCAF5_InterruptHandler)(void);
void (*IOCBF0_InterruptHandler)(void);
void (*IOCBF3_InterruptHandler)(void);


void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATA = 0x80;
    LATB = 0x00;
    LATC = 0x01;

    /**
    TRISx registers
    */
    TRISA = 0x0F;
    TRISB = 0xCF;
    TRISC = 0x00;
    
    /**
    ANSELx registers
    */
    ANSELC = 0x00;
    ANSELB = 0x40;
    ANSELA = 0x00;

    /**
    WPUx registers
    */
    WPUE = 0x00;           
    WPUB = 0x88;
    WPUA = 0x0F;
    WPUC = 0x00;
    
    /**
    ODx registers
    */
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;


    /**
    IOCx registers 
    */
    //interrupt on change for group IOCAF - flag    
    IOCAFbits.IOCAF0 = 0;
    //interrupt on change for group IOCAF - flag
    IOCAFbits.IOCAF1 = 0;
    //interrupt on change for group IOCAF - flag
    IOCAFbits.IOCAF2 = 0;
    //interrupt on change for group IOCAF - flag
    IOCAFbits.IOCAF3 = 0;
    //interrupt on change for group IOCAF - flag
    IOCAFbits.IOCAF5 = 0;
    //interrupt on change for group IOCAN - negative
    IOCANbits.IOCAN0 = 0;
    //interrupt on change for group IOCAN - negative
    IOCANbits.IOCAN1 = 0;
    //interrupt on change for group IOCAN - negative
    IOCANbits.IOCAN2 = 1;
    //interrupt on change for group IOCAN - negative
    IOCANbits.IOCAN3 = 1;
    //interrupt on change for group IOCAN - negative
    IOCANbits.IOCAN5 = 0;
    //interrupt on change for group IOCAP - positive
    IOCAPbits.IOCAP0 = 0;
    //interrupt on change for group IOCAP - positive
    IOCAPbits.IOCAP1 = 0;
    //interrupt on change for group IOCAP - positive
    IOCAPbits.IOCAP2 = 1;
    //interrupt on change for group IOCAP - positive
    IOCAPbits.IOCAP3 = 1;
    //interrupt on change for group IOCAP - positive
    IOCAPbits.IOCAP5 = 0;
    //interrupt on change for group IOCBF - flag
    IOCBFbits.IOCBF0 = 0;
    //interrupt on change for group IOCBF - flag
    IOCBFbits.IOCBF3 = 0;
    //interrupt on change for group IOCBN - negative
    IOCBNbits.IOCBN0 = 1;
    //interrupt on change for group IOCBN - negative
    IOCBNbits.IOCBN3 = 0;
    //interrupt on change for group IOCBP - positive
    IOCBPbits.IOCBP0 = 1;
    //interrupt on change for group IOCBP - positive
    IOCBPbits.IOCBP3 = 0;



    // register default IOC callback functions at runtime; use these methods to register a custom function
    IOCAF0_SetInterruptHandler(IOCAF0_DefaultInterruptHandler);
    IOCAF1_SetInterruptHandler(IOCAF1_DefaultInterruptHandler);
    IOCAF2_SetInterruptHandler(IOCAF2_DefaultInterruptHandler);
    IOCAF3_SetInterruptHandler(IOCAF3_DefaultInterruptHandler);
    IOCAF5_SetInterruptHandler(IOCAF5_DefaultInterruptHandler);
    IOCBF0_SetInterruptHandler(IOCBF0_DefaultInterruptHandler);
    IOCBF3_SetInterruptHandler(IOCBF3_DefaultInterruptHandler);
   
    // Enable IOCI interrupt 
    PIE0bits.IOCIE = 1; 
    
    #if (__XC8_VERSION <= 1380)
    #define ADACTPPSbits ADCACTPPSbits
    #endif
	
    RB1PPS = 0x17;   //RB1->MSSP2:SCL2;    
    RB2PPS = 0x18;   //RB2->MSSP2:SDA2;    
    SSP2CLKPPSbits.SSP2CLKPPS = 0x09;   //RB1->MSSP2:SCL2;    
    SSP2DATPPSbits.SSP2DATPPS = 0x0A;   //RB2->MSSP2:SDA2;    
}
  
void PIN_MANAGER_IOC(void)
{   
	// interrupt on change for pin IOCAF0
    if(IOCAFbits.IOCAF0 == 1)
    {
        IOCAF0_ISR();  
    }	
	// interrupt on change for pin IOCAF1
    if(IOCAFbits.IOCAF1 == 1)
    {
        IOCAF1_ISR();  
    }	
	// interrupt on change for pin IOCAF2
    if(IOCAFbits.IOCAF2 == 1)
    {
        IOCAF2_ISR();  
    }	
	// interrupt on change for pin IOCAF3
    if(IOCAFbits.IOCAF3 == 1)
    {
        IOCAF3_ISR();  
    }	
	// interrupt on change for pin IOCAF5
    if(IOCAFbits.IOCAF5 == 1)
    {
        IOCAF5_ISR();  
    }	
	// interrupt on change for pin IOCBF0
    if(IOCBFbits.IOCBF0 == 1)
    {
        IOCBF0_ISR();  
    }
	// interrupt on change for pin IOCBF3
    if(IOCBFbits.IOCBF3 == 1)
    {
        IOCBF3_ISR();  
}
    }	

/**
   IOCAF0 Interrupt Service Routine
*/
void IOCAF0_ISR(void) {

    // Add custom IOCAF0 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCAF0_InterruptHandler)
    {
        IOCAF0_InterruptHandler();
    }
    IOCAFbits.IOCAF0 = 0;
}

/**
  Allows selecting an interrupt handler for IOCAF0 at application runtime
*/
void IOCAF0_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCAF0_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCAF0
*/
void IOCAF0_DefaultInterruptHandler(void){
    // add your IOCAF0 interrupt custom code
    // or set custom function using IOCAF0_SetInterruptHandler()
}

/**
   IOCAF1 Interrupt Service Routine
*/
void IOCAF1_ISR(void) {

    // Add custom IOCAF1 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCAF1_InterruptHandler)
    {
        IOCAF1_InterruptHandler();
    }
    IOCAFbits.IOCAF1 = 0;
}

/**
  Allows selecting an interrupt handler for IOCAF1 at application runtime
*/
void IOCAF1_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCAF1_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCAF1
*/
void IOCAF1_DefaultInterruptHandler(void){
    // add your IOCAF1 interrupt custom code
    // or set custom function using IOCAF1_SetInterruptHandler()
}

/**
   IOCAF2 Interrupt Service Routine
*/
void IOCAF2_ISR(void) {

    // Add custom IOCAF2 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCAF2_InterruptHandler)
    {
        IOCAF2_InterruptHandler();
    }
    IOCAFbits.IOCAF2 = 0;
}

/**
  Allows selecting an interrupt handler for IOCAF2 at application runtime
*/
void IOCAF2_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCAF2_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCAF2
*/
void IOCAF2_DefaultInterruptHandler(void){
    // add your IOCAF2 interrupt custom code
    // or set custom function using IOCAF2_SetInterruptHandler()
    PWRKEY_LAT = !PWRKEY_ON_PORT; //按键映射
        /* 电源键按下 */
    if(PWRKEY_ON_PORT == 0){
        SYS_PWR_EN_LAT = 1;
        MCU_PWR_ON_LAT = 1;
        //TIMERS_Start(0); //2s检测开机
        TIMERS_Start(3); //4s屏蔽按键
        TIMERS_Start(4); //8s复位重启
    }
    else {
        TIMERS_Stop(4);
    }

}

/**
   IOCAF3 Interrupt Service Routine
*/
void IOCAF3_ISR(void) {

    // Add custom IOCAF3 code
    
    // Call the interrupt handler for the callback registered at runtime
    if(IOCAF3_InterruptHandler)
    {
        IOCAF3_InterruptHandler();
    }
    IOCAFbits.IOCAF3 = 0;
}

/**
  Allows selecting an interrupt handler for IOCAF3 at application runtime
*/
void IOCAF3_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCAF3_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCAF3
*/
void IOCAF3_DefaultInterruptHandler(void){
    // add your IOCAF3 interrupt custom code
    // or set custom function using IOCAF3_SetInterruptHandler()
}

/**
   IOCAF5 Interrupt Service Routine
*/
void IOCAF5_ISR(void) {

    // Add custom IOCAF5 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCAF5_InterruptHandler)
    {
        IOCAF5_InterruptHandler();
    }
    IOCAFbits.IOCAF5 = 0;
}

/**
  Allows selecting an interrupt handler for IOCAF5 at application runtime
*/
void IOCAF5_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCAF5_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCAF5
*/
void IOCAF5_DefaultInterruptHandler(void){
    // add your IOCAF5 interrupt custom code
    // or set custom function using IOCAF5_SetInterruptHandler()
}

/**
   IOCBF0 Interrupt Service Routine
*/
void IOCBF0_ISR(void) {

    // Add custom IOCBF0 code
    
    // Call the interrupt handler for the callback registered at runtime
    if(IOCBF0_InterruptHandler)
    {
        IOCBF0_InterruptHandler();
    }
    IOCBFbits.IOCBF0 = 0;
}
    
/**
  Allows selecting an interrupt handler for IOCBF0 at application runtime
*/
void IOCBF0_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCBF0_InterruptHandler = InterruptHandler;
}
    
/**
  Default interrupt handler for IOCBF0
*/
void IOCBF0_DefaultInterruptHandler(void){
    // add your IOCBF0 interrupt custom code
    // or set custom function using IOCBF0_SetInterruptHandler()

    if(!GPIO_28_PORT){
        /* 检测到GPIO_28低电平
         * 开启软定时器0，延迟300ms后再根据电平高低判断是关机还是重启
         */
        TIMERS_Start(0);
    }
}

/**
   IOCBF3 Interrupt Service Routine
*/
void IOCBF3_ISR(void) {

    // Add custom IOCBF3 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCBF3_InterruptHandler)
    {
        IOCBF3_InterruptHandler();
    }
    IOCBFbits.IOCBF3 = 0;
}

/**
  Allows selecting an interrupt handler for IOCBF3 at application runtime
*/
void IOCBF3_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCBF3_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCBF3
*/
void IOCBF3_DefaultInterruptHandler(void){
    // add your IOCBF3 interrupt custom code
    // or set custom function using IOCBF3_SetInterruptHandler()
}

/**
 End of File 
*/
