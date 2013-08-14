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
		return rom;
	}

	for (int i = 0; i < 4; i++) {
		rom.magic_number[i] = fgetc(file);
	}

	if (*(uint32_t *) rom.magic_number != 0x1a53454e) {
		printf("Error: Not a valid .nes file");
		return rom;
	}

	printf("%x", *(uint32_t *) rom.magic_number);

	return rom;
}

