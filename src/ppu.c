/*
 * ppu.c
 *
 *  Created on: Jul 13, 2013
 *      Author: Yate
 */
#include <stdint.h>

#include "ppu.h"

//uint8_t ppu_memory[0x4000];
//uint8_t mirroring_mode = MIRROR_HORIZONTAL;
//
//void write_name_table(uint16_t address, uint8_t data) {
//	uint16_t base_address = address & 0x0FFF;
//
//	if (mirroring_mode == MIRROR_HORIZONTAL) {
//		if (address < 0x2800) {
//			ppu_memory[NAME_TABLE_0 | base_address] = data;
//			ppu_memory[NAME_TABLE_1 | base_address] = data;
//		} else {
//			ppu_memory[NAME_TABLE_2 | base_address] = data;
//			ppu_memory[NAME_TABLE_3 | base_address] = data;
//		}
//	} else if (mirroring_mode == MIRROR_HORIZONTAL) {
//		if (address < 0x2400 || (address < 0x2C00 && address >= 0x2800)) {
//			ppu_memory[NAME_TABLE_0 | base_address] = data;
//			ppu_memory[NAME_TABLE_2 | base_address] = data;
//		} else {
//			ppu_memory[NAME_TABLE_1 | base_address] = data;
//			ppu_memory[NAME_TABLE_3 | base_address] = data;
//		}
//	}
//}
//
//uint8_t read_ppu_mem(uint16_t address) {
//	return ppu_memory[address];
//}

