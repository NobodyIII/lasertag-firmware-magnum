/*
 * ir_in.h
 *
 *  Created on: Apr 17, 2020
 *      Author: blarson
 */

#ifndef IR_IN_H_
#define IR_IN_H_

#include "tim.h"

#define IR_IN_TIMER &htim17
#define IR_IN_TIMER_CHANNEL TIM_CHANNEL_1

void ir_in_init(void);
void ir_in_timer_callback(int delta_t);

#endif /* IR_IN_H_ */
