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
	ppu.access_number = 0;
	ppu_load_vrom(&ppu, rom);

	return ppu;
}

void ppu_inc_access_number(ppu_t *ppu) {
	ppu->access_number++;
	ppu->access_number %= 2;
}

void ppu_draw(ppu_t *ppu, SDL_Texture *screen_texture, SDL_Renderer *renderer) {
	uint8_t pixel_buffer[256 * 240];
	uint16_t pixel_buffer_addr = 0;
	uint16_t nametable_address = NAME_TABLE_0;
	uint16_t attr_address = ATTR_TABLE_0;
	uint16_t start_attr_address = ATTR_TABLE_0;
	uint8_t row_num = 0;
	uint8_t col_num = 0;
	for (uint8_t nametable_row = 0; nametable_row < 30; nametable_row++) {
		for (uint8_t tile_num = 0; tile_num < 32; tile_num++) {
			uint8_t attr_byte = ppu->memory[attr_address];

			uint8_t bottom_right = attr_byte >> 6;
			uint8_t bottom_left = (attr_byte >> 4) & 0xff;
			uint8_t top_right = (attr_byte >> 2) & 0xff;
			uint8_t top_left = attr_byte & 0xff;

			uint8_t palette_index_attr;

			if (row_num <= 2) {
				if (col_num <= 2) {
					palette_index_attr = top_left;
				} else {
					palette_index_attr = top_right;
				}
			} else {
				if (col_num <= 2) {
					palette_index_attr = bottom_right;
				} else {
					palette_index_attr = bottom_left;
				}
			}

			for (uint8_t low_tile_addr = ppu->memory[nametable_address]; low_tile_addr < 8; low_tile_addr++) {
				uint8_t high_tile_addr = ppu->memory[low_tile_addr + 8];

				for (int shift = 0; shift < 8; shift++) {
					uint8_t palette_index = (high_tile_addr << 1) | low_tile_addr;
					uint8_t pixel = ppu->memory[palette_index_attr * 4 + palette_index];
					pixel_buffer[pixel_buffer_addr++] = pixel;
				}
			}

			col_num++;

			if (col_num == 4) {
				attr_address++;
			}

			col_num = col_num % 4;
			nametable_address++;
		}

		row_num++;

		if (row_num == 4) {
			start_attr_address += 8;
		}
		attr_address = start_attr_address;
		row_num = row_num % 4;

		SDL_UpdateTexture(screen_texture, NULL, pixel_buffer, 32 * sizeof(uint8_t));
		SDL_RenderCopy(renderer, screen_texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
}

