/* 
 * File:   soft_timer.h
 * Author: MY-PC
 *
 * Created on 2018年6月20日, 下午3:53
 */

#ifndef SOFT_TIMER_H
#define	SOFT_TIMER_H
#include <stdint.h>
#include <stdbool.h> 

#ifdef	__cplusplus
extern "C" {
#endif 
#define uint unsigned int    
#define MAX_SOFT_TIMER_COUNT    6
struct timers_t{
	bool isStart;
    bool isLoop;
    void (*pHandler)();
    uint count;
	uint curCount;    
};

void TIMERS_Add(uint index, uint count,bool loop, void (*pHandler)());
void TIMERS_Start(uint index);
void TIMERS_Start_Now(uint index);
void TIMERS_Stop(uint index);
void TIMERS_Manager(void);


#ifdef	__cplusplus
}
#endif

#endif	/* SOFT_TIMER_H */

