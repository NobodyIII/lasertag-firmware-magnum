/*
 * ir_data.c
 *
 *  Created on: Apr 19, 2020
 *      Author: blarson
 */

#include "ir_data.h"
#include "ir_out.h"
#include "player.h"

#include "rgb.h"

/*
 * firing packet:
 * error detection (4 bits)
 * packet type (2 bits)
 * player ID (6 bits)
 * team ID (3 bits) (team 0 = no friendly fire protection)
 * damage (4 bits)
 */

#define FIRING_PACKET_PLAYER_MASK 0x3f
#define FIRING_PACKET_PLAYER_SHIFT 7
#define FIRING_PACKET_TEAM_MASK 0x07
#define FIRING_PACKET_TEAM_SHIFT 4
#define FIRING_PACKET_DAMAGE_MASK 0x0f
#define FIRING_PACKET_DAMAGE_SHIFT 0

void ir_in_data_handler(uint16_t data)
{
  //TODO: fill for basic play
//  rgb_output(RGB_COLOR_BLUE, 1);
  player_shot(0, data, 1);
}

int ir_send_firing_packet(int player_id, int team_id, int damage)
{
  uint16_t packet = (player_id & FIRING_PACKET_PLAYER_MASK) << FIRING_PACKET_PLAYER_SHIFT
	     | (team_id & FIRING_PACKET_TEAM_MASK) << FIRING_PACKET_TEAM_SHIFT
	     | (damage & FIRING_PACKET_DAMAGE_MASK) << FIRING_PACKET_DAMAGE_SHIFT;
  return ir_out_send_signal(packet);
}
