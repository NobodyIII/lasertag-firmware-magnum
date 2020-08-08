/*
 * buttons.c
 *
 *  Created on: Apr 9, 2020
 *      Author: Ben Larson
 */

#include "main.h"
#include "buttons.h"
#include "player.h"
#include "firing.h"

/* number of ticks a pin state change must last to be recognized (should be effective but low-latency) */
#define DEBOUNCE_TICKS 50
#define DEBOUNCE_PIN_COUNT 4

static void trigger_press()
{
  firing_trigger_press();
}

static void trigger_release()
{
  /* relevant for fully automatic modes */
  firing_trigger_release();
}

static void team_sel()
{
  player_team_select();
}

static void weapon_sel_bw()
{
  firing_weapon_select(-1);
}

static void weapon_sel_fw()
{
  firing_weapon_select(1);
}

/* no-op callback */
static void nop() { }

static uint16_t debounce_pin_status[DEBOUNCE_PIN_COUNT] = {0,0,0,0};
static unsigned debounce_timer[DEBOUNCE_PIN_COUNT] = {0,0,0,0};
static const uint16_t debounce_pins[DEBOUNCE_PIN_COUNT] = {TRIGGER_Pin, TEAM_SEL_Pin, WEAPON_SEL_BW_Pin, WEAPON_SEL_FW_Pin};
static const GPIO_TypeDef *debounce_ports[DEBOUNCE_PIN_COUNT] =
  {TRIGGER_GPIO_Port, TEAM_SEL_GPIO_Port, WEAPON_SEL_BW_GPIO_Port, WEAPON_SEL_FW_GPIO_Port};

typedef void (*callback)(void);
static const callback debounce_down_callback[DEBOUNCE_PIN_COUNT] =
  {trigger_press, team_sel, weapon_sel_bw, weapon_sel_fw};
static const callback debounce_up_callback[DEBOUNCE_PIN_COUNT] =
  {trigger_release, nop, nop, nop};

/* called once for each pin, regardless of which one was actually changed */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* arbitrarily pick a pin so we don't do the same thing multiple times */
//  if (GPIO_Pin == TRIGGER_Pin) {
    /* debounce each pin */
    for (int i = 0; i < DEBOUNCE_PIN_COUNT; i++) {
      int status  = !HAL_GPIO_ReadPin(debounce_ports[i], debounce_pins[i]);
      /* has the pin's input changed? */
      if (status != debounce_pin_status[i]) {
	/* set/reset debounce timer for pin */
	debounce_timer[i] = DEBOUNCE_TICKS;
      }
      debounce_pin_status[i] = status;
    }
//  }
}

/* worst-case interrupted scenario: debounce_timer[i] reset during decrement -
 * extremely unlikely; allows a single bounce through filter; not worth disabling irq */
void buttons_debounce_tick()
{
  for (int i = 0; i < DEBOUNCE_PIN_COUNT; i++) {
      if (debounce_timer[i] > 0) {
	debounce_timer[i]--;
	/* are we done waiting to debounce this pin? */
	if (debounce_timer[i] == 0) {
	  /* trigger pin's callback */
	  if (debounce_pin_status[i])
	    debounce_down_callback[i]();
	  else
	    debounce_up_callback[i]();
	}
    }
  }
}
