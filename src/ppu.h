/*
 * ppu.h
 *
 *  Created on: Jul 13, 2013
 *      Author: Yate
 */

#ifndef PPU_H_
#define PPU_H_

#define PATTERN_TABLE_0 0x0000;
#define PATTERN_TABLE_1 0x1000;

#define NAME_TABLE_0 0x2000;
#define NAME_TABLE_1 0x2400;
#define NAME_TABLE_2 0x2800;
#define NAME_TABLE_3 0x2C00;

#define ATTR_TABLE_0 0x23C0;
#define ATTR_TABLE_1 0x27C0;
#define ATTR_TABLE_2 0x2BC0;
#define ATTR_TABLE_3 0x2FC0;

#define IMAGE_PALETTE 0x3F00;
#define SPRITE_PALETTE 0x3F10;

extern uint8_t ppu_memory[0x4000];



#endif /* PPU_H_ */
