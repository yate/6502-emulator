/*
 ============================================================================
 Name        : Emulator.c
 Author      : Mike Yeatts
 Version     :
 Copyright   : Your copyright notice
 Description : 6502 Emulator
 ============================================================================
 */

#include <stdio.h>
#include "cpu.h"
#include "ppu.h"
#include "rom.h"

int main(int argc, char *argv[]) {

	rom_t rom = create_rom("mario.nes");
	ppu_t ppu = create_ppu(&rom);
	cpu_load_rom(&rom);

	run_nes(&ppu);

	destroy_rom(&rom);

	return 0;
}
