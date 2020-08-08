/*
 * ir_out.c
 *
 *  Created on: Apr 17, 2020
 *      Author: blarson
 */

#include "error.h"
#include "ir_common.h"
#include "ir_edc.h"
#include "ir_out.h"
#include "main.h"
#include "tim.h"

#include "rgb.h"

#define IR_PWM_TIMER &htim2
#define IR_PWM_CHANNEL TIM_CHANNEL_3

static uint32_t ir_out_signal = 0;
static int ir_out_signal_pos = -1; /* how many full bits are left? */

static int bit_ticks_left = 0;

static void toggle_output()
{
  HAL_GPIO_TogglePin(IR_DATA_OUT_GPIO_Port, IR_DATA_OUT_Pin);
}

static uint16_t signal_next_msb()
{
  uint16_t bit = (ir_out_signal >> ir_out_signal_pos) & 0x1;
  return bit;
}

int ir_out_send_signal(uint16_t signal)
{
  signal = ir_edc_prepend(signal);

  /* prevent race conditions */
  __disable_irq();

  /* fail if we are currently sending a signal */
  if (ir_out_signal_pos >= 0) {
    __enable_irq();
    return LT_RESOURCE_BUSY;
  }

  /* set current signal */
  ir_out_signal = signal;
  ir_out_signal_pos = IR_BITS_PER_PACKET;

  /* don't leave IRQs disabled */
  __enable_irq();
  return 0;
}

void ir_out_init()
{
  /* start our data timer */
  HAL_TIM_Base_Start_IT(IR_OUT_DATA_TIMER);

  /* for now, we always want the PWM running */
  HAL_TIM_PWM_Start(IR_PWM_TIMER, IR_PWM_CHANNEL);
}

void ir_out_data_timer_isr()
{
  /* are we currently sending a signal? */
  if (ir_out_signal_pos >= 0) {
    /* are we in the middle of a 1 bit? */
    if (bit_ticks_left) {
      /* decrement counter */
      bit_ticks_left--;
    /* or are we done with the current bit? */
    } else {
      /* terminate bit by transition in the signal */
      toggle_output();
      /* do we have more bits? */
      if (--ir_out_signal_pos >= 0)
	/* delay for an extra tick for a 1 bit */
	bit_ticks_left = signal_next_msb();
      /* no special code needed to terminate signal (odd # of bits including start code = end with signal low) */
    }
  }
}
