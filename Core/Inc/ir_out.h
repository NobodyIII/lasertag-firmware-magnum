/*
 * ir_out.h
 *
 *  Created on: Apr 17, 2020
 *      Author: blarson
 */

#ifndef IR_OUT_H_
#define IR_OUT_H_

#include "main.h"

#define IR_OUT_DATA_TIMER &htim16

int ir_out_send_signal(uint16_t signal);

void ir_out_init(void);
void ir_out_data_timer_isr(void);

#endif /* IR_OUT_H_ */
