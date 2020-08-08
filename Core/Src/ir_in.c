/*
 * ir_in.c
 *
 *  Created on: Apr 17, 2020
 *      Author: blarson
 */

#include "main.h"
#include "ir_common.h"
#include "ir_data.h"
#include "ir_edc.h"
#include "ir_in.h"

#include "rgb.h"

/* see ir_common.h for IR coding description */

/* timer frequency: 40kHz (0.025ms) = 20 ticks per zero bit */

//TODO: (reliability) tune
#define MIN_TICKS_PER_ZERO_BIT 15
#define MAX_TICKS_PER_ZERO_BIT 25
#define MIN_TICKS_PER_ONE_BIT 35
#define MAX_TICKS_PER_ONE_BIT 45

static uint32_t signal_in = 0;
static int signal_pos = 0;

static void input_reset()
{
  signal_in = 0;
  signal_pos = 0;
}

static void input_complete()
{
  /* handle signal if it passes edc */
  if (ir_edc_verify(signal_in))
    ir_in_data_handler(signal_in);
  /* reset so we're ready for another signal */
  input_reset();
}

static void input_drop_first_bit()
{
  signal_pos--;
  signal_in &= ~(1 << signal_pos);
}

static void input_add_bit(unsigned bit)
{
  /* debug: verify we have just one bit */
  assert_param(bit <= 1);
  /* shift in new bit */
  signal_in <<= 1;
  signal_in |= bit;
  signal_pos++;
  /* check for bad start code */
  if (signal_pos == IR_START_CODE_LENGTH - 1 && signal_in != IR_START_CODE)
    input_drop_first_bit();
  /* check whether we have a complete signal */
  else if (signal_pos == IR_BITS_PER_PACKET)
    input_complete();
}

void ir_in_timer_callback(int delta_t)
{
  if (delta_t > MIN_TICKS_PER_ZERO_BIT && delta_t < MAX_TICKS_PER_ZERO_BIT)
    input_add_bit(0);
  else if (delta_t > MIN_TICKS_PER_ONE_BIT && delta_t < MAX_TICKS_PER_ONE_BIT)
    input_add_bit(1);
  else /* bad signal */
    input_reset();
}

void ir_in_init()
{
  HAL_TIM_IC_Start_IT(IR_IN_TIMER, IR_IN_TIMER_CHANNEL);
}


