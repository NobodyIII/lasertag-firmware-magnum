/*
 * audio.c
 *
 *  Created on: Apr 9, 2020
 *      Author: Ben Larson
 */

/* this code requires raw 16-bit signed PCM, single channel, 8000Hz, stored on a w25qxx-compatible SPI flash chip */

/*
 * audio mechanism:
 * 1. there are 2 buffers for page flipping
 * 2. when a sound starts playing, audio is enabled, buffer 1 is filled, then playback begins, then buffer 2 is filled
 * 3. when a buffer finishes playing, either (a) will happen if the sound isn't finished, or (b) if it is
 *    (a) playback begins on the other buffer, then the empty buffer is filled
 *    (b) audio is disabled
 */

#include "w25qxxConf.h"
#include "w25qxx.h"

#include "audio.h"
#include "error.h"
#include "i2s.h"

#define AUDIO_SPI &hspi2
#define BUFFER_SAMPLES 256
#define SAMPLE_BYTES 2

typedef struct {
  uint32_t start;
  uint32_t length;
} sound_t;

static sound_t sounds[AUDIO_NUM_SOUNDS];

/* disable IRQs when writing to these variables! */
static uint32_t sound_head = 0;
static uint32_t sound_bytes_left = 0;

/* audio out buffer: 2 pages of BUFFER_SAMPLES, with junk data for the unused channels */
static int16_t output_buffer[2][BUFFER_SAMPLES][2];
static int output_buffer_size[2];
static int16_t input_buffer[BUFFER_SAMPLES];

//static uint16_t audio_buffer[BUFFER_SIZE];

//static int current_buffer;

void audio_init()
{
  /* initialize flash */
  W25qxx_Init();

  /* read sound metadata */
  W25qxx_ReadBytes((uint8_t*)sounds, 0, sizeof(sounds));

  //TODO: remove?
  /* start DMA */
  HAL_I2S_Transmit_DMA(&hi2s1, (uint16_t*)output_buffer, BUFFER_SAMPLES * 4);
}

static void audio_enable()
{
  /* assert audio_enable GPIO pin */
  HAL_GPIO_WritePin(AUDIO_ENABLE_GPIO_Port, AUDIO_ENABLE_Pin, 1);

  /* start DMA */
//  HAL_I2S_Transmit_DMA(&hi2s1, (uint16_t*)output_buffer, BUFFER_SAMPLES * 4);
}

static void audio_disable()
{
  /* de-assert audio_enable GPIO pin */
  HAL_GPIO_WritePin(AUDIO_ENABLE_GPIO_Port, AUDIO_ENABLE_Pin, 0);

  /* stop DMA */
//  HAL_I2S_DMAStop(&hi2s1);
}

static void audio_fill_buffer(int buffer)
{
  volatile int start_tick = HAL_GetTick();

  if (!sound_bytes_left) {
    sound_head = 0;
    audio_disable();
    return;
  }

  /* read bytes into input buffer */
  uint32_t read_length = (sound_bytes_left < BUFFER_SAMPLES)? sound_bytes_left : BUFFER_SAMPLES;
  W25qxx_ReadBytes((uint8_t*)input_buffer, sound_head, read_length);
  sound_head += read_length;
  sound_bytes_left -= read_length;

  volatile int duration = HAL_GetTick() - start_tick;

  /* copy data from input buffer to output buffer */
  for (int i = 0; i < read_length; i++) {
    int16_t sample = input_buffer[i];
    output_buffer[buffer][i][0] = sample;
    /* ignore unused channel */
  }
  output_buffer_size[buffer] = read_length * 2;

}

void audio_tx_complete(int buffer) {
  /* refill the fully transmitted buffer */
  audio_fill_buffer(buffer);
}

int audio_play(sound_ref_t sound_ref, int override)
{
  /* stop if we're already playing a sound and override parameter is 0 */
  if (sound_head && !override)
    return LT_RESOURCE_BUSY;

  sound_t sound = sounds[(int)sound_ref];

  /* prevent race conditions when changing sounds */

  __disable_irq();

  audio_disable();

  sound_head = sound.start;
  sound_bytes_left = sound.length;

  __enable_irq();

//  audio_fill_buffer(0);
//  audio_fill_buffer(1);

  audio_enable();

  return 0;
}


