/*
 * ir_edc.h
 *
 *  Created on: Apr 23, 2020
 *      Author: blarson
 */

#ifndef IR_EDC_H_
#define IR_EDC_H_

#include "main.h"

uint32_t ir_edc_prepend(uint32_t data);
int ir_edc_verify(uint32_t ir_in);

#endif /* IR_EDC_H_ */
