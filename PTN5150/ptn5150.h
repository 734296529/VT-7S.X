/* 
 * File:   ptn5150.h
 * Author: MY-PC
 *
 * Created on November 20, 2019, 11:16 AM
 */

#ifndef PTN5150_H
#define	PTN5150_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "../mcc_generated_files/mcc.h"
#define u8 unsigned char
#define u32 unsigned int 
void Idle(void);//I2Cø’œ–ºÏ≤‚
void write_nbyte(u8 Address,u8 Data[],u8 Num);
void read_nbyte(u8 Address,u8 Data[],u8 Num);

#ifdef	__cplusplus
}
#endif

#endif	/* PTN5150_H */

