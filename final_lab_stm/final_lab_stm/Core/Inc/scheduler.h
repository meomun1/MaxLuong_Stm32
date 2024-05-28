/*
 * scheduler.h
 *
 *  Created on: May 18, 2024
 *      Author: Administrator
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>

typedef struct{
	void (*pTask)(void); // task pointer
	uint32_t Delay; 	 // counter
	uint32_t Period;
	uint8_t RunMe;		 // timer_flag

	uint32_t TaskID;	 //

}sTasks;

#define SCH_MAX_TASKS 40
#define NO_TASK_ID 0

void SCH_Init(void);

// setTimer
void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD);

// timerRun
void SCH_Update(void);

// check timer flag
void SCH_Dispatch_Tasks(void);

void SCH_Delete(uint32_t ID);

#endif /* INC_SCHEDULER_H_ */
