/*
 * firing.h
 *
 *  Created on: Apr 24, 2020
 *      Author: blarson
 */

#ifndef FIRING_H_
#define FIRING_H_

void firing_trigger_press(void);
void firing_trigger_release(void);

void firing_weapon_select(int direction); /* +1 for forward, -1 for backward */
void firing_tick(void);

#endif /* FIRING_H_ */
