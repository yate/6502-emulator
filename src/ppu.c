/*
 * ppu.c
 *
 *  Created on: Jul 13, 2013
 *      Author: Yate
 */
#include <stdint.h>

#include "ppu.h"

void ppu_load_vrom(ppu_t *ppu, rom_t *rom) {
	memcpy(ppu->memory + PATTERN_TABLE_0, rom->vrom_banks, rom->vrom_size);
}

ppu_t create_ppu(rom_t *rom) {
	ppu_t ppu;

	ppu.mirroring_mode = rom->mirroring_mode;
	ppu_load_vrom(&ppu, rom);

	return ppu;
}

void ppu_draw(ppu_t *ppu, SDL_Texture *screen_texture, SDL_Renderer *renderer) {
//	for (uint16_t pattern_address = PATTERN_TABLE_0; pattern_address < 0x2000; pattern_address += 16) {
//		uint8_t layer_one = ppu->memory[pattern_address];
//		uint8_t layer_two = ppu->memory[pattern_address + 8];
//		uint8_t final_palette = 0;
//	}

	for (uint16_t nametable_index = NAME_TABLE_0; nametable_index <= 0x23c0; nametable_index++) {
		uint8_t tile = ppu->memory[NAME_TABLE_0 + nametable_index];
		uint8_t attr = ppu->memory[ATTR_TABLE_0];
	}
}

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

