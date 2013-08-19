/*
 * rom.c
 *
 *  Created on: Aug 13, 2013
 *      Author: Yate
 */

#include "rom.h"

rom_t create_rom(char *filename) {
	rom_t rom;
	FILE *file = fopen(filename, "rb");

	if (file == NULL) {
		printf("Error: Failed to load rom %s", filename);
		exit(1);
	}

	for (int i = 0; i < 4; i++) {
		rom.magic_number[i] = fgetc(file);
	}

	if (*(uint32_t *) rom.magic_number != NES_MAGIC_NUMBER) {
		printf("Error: Not a valid .nes file");
		exit(1);
	}

	rom.prg_rom_size = fgetc(file) * 16384;
	rom.vrom_size = fgetc(file) * 8192;

	uint8_t flags = fgetc(file);
	rom.mirroring_mode = flags & 0x01;
	rom.has_battery_backed_ram = (flags >> 1) & 0x01;
	rom.has_trainer = (flags >> 2) & 0x01;
	rom.has_four_screen_vram = (flags >> 3) & 0x01;
	rom.low_bits_mapper_type = (flags >> 4) & 0x07;

	flags = fgetc(file);
	rom.is_vs_system_cartridge = flags & 0x01;
	rom.high_bits_mapper_type = (flags >> 4) & 0x07;

	rom.prg_ram_size_in_bytes = fgetc(file);
	if (rom.prg_ram_size_in_bytes == 0)
		rom.prg_ram_size_in_bytes = 1;

	flags = fgetc(file);
	rom.pal_or_ntsc = flags & 0x01;

	rom.rom_banks = malloc(rom.prg_rom_size);
	rom.vrom_banks = malloc(rom.vrom_size);

	if (rom.vrom_banks == NULL || rom.rom_banks == NULL) {
		printf("Failed to load ROM");
		exit(1);
	}

	fseek(file, 16, 0);

	for (int i = 0; i < rom.prg_rom_size; i++) {
		rom.rom_banks[i] = fgetc(file);
	}

	for (int i = 0; i < rom.vrom_size; i++) {
		rom.vrom_banks[i] = fgetc(file);
	}

	fclose(file);
	return rom;
}

void destroy_rom(rom_t *rom) {
	free(rom->rom_banks);
	free(rom->vrom_banks);
}

