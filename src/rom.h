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

#define NES_MAGIC_NUMBER

typedef struct {
	uint8_t magic_number[4];
	uint8_t prg_rom_size;
	uint8_t chr_rom_size;
	uint8_t mirroring_mode;
	uint8_t has_battery_backed_ram;
	uint8_t has_trainer;
	uint8_t low_byte_mapper_type;
	uint8_t high_byte_mapper_type;
	uint8_t is_vs_system_cartridge;
	uint8_t prg_rom_size_in_bytes;
	uint8_t pal_or_ntsc;
	uint8_t *rom_banks;
	uint8_t *vom_banks;
} rom_t;


rom_t create_rom(char *filename);

#endif /* ROM_H_ */
