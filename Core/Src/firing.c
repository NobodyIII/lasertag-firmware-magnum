/*
 * firing.c
 *
 *  Created on: Apr 24, 2020
 *      Author: blarson
 */

#include "audio.h"
#include "ir_data.h"
#include "ir_out.h"
#include "firing.h"
#include "gpio.h"
#include "player.h"

#include "rgb.h"

#define LASER_ON_TIME 100

static int laser_off_timer = 0;

int is_firing()
{
  //TODO: figure out what should be here (remove the function?)
  return 0;
//  return firing_repeat == 0;
}

void firing_trigger_press()
{
  //TODO: fill for basic play
//  rgb_output(RGB_COLOR_RED, 1);
  if (player_can_shoot()) {
    ir_out_send_signal(player_fire());

    /* laser time! */
    laser_off_timer = LASER_ON_TIME;
    HAL_GPIO_WritePin(LASER_CTL_GPIO_Port, LASER_CTL_Pin, 1);

    /* start the sound */
    audio_play(SOUND_FIRE_1, 1);
  }
}

void firing_trigger_release()
{
  //TODO: fill for advanced play
//  rgb_output(RGB_COLOR_GREEN, 1);
}

void firing_weapon_select(int direction) { /* +1 for forward, -1 for backward */
  //TODO: fill for advanced play
  //TODO: remove debugging code
  audio_play(SOUND_GAME_OVER, 1);
  rgb_output(RGB_COLOR_BLUE, 1);
}

void firing_tick()
{
  //TODO: fill for basic play
  if (laser_off_timer > 0) {
      if (--laser_off_timer == 0)
	HAL_GPIO_WritePin(LASER_CTL_GPIO_Port, LASER_CTL_Pin, 0);
  }
}
