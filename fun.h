#ifndef __FUN_H__
#define __FUN_H__
#include "mcc_generated_files/mcc.h"
#include "PTN5150/ptn5150.h"
void LED_Manage(void);
void SYS_DownDet(void);

void KEY_Up(void);
void Force_Reboot(void);

void GPIO_MAP(void);
void USB_Init(void);
void USB_Handler(void);
void USB_Switch(void);




#endif
