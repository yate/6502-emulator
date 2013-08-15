/*
 * rom.h
 *
 *  Created on: Aug 13, 2013
 *      Author: Yate
 */

#ifndef ROM_H_
#define ROM_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define NES_MAGIC_NUMBER 0x1a53454e

typedef struct {
	uint8_t magic_number[4];
	uint16_t prg_rom_size;
	uint16_t vrom_size;
	uint8_t mirroring_mode;
	uint8_t has_battery_backed_ram; /* battery-backed RAM at 0x6000-0x7fff */
	uint8_t has_trainer; /* 512-byte trainer at $7000-$71ff */
	uint8_t has_four_screen_vram;
	uint8_t low_bits_mapper_type;
	uint8_t high_bits_mapper_type;
	uint8_t is_vs_system_cartridge;
	uint8_t prg_ram_size_in_bytes;
	uint8_t pal_or_ntsc;
	uint8_t *rom_banks;
	uint8_t *vrom_banks;
} rom_t;


rom_t create_rom(char *filename);
void destroy_rom(rom_t *rom);

#endif /* ROM_H_ */
