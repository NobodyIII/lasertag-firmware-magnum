/*
 * ir_data.h
 *
 *  Created on: Apr 19, 2020
 *      Author: blarson
 */

#ifndef IR_DATA_H_
#define IR_DATA_H_

#include "main.h"

void ir_in_data_handler(uint16_t data);

int ir_send_firing_packet(int player_id, int team_id, int damage);

#endif /* IR_DATA_H_ */
