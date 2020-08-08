/*
 * rgb.c
 *
 *  Created on: Apr 14, 2020
 *      Author: blarson
 */

#include "main.h"
#include "rgb.h"

#define RGB_GPIO_MASK_INV 0x1FFF

static const uint16_t color_gpio[RGB_NUM_COLORS] =
    {0x0000, 0x8000, 0x2000, 0x4000, 0xc000, 0xa000, 0x6000, 0xe000};

static rgb_color_ref_t rgb_color;
static int rgb_brightness = 0;

static int rgb_brightness_counter = 0;

static void rgb_output_color(rgb_color_ref_t color)
{
  /* set RGB pins */
  RGB_GPIO_Port->ODR = (RGB_GPIO_Port->ODR & RGB_GPIO_MASK_INV) | color_gpio[(int)color];
}

void rgb_output(rgb_color_ref_t color, int brightness)
{
  rgb_color = color;
  rgb_brightness = brightness;
}

void rgb_tick()
{
  /* increment counter */
  rgb_brightness_counter = (rgb_brightness_counter + 1) % RGB_MAX_BRIGHTNESS;

  /* use brightness to produce PWM signal */
  if (rgb_brightness > rgb_brightness_counter)
    rgb_output_color(rgb_color);
  else
    rgb_output_color(RGB_COLOR_BLACK);
}
