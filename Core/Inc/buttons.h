/*
 * buttons.h
 *
 *  Created on: Apr 9, 2020
 *      Author: Ben Larson
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void buttons_debounce_tick();

#endif /* BUTTONS_H_ */
