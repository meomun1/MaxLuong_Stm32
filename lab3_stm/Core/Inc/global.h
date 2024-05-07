/*
 * global.h
 *
 *  Created on: May 6, 2024
 *      Author: Administrator
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "software_timer.h"
#include "button.h"
#include "main.h"

#define INIT 1
#define AUTO_RED 2
#define AUTO_GREEN 3
#define AUTO_YELLOW 4
#define SECOND_INIT 5

extern int status1;
extern int status2;


extern int red_time;
extern int green_time;
extern int yellow_time;

extern int led_time_1;
extern int led_time_2;



#endif /* INC_GLOBAL_H_ */
