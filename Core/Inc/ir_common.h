/*
 * ir_common.h
 *
 *  Created on: Apr 18, 2020
 *      Author: blarson
 */

#ifndef IR_COMMON_H_
#define IR_COMMON_H_

/*
 * custom IR encoding rules:
 * 1. each new bit begins with a transition (high-to-low or low-to-high)
 * 2. a '1' bit is twice as long as a zero bit
 * 3. a '0' bit is 0.5ms long (-> a '1' bit is 1ms long)
 * 4. (handled by hardware) the carrier wave is square, 38kHz @ 25% duty cycle, 940nm IR
 */

/* all packets are 16 bits long after a 2-bit start code: 00 */

/* code in ir_out.c assumes this is zero; change that if you change this */
#define IR_START_CODE 0x0
#define IR_START_CODE_LENGTH 0

#define IR_EDC_LENGTH 4
#define IR_EDC_MASK 0x1e000

#define IR_DATA_LENGTH 13
#define IR_DATA_MASK 0x1fff

#define IR_EDC_SHIFT IR_DATA_LENGTH
#define IR_BITS_PER_PACKET IR_DATA_LENGTH + IR_EDC_LENGTH + IR_START_CODE_LENGTH

#endif /* IR_COMMON_H_ */
