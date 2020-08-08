/*
 * player.h
 *
 *  Created on: Apr 19, 2020
 *      Author: blarson
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "main.h"

#define MAX_PLAYERS 64
#define MAX_TEAMS 7

typedef enum {
  PLAYER_UNCONFIGURED,
  PLAYER_WILL_START,
  PLAYER_ALIVE,
  PLAYER_SHOT,
  PLAYER_DEAD
} player_state_t;

extern player_state_t player_state;

void player_set_num_teams(int teams, int enable_friendly_fire);
void player_set_max_hp(int hp);
void player_set_lives(int lives);
void player_set_revive_delay(int seconds);

void player_reset(void);

void player_shot(int shooter, int team, int damage);

int player_can_shoot(void);
uint32_t player_fire(void);

void player_team_select(void);

void player_tick(void);

/* packet contents (firing):
 * [15:14] firing code: 10
 * [13:8] player ID (player 0 is environment; all players take damage from player 0)
 * [7:4] damage dealt
 * [3:0] error detection code = number of 0 bits in the rest of the packet
 */

/* packet contents (setup):
 * [15:14] setup code: 01
 */

#endif /* PLAYER_H_ */
