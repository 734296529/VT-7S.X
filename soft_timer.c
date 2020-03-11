#include "soft_timer.h"
#include "mcc_generated_files/mcc.h"
struct timers_t soft_timers[MAX_SOFT_TIMER_COUNT] = {0};

void TIMERS_Start(uint index)
{
	soft_timers[index].isStart = 1;
	soft_timers[index].curCount = soft_timers[index].count;
}

void TIMERS_Start_Now(uint index)
{
	soft_timers[index].isStart = 1;
	soft_timers[index].curCount = 1;
}

void TIMERS_Stop(uint index)
{
	soft_timers[index].isStart = 0;
}

void TIMERS_Add(uint index, uint count,bool loop, void (*pHandler)())
{
	soft_timers[index].count = count;
	soft_timers[index].curCount = count;
	soft_timers[index].pHandler = pHandler;
	soft_timers[index].isStart = 0;
    soft_timers[index].isLoop = loop;
}

void TIMERS_Manager(void)
{
	uint i;
	for(i=0; i<MAX_SOFT_TIMER_COUNT; i++)
	{
		soft_timers[i].curCount --;
		if(soft_timers[i].curCount == 0 && soft_timers[i].isStart == 1)
		{			
            if(soft_timers[i].pHandler){
                soft_timers[i].pHandler();
            }
            if(soft_timers[i].isLoop){
                soft_timers[i].curCount = soft_timers[i].count;
            }else{
                soft_timers[i].isStart = 0;
            }
 		}			
	}
}

