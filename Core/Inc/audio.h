/*
 * audio.h
 *
 *  Created on: Apr 9, 2020
 *      Author: Ben Larson
 */

#ifndef AUDIO_H_
#define AUDIO_H_

typedef enum {
  SOUND_POWER,
  SOUND_CONFIGURED,
  SOUND_START,
  SOUND_HIT,
  SOUND_DEAD,
  SOUND_REVIVE,
  SOUND_GAME_OVER,
  SOUND_FIRE_1,
  SOUND_RSRV1,
  SOUND_RSRV2,
  SOUND_RSRV3,
  SOUND_RSRV4,
  SOUND_RSRV5,
  SOUND_RSRV6,
  SOUND_RSRV7,
  SOUND_RSRV8,
} sound_ref_t;

#define AUDIO_NUM_SOUNDS 16

void audio_init(void);
int audio_play(sound_ref_t sound_id, int override);
void audio_tx_complete(int buffer);
//void audio_timer_isr(void);

#endif /* AUDIO_H_ */
