/*
 * rgb.h
 *
 *  Created on: Apr 14, 2020
 *      Author: blarson
 */

#ifndef RGB_H_
#define RGB_H_

typedef enum {
  RGB_COLOR_BLACK,
  RGB_COLOR_RED,
  RGB_COLOR_BLUE,
  RGB_COLOR_GREEN,
  RGB_COLOR_YELLOW,
  RGB_COLOR_MAGENTA,
  RGB_COLOR_CYAN,
  RGB_COLOR_WHITE
} rgb_color_ref_t;

#define RGB_NUM_COLORS 8
#define RGB_MAX_BRIGHTNESS 10

void rgb_output(rgb_color_ref_t color, int brightness);
void rgb_tick(void);

#endif /* RGB_H_ */
