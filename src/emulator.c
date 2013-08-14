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
//#include "cpu.h"
#include "rom.h"

int main(int argc, char *argv[]) {

	//run_6502("adventure.obj");

	rom_t rom = create_rom("mario.nes");

	return 0;
}
