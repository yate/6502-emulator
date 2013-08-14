/*
 * cpu.c
 *
 *  Created on: Jun 17, 2013
 *      Author: n0210015
 */

#include "cpu.h"
#include "ppu.h"

uint8_t A = 0; /* accumulator register */
uint8_t X = 0; /* index X register */
uint8_t Y = 0; /* index Y register */
uint8_t SR = 0x24; /* status register 00100000 */
uint16_t SP = 0x01FD; /* stack pointer to the low byte of the stack */
uint16_t PC = 0xC000; /* program counter */

uint8_t memory[0x10000];

uint16_t pixelMap = 0x0200;

/*
 ============================================================================
 Main
 ============================================================================
 */
uint16_t readTwoBytes() {
	uint16_t result = *(uint16_t *) (memory + PC);
	PC += 2;
	return result;
}
uint8_t readByte() {
	uint8_t result = memory[PC];
	PC++;
	return result;
}

int processIns(uint8_t ins) {

	int done = 0;
	switch (ins) {
	case 0x00:
		brk();
		printf("BREAK: done...\n");
		done = 1;
		break;
	case 0x01:
		oraIndX(readByte());
		break;
	case 0x03:
		printf("done...\n");
		done = 1;
		break;
	case 0x04:
		nopZero(readByte());
		break;
	case 0x05:
		oraZero(readByte());
		break;
	case 0x06:
		aslZero(readByte());
		break;
	case 0x08:
		php();
		break;
	case 0x09:
		ora(readByte());
		break;
	case 0x0A:
		asl();
		break;
	case 0x0C:
		nopAbs(readTwoBytes());
		break;
	case 0x0D:
		oraAbs(readTwoBytes());
		break;
	case 0x0E:
		aslAbs(readTwoBytes());
		break;
	case 0x10:
		bpl(readByte());
		break;
	case 0x11:
		oraIndY(readByte());
		break;
	case 0x14:
		nopZeroX(readByte());
		break;
	case 0x15:
		oraZeroX(readByte());
		break;
	case 0x16:
		aslZeroX(readByte());
		break;
	case 0x18:
		clc();
		break;
	case 0x19:
		oraAbsY(readTwoBytes());
		break;
	case 0x1A:
		nop();
		break;
	case 0x1C:
		nopAbsX(readTwoBytes());
		break;
	case 0x1D:
		oraAbsX(readTwoBytes());
		break;
	case 0x1E:
		aslAbsX(readTwoBytes());
		break;
	case 0x20:
		jsrAbs(readTwoBytes());
		break;
	case 0x21:
		andIndX(readByte());
		break;
	case 0x24:
		bitZero(readByte());
		break;
	case 0x25:
		andZero(readByte());
		break;
	case 0x26:
		rolZero(readByte());
		break;
	case 0x28:
		plp();
		break;
	case 0x29:
		and(readByte());
		break;
	case 0x2A:
		rol();
		break;
	case 0x2C:
		bitAbs(readTwoBytes());
		break;
	case 0x2D:
		andAbs(readTwoBytes());
		break;
	case 0x2E:
		rolAbs(readTwoBytes());
		break;
	case 0x30:
		bmi(readByte());
		break;
	case 0x31:
		andIndY(readByte());
		break;
	case 0x34:
		nopZeroX(readByte());
		break;
	case 0x35:
		andZeroX(readByte());
		break;
	case 0x36:
		rolZeroX(readByte());
		break;
	case 0x38:
		sec();
		break;
	case 0x39:
		andAbsY(readTwoBytes());
		break;
	case 0x3A:
		nop();
		break;
	case 0x3C:
		nopAbsX(readTwoBytes());
		break;
	case 0x3D:
		andAbsX(readTwoBytes());
		break;
	case 0x3E:
		rolAbsX(readTwoBytes());
		break;
	case 0x40:
		rti();
		break;
	case 0x41:
		eorIndX(readByte());
		break;
	case 0x44:
		nopZero(readByte());
		break;
	case 0x45:
		eorZero(readByte());
		break;
	case 0x46:
		lsrZero(readByte());
		break;
	case 0x48:
		pha();
		break;
	case 0x49:
		eor(readByte());
		break;
	case 0x4A:
		lsr();
		break;
	case 0x4C:
		jmpAbs(readTwoBytes());
		break;
	case 0x4D:
		eorAbs(readTwoBytes());
		break;
	case 0x4E:
		lsrAbs(readTwoBytes());
		break;
	case 0x50:
		bvc(readByte());
		break;
	case 0x51:
		eorIndY(readByte());
		break;
	case 0x54:
		nopZeroX(readByte());
		break;
	case 0x55:
		eorZeroX(readByte());
		break;
	case 0x56:
		lsrZeroX(readByte());
		break;
	case 0x58:
		cli();
		break;
	case 0x59:
		eorAbsY(readTwoBytes());
		break;
	case 0x5A:
		nop();
		break;
	case 0x5C:
		nopAbsX(readTwoBytes());
		break;
	case 0x5D:
		eorAbsX(readTwoBytes());
		break;
	case 0x5E:
		lsrAbsX(readTwoBytes());
		break;
	case 0x60:
		rts();
		break;
	case 0x61:
		adcIndX(readByte());
		break;
	case 0x64:
		nopZero(readByte());
		break;
	case 0x65:
		adcZero(readByte());
		break;
	case 0x66:
		rorZero(readByte());
		break;
	case 0x68:
		pla();
		break;
	case 0x69:
		adc(readByte());
		break;
	case 0x6A:
		ror();
		break;
	case 0x6C:
		jmpInd(readTwoBytes());
		break;
	case 0x6D:
		adcAbs(readTwoBytes());
		break;
	case 0x6E:
		rorAbs(readTwoBytes());
		break;
	case 0x70:
		bvs(readByte());
		break;
	case 0x71:
		adcIndY(readByte());
		break;
	case 0x74:
		nopZeroX(readByte());
		break;
	case 0x75:
		adcZeroX(readByte());
		break;
	case 0x76:
		rorZeroX(readByte());
		break;
	case 0x78:
		sei();
		break;
	case 0x79:
		adcAbsY(readTwoBytes());
		break;
	case 0x7A:
		nop();
		break;
	case 0x7C:
		nopAbsX(readTwoBytes());
		break;
	case 0x7D:
		adcAbsX(readTwoBytes());
		break;
	case 0x7E:
		rorAbsX(readTwoBytes());
		break;
	case 0x80:
		nopImm(readByte());
		break;
	case 0x81:
		staIndX(readByte());
		break;
	case 0x82:
		nopImm(readByte());
		break;
	case 0x84:
		styZero(readByte());
		break;
	case 0x85:
		staZero(readByte());
		break;
	case 0x86:
		stxZero(readByte());
		break;
	case 0x88:
		dey();
		break;
	case 0x89:
		nopImm(readByte());
		break;
	case 0x8A:
		txa();
		break;
	case 0x8C:
		styAbs(readTwoBytes());
		break;
	case 0x8D:
		staAbs(readTwoBytes());
		break;
	case 0x8E:
		stxAbs(readTwoBytes());
		break;
	case 0x90:
		bcc(readByte());
		break;
	case 0x91:
		staIndY(readByte());
		break;
	case 0x94:
		styZeroX(readByte());
		break;
	case 0x95:
		staZeroX(readByte());
		break;
	case 0x96:
		stxZeroY(readByte());
		break;
	case 0x98:
		tya();
		break;
	case 0x99:
		staAbsY(readTwoBytes());
		break;
	case 0x9A:
		txs();
		break;
	case 0x9D:
		staAbsX(readTwoBytes());
		break;
	case 0xA0:
		ldy(readByte());
		break;
	case 0xA1:
		ldaIndX(readByte());
		break;
	case 0xA2:
		ldx(readByte());
		break;
	case 0xA4:
		ldyZero(readByte());
		break;
	case 0xA5:
		ldaZero(readByte());
		break;
	case 0xA6:
		ldxZero(readByte());
		break;
	case 0xA8:
		tay();
		break;
	case 0xA9:
		lda(readByte());
		break;
	case 0xAA:
		tax();
		break;
	case 0xAC:
		ldyAbs(readTwoBytes());
		break;
	case 0xAD:
		ldaAbs(readTwoBytes());
		break;
	case 0xAE:
		ldxAbs(readTwoBytes());
		break;
	case 0xB0:
		bcs(readByte());
		break;
	case 0xB1:
		ldaIndY(readByte());
		break;
	case 0xB4:
		ldyZeroX(readByte());
		break;
	case 0xB5:
		ldaZeroX(readByte());
		break;
	case 0xB6:
		ldxZeroY(readByte());
		break;
	case 0xB8:
		clv();
		break;
	case 0xB9:
		ldaAbsY(readTwoBytes());
		break;
	case 0xBA:
		tsx();
		break;
	case 0xBC:
		ldyAbsX(readTwoBytes());
		break;
	case 0xBD:
		ldaAbsX(readTwoBytes());
		break;
	case 0xBE:
		ldxAbsY(readTwoBytes());
		break;
	case 0xC0:
		cmpY(readByte());
		break;
	case 0xC1:
		cmpIndX(readByte());
		break;
	case 0xC3:
		nopImm(readByte());
		break;
	case 0xC4:
		cmpYZero(readByte());
		break;
	case 0xC5:
		cmpZero(readByte());
		break;
	case 0xC6:
		decZero(readByte());
		break;
	case 0xC8:
		iny();
		break;
	case 0xC9:
		cmp(readByte());
		break;
	case 0xCA:
		dex();
		break;
	case 0xCC:
		cmpYAbs(readTwoBytes());
		break;
	case 0xCD:
		cmpAbs(readTwoBytes());
		break;
	case 0xCE:
		decAbs(readTwoBytes());
		break;
	case 0xD0:
		bne(readByte());
		break;
	case 0xD1:
		cmpIndY(readByte());
		break;
	case 0xD4:
		nopZeroX(readByte());
		break;
	case 0xD5:
		cmpZeroX(readByte());
		break;
	case 0xD6:
		decZeroX(readByte());
		break;
	case 0xD8:
		cld();
		break;
	case 0xD9:
		cmpAbsY(readTwoBytes());
		break;
	case 0xDA:
		nop();
		break;
	case 0xDC:
		nopAbsX(readTwoBytes());
		break;
	case 0xDD:
		cmpAbsX(readTwoBytes());
		break;
	case 0xDE:
		decAbsX(readTwoBytes());
		break;
	case 0xE0:
		cmpX(readByte());
		break;
	case 0xE1:
		sbcIndX(readByte());
		break;
	case 0xE3:
		nopImm(readByte());
		break;
	case 0xE4:
		cmpXZero(readByte());
		break;
	case 0xE5:
		sbcZero(readByte());
		break;
	case 0xE6:
		incZero(readByte());
		break;
	case 0xE8:
		inx();
		break;
	case 0xE9:
		sbc(readByte());
		break;
	case 0xEA:
		nop();
		break;
	case 0xEC:
		cmpXAbs(readTwoBytes());
		break;
	case 0xED:
		sbcAbs(readTwoBytes());
		break;
	case 0xEE:
		incAbs(readTwoBytes());
		break;
	case 0xF0:
		beq(readByte());
		break;
	case 0xF1:
		sbcIndY(readByte());
		break;
	case 0xF4:
		nopZeroX(readByte());
		break;
	case 0xF5:
		sbcZeroX(readByte());
		break;
	case 0xF6:
		incZeroX(readByte());
		break;
	case 0xF8:
		sed();
		break;
	case 0xF9:
		sbcAbsY(readTwoBytes());
		break;
	case 0xFA:
		nop();
		break;
	case 0xFC:
		nopAbsX(readTwoBytes());
		break;
	case 0xFD:
		sbcAbsX(readTwoBytes());
		break;
	case 0xFE:
		incAbsX(readTwoBytes());
		break;
	default:
		printf("Could not read instruction [%X]...\n", ins);
		done = 1;
	}
	return done;
}

void run_6502(char* filename) {

	PC = 0x0600;
	SP = 0x01FF;

	srand(time(NULL));
	for (int i = 0; i < 0x10000; i++) {
		memory[i] = 0x00;
	}

	FILE *file = fopen(filename, "rb");
	if (file == NULL) {
		printf("Unable to open file\n");
		return;
	}

	// load memory with file
	int startPC = PC;
	int byte = fgetc(file);
	while (byte != EOF) {
		memory[startPC++] = byte;
		byte = fgetc(file);
	}

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *window = SDL_CreateWindow("6502 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 256, 256,
			SDL_WINDOW_OPENGL);

	if (window == NULL) {
		printf("Error opening window: %s", SDL_GetError());
		return;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	if (renderer == NULL) {
		printf("Error creating renderer: %s", SDL_GetError());
		return;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_Texture *screen_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB332, SDL_TEXTUREACCESS_STREAMING, 256,
			256);

	SDL_Event event;
	int rate = 2;
	int done = 0;
	while (!done) {
		memory[0xFE] = rand() % 256;
		uint8_t ins = readByte();
		done = processIns(ins);

		if (rate-- == 0) {
			drawPixels(screen_texture, renderer);
			rate = 2;
		}

		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_KEYDOWN:
			memory[0xFF] = event.key.keysym.sym;
			break;
		case SDL_QUIT:
			SDL_Quit();
			return;
		}
	}
	drawPixels(screen_texture, renderer);
	printf("done...\n");
	while (1) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_KEYDOWN:
			SDL_Quit();
			return;
		case SDL_QUIT:
			SDL_Quit();
			return;
		}
	}
}

void drawPixels(SDL_Texture *screen_texture, SDL_Renderer *renderer) {

	uint8_t pixel_buffer[256 * 256];
	uint16_t pixelNum = pixelMap;
	for (int y = 0; y < 256; y++) {
		for (int x = 0; x < 256; x++) {
			uint8_t pixel = memory[pixelNum];
			switch (pixel) {
			case 0:
				pixel_buffer[pixelNum] = 0x00;
				break;
			case 1:
				pixel_buffer[pixelNum] = 0xff;
				break;
			case 2:
				pixel_buffer[pixelNum] = 0xe0;
				break;
			case 3:
				pixel_buffer[pixelNum] = 0x1f;
				break;
			case 4:
				pixel_buffer[pixelNum] = 0x82;
				break;
			case 5:
				pixel_buffer[pixelNum] = 0x1c;
				break;
			case 6:
				pixel_buffer[pixelNum] = 0x03;
				break;
			case 7:
				pixel_buffer[pixelNum] = 0xfc;
				break;
			case 8:
				pixel_buffer[pixelNum] = 0xf0;
				break;
			case 9:
				pixel_buffer[pixelNum] = 0x84;
				break;
			case 10:
				pixel_buffer[pixelNum] = 0xe3;
				break;
			case 11:
				pixel_buffer[pixelNum] = 0x49;
				break;
			case 12:
				pixel_buffer[pixelNum] = 0x92;
				break;
			case 13:
				pixel_buffer[pixelNum] = 0xbf;
				break;
			case 14:
				pixel_buffer[pixelNum] = 0x0f;
				break;
			case 15:
				pixel_buffer[pixelNum] = 0xd2;
				break;
			}
			pixelNum++;
		}
	}
	SDL_UpdateTexture(screen_texture, NULL, pixel_buffer, 640 * sizeof(uint8_t));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, screen_texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}
/*
 ============================================================================
 Interrupts
 ============================================================================
 */
void rti() {
	// set status registers
	SP++;
	SR = memory[SP] & ~(BREAK_FLAG);
	SR = SR | 0x20;

	// set program counter
	SP++;
	PC = memory[SP] & 0xFF;
	SP++;
	PC = PC | (memory[SP] << 8);
}
/*
 ============================================================================
 Subroutines
 ============================================================================
 */
void jsrAbs(uint16_t address) {

	PC--;
	uint8_t highPC = (PC >> 8) & 0xFF;
	uint8_t lowPC = PC & 0xFF;

	memory[SP] = highPC;
	SP--;
	memory[SP] = lowPC;
	SP--;

	PC = address;
}
void rts() {
	SP++;
	PC = memory[SP] & 0xFF;
	SP++;
	PC = PC | (memory[SP] << 8);
	PC++;
}
/*
 ============================================================================
 Store Y Register
 ============================================================================
 */
void styZero(uint8_t address) {
	memory[address & 0xFF] = Y;
}
void styZeroX(uint8_t address) {
	memory[(address + X) & 0xFF] = Y;
}
void styAbs(uint16_t address) {
	memory[address] = Y;
}
/*
 ============================================================================
 Store X Register
 ============================================================================
 */
void stxZero(uint8_t address) {
	memory[address & 0xFF] = X;
}
void stxZeroY(uint8_t address) {
	memory[(address + Y) & 0xFF] = X;
}
void stxAbs(uint16_t address) {
	memory[address] = X;
}
/*
 ============================================================================
 Store Accumulator
 ============================================================================
 */
void staZero(uint8_t address) {
	memory[address & 0xFF] = A;
}
void staZeroX(uint8_t address) {
	memory[(address + X) & 0xFF] = A;
}
void staAbs(uint16_t address) {
	memory[address] = A;
}
void staAbsX(uint16_t address) {
	memory[(address + X) & 0xFFFF] = A;
}
void staAbsY(uint16_t address) {
	memory[(address + Y) & 0xFFFF] = A;
}
void staIndX(uint8_t address) {
	uint16_t newAddress = indXAddress(address);
	memory[newAddress] = A;
}
void staIndY(uint8_t address) {
	uint16_t newAddress = indYAddress(address);
	memory[newAddress] = A;
}
/*
 ============================================================================
 Subtract with Carry
 ============================================================================
 */
void setSbcFlags(uint8_t A, uint8_t B, uint8_t result) {
	if (result == 0) SR = SR | ZERO_FLAG;
	else SR = SR & (~ZERO_FLAG);

	if (result > A) SR = SR & ~CARRY_FLAG;
	else SR = SR | CARRY_FLAG;

	if (result & 0x80) SR = SR | SIGN_FLAG;
	else SR = SR & (~SIGN_FLAG);

	setSbcOverflow(A, B, result);
}

/* one byte address for immediate mode */
void sbc(uint8_t address) {
	uint8_t oldA = A;
	A = A - address - (1 - (SR & CARRY_FLAG));
	setSbcFlags(oldA, address, A);
}
/* one byte address for zero page mode */
void sbcZero(uint8_t address) {
	uint8_t oldA = A;
	A = A - memory[address & 0xFF] - (1 - (SR & CARRY_FLAG));
	setSbcFlags(oldA, memory[address & 0xFF], A);
}
/* one byte address zero page + X with zero page wrap around */
void sbcZeroX(uint8_t address) {
	uint8_t oldA = A;
	A = A - memory[(address + X) & 0xFF] - (1 - (SR & CARRY_FLAG));
	setSbcFlags(oldA, memory[(address + X) & 0xFF], A);
}
/* two byte absolute address */
void sbcAbs(uint16_t address) {
	uint8_t oldA = A;
	A = A - memory[address] - (1 - (SR & CARRY_FLAG));
	setSbcFlags(oldA, memory[address], A);
}
/* two byte absolute address + X */
void sbcAbsX(uint16_t address) {
	uint8_t oldA = A;
	A = A - memory[(address + X) & 0xFFFF] - (1 - (SR & CARRY_FLAG));
	setSbcFlags(oldA, memory[(address + X) & 0xFFFF], A);
}
/* two byte absolute address + Y */
void sbcAbsY(uint16_t address) {
	uint8_t oldA = A;
	A = A - memory[(address + Y) & 0xFFFF] - (1 - (SR & CARRY_FLAG));
	setSbcFlags(oldA, memory[(address + Y) & 0xFFFF], A);
}
/* one byte indirect address + X with zero page wrap around */
void sbcIndX(uint8_t address) {
	uint16_t newAddress = indXAddress(address);
	uint8_t oldA = A;
	A = A - memory[newAddress] - (1 - (SR & CARRY_FLAG));
	setSbcFlags(oldA, memory[newAddress], A);
}
/* one byte indirect address + Y */
void sbcIndY(uint8_t address) {
	uint16_t newAddress = indYAddress(address);
	uint8_t oldA = A;
	A = A - memory[newAddress] - (1 - (SR & CARRY_FLAG));
	setSbcFlags(oldA, memory[newAddress], A);
}
/*
 ============================================================================
 Rotate right
 ============================================================================
 */
void ror() {
	uint8_t oldA = A;
	A = A >> 1;
	A = A | ((SR & CARRY_FLAG) << 7);
	SR = SR | (oldA & CARRY_FLAG);
	setZeroSignFlags(A);
}
void rorZero(uint8_t address) {
	uint8_t oldMem = memory[address & 0xFF];
	memory[address & 0xFF] = memory[address & 0xFF] >> 1;
	memory[address & 0xFF] = memory[address & 0xFF] | ((SR & CARRY_FLAG) << 7);
	SR = SR | (oldMem & CARRY_FLAG);
	setZeroSignFlags(memory[address & 0xFF]);
}
void rorZeroX(uint8_t address) {
	uint8_t oldMem = memory[(address + X) & 0xFF];
	memory[(address + X) & 0xFF] = memory[(address + X) & 0xFF] >> 1;
	memory[(address + X) & 0xFF] = memory[(address + X) & 0xFF] | ((SR & CARRY_FLAG) << 7);
	SR = SR | (oldMem & CARRY_FLAG);
	setZeroSignFlags(memory[(address + X) & 0xFF]);
}
void rorAbs(uint16_t address) {
	uint8_t oldMem = memory[address];
	memory[address] = memory[address] >> 1;
	memory[address] = memory[address] | ((SR & CARRY_FLAG) << 7);
	SR = SR | (oldMem & CARRY_FLAG);
	setZeroSignFlags(memory[address]);
}
void rorAbsX(uint16_t address) {
	uint8_t oldMem = memory[(address + X) & 0xFFFF];
	memory[(address + X) & 0xFFFF] = memory[(address + X) & 0xFFFF] >> 1;
	memory[(address + X) & 0xFFFF] = memory[(address + X) & 0xFFFF] | ((SR & CARRY_FLAG) << 7);
	SR = SR | (oldMem & CARRY_FLAG);
	setZeroSignFlags(memory[(address + X) & 0xFFFF]);
}
/*
 ============================================================================
 Rotate left
 ============================================================================
 */
void rol() {
	uint8_t oldA = A;
	A = A << 1;
	A = A | (SR & CARRY_FLAG);
	SR = SR | ((oldA & SIGN_FLAG) >> 7);
	setZeroSignFlags(A);
}
void rolZero(uint8_t address) {
	uint8_t oldMem = memory[address & 0xFF];
	memory[address & 0xFF] = memory[address & 0xFF] << 1;
	memory[address & 0xFF] = memory[address & 0xFF] | (SR & CARRY_FLAG);
	SR = SR | ((oldMem & SIGN_FLAG) >> 7);
	setZeroSignFlags(memory[address & 0xFF]);
}
void rolZeroX(uint8_t address) {
	uint8_t oldMem = memory[(address + X) & 0xFF];
	memory[(address + X) & 0xFF] = memory[(address + X) & 0xFF] << 1;
	memory[(address + X) & 0xFF] = memory[(address + X) & 0xFF] | (SR & CARRY_FLAG);
	SR = SR | ((oldMem & SIGN_FLAG) >> 7);
	setZeroSignFlags(memory[(address + X) & 0xFF]);
}
void rolAbs(uint16_t address) {
	uint8_t oldMem = memory[address];
	memory[address] = memory[address] << 1;
	memory[address] = memory[address] | (SR & CARRY_FLAG);
	SR = SR | ((oldMem & SIGN_FLAG) >> 7);
	setZeroSignFlags(memory[address]);
}
void rolAbsX(uint16_t address) {
	uint8_t oldMem = memory[(address + X) & 0xFFFF];
	memory[(address + X) & 0xFFFF] = memory[(address + X) & 0xFFFF] << 1;
	memory[(address + X) & 0xFFFF] = memory[(address + X) & 0xFFFF] | (SR & CARRY_FLAG);
	SR = SR | ((oldMem & SIGN_FLAG) >> 7);
	setZeroSignFlags(memory[(address + X) & 0xFFFF]);
}
/*
 ============================================================================
 Logical Or
 ============================================================================
 */
void ora(uint8_t address) {
	A = A | address;
	setZeroSignFlags(A);
}
void oraZero(uint8_t address) {
	A = A | memory[address & 0xFF];
	setZeroSignFlags(A);
}
void oraZeroX(uint8_t address) {
	A = A | memory[(address + X) & 0xFF];
	setZeroSignFlags(A);
}
void oraAbs(uint16_t address) {
	A = A | memory[address];
	setZeroSignFlags(A);
}
void oraAbsX(uint16_t address) {
	A = A | memory[(address + X) & 0xFFFF];
	setZeroSignFlags(A);
}
void oraAbsY(uint16_t address) {
	A = A | memory[(address + Y) & 0xFFFF];
	setZeroSignFlags(A);
}
void oraIndX(uint8_t address) {
	uint16_t newAddress = indXAddress(address);
	A = A | memory[newAddress];
	setZeroSignFlags(A);
}
void oraIndY(uint8_t address) {
	uint16_t newAddress = indYAddress(address);
	A = A | memory[newAddress];
	setZeroSignFlags(A);
}
/*
 ============================================================================
 Logical shift right
 ============================================================================
 */
void lsr() {
	// set the carry flag to whatever was in bit 7 of A
	if (A & CARRY_FLAG) SR = SR | CARRY_FLAG;
	else SR = SR & ~CARRY_FLAG;
	A = A >> 1;
	setZeroSignFlags(A);
}
void lsrZero(uint8_t address) {
	uint8_t value = memory[address & 0xFF];
	if (value & CARRY_FLAG) SR = SR | CARRY_FLAG;
	else SR = SR & ~CARRY_FLAG;
	memory[address & 0xFF] = value >> 1;
	setZeroSignFlags(memory[address & 0xFF]);
}
void lsrZeroX(uint8_t address) {
	uint8_t value = memory[(address + X) & 0xFF];
	if (value & CARRY_FLAG) SR = SR | CARRY_FLAG;
	else SR = SR & ~CARRY_FLAG;

	memory[(address + X) & 0xFF] = value >> 1;
	setZeroSignFlags(memory[(address + X) & 0xFF]);
}
void lsrAbs(uint16_t address) {
	uint8_t value = memory[address];
	if (value & CARRY_FLAG) SR = SR | CARRY_FLAG;
	else SR = SR & ~CARRY_FLAG;

	memory[address] = value >> 1;
	setZeroSignFlags(memory[address]);
}
void lsrAbsX(uint16_t address) {
	uint8_t value = memory[(address + X) & 0xFFFF];
	if (value & CARRY_FLAG) SR = SR | CARRY_FLAG;
	else SR = SR & ~CARRY_FLAG;

	memory[(address + X) & 0xFFFF] = value >> 1;
	setZeroSignFlags(memory[(address + X) & 0xFFFF]);
}
/*
 ============================================================================
 Load Y Register
 ============================================================================
 */
void ldy(uint8_t address) {
	Y = address;
	setZeroSignFlags(Y);
}
void ldyZero(uint8_t address) {
	Y = memory[address & 0xFF];
	setZeroSignFlags(Y);
}
void ldyZeroX(uint8_t address) {
	Y = memory[(address + X) & 0xFF];
	setZeroSignFlags(Y);
}
void ldyAbs(uint16_t address) {
	Y = memory[address];
	setZeroSignFlags(Y);
}
void ldyAbsX(uint16_t address) {
	Y = memory[(address + X) & 0xFFFF];
	setZeroSignFlags(Y);
}
/*
 ============================================================================
 Load X Register
 ============================================================================
 */
void ldx(uint8_t address) {
	X = address;
	setZeroSignFlags(X);
}
void ldxZero(uint8_t address) {
	X = memory[address & 0xFF];
	setZeroSignFlags(X);
}
void ldxZeroY(uint8_t address) {
	X = memory[(address + Y) & 0xFF];
	setZeroSignFlags(X);
}
void ldxAbs(uint16_t address) {
	X = memory[address];
	setZeroSignFlags(X);
}
void ldxAbsY(uint16_t address) {
	X = memory[(address + Y) & 0xFFFF];
	setZeroSignFlags(X);
}
/*
 ============================================================================
 Load Accumulator
 ============================================================================
 */
void lda(uint8_t address) {
	A = address;
	setZeroSignFlags(A);
}
void ldaZero(uint8_t address) {
	A = memory[address & 0xFF];
	setZeroSignFlags(A);
}
void ldaZeroX(uint8_t address) {
	A = memory[(address + X) & 0xFF];
	setZeroSignFlags(A);
}
void ldaAbs(uint16_t address) {
	A = memory[address];
	setZeroSignFlags(A);
}
void ldaAbsX(uint16_t address) {
	A = memory[(address + X) & 0xFFFF];
	setZeroSignFlags(A);
}
void ldaAbsY(uint16_t address) {
	A = memory[(address + Y) & 0xFFFF];
	setZeroSignFlags(A);
}
void ldaIndX(uint8_t address) {
	uint16_t newAddress = indXAddress(address);
	A = memory[newAddress];
	setZeroSignFlags(A);
}
void ldaIndY(uint8_t address) {
	uint16_t newAddress = indYAddress(address);
	A = memory[newAddress];
	setZeroSignFlags(A);
}
/*
 ============================================================================
 Jump
 ============================================================================
 */
void jmpAbs(uint16_t address) {
	PC = address;
}
void jmpInd(uint16_t address) {
	PC = memory[address];

	// mimic jmp bug in the CPU
	if ((address & 0xFF) == 0xFF) PC = PC | (memory[address & 0xFF00] << 8);
	else PC = PC | (memory[address + 1] << 8);
}
/*
 ============================================================================
 Increment memory
 ============================================================================
 */
void incZero(uint8_t address) {
	memory[address & 0xFF]++;
	setZeroSignFlags(memory[address & 0xFF]);
}
void incZeroX(uint8_t address) {
	memory[(address + X) & 0xFF]++;
	setZeroSignFlags(memory[(address + X) & 0xFF]);
}
void incAbs(uint16_t address) {
	memory[address]++;
	setZeroSignFlags(memory[address]);
}
void incAbsX(uint16_t address) {
	memory[(address + X) & 0xFFFF]++;
	setZeroSignFlags(memory[(address + X) & 0xFFFF]);
}
/*
 ============================================================================
 Exclusive Or
 ============================================================================
 */
void eor(uint8_t address) {
	A = A ^ address;
	setZeroSignFlags(A);
}
void eorZero(uint8_t address) {
	A = A ^ memory[address & 0xFF];
	setZeroSignFlags(A);
}
void eorZeroX(uint8_t address) {
	A = A ^ memory[(address + X) & 0xFF];
	setZeroSignFlags(A);
}
void eorAbs(uint16_t address) {
	A = A ^ memory[address];
	setZeroSignFlags(A);
}
void eorAbsX(uint16_t address) {
	A = A ^ memory[(address + X) & 0xFFFF];
	setZeroSignFlags(A);
}
void eorAbsY(uint16_t address) {
	A = A ^ memory[(address + Y) & 0xFFFF];
	setZeroSignFlags(A);
}
void eorIndX(uint8_t address) {
	uint16_t newAddress = indXAddress(address);
	A = A ^ memory[newAddress];
	setZeroSignFlags(A);
}
void eorIndY(uint8_t address) {
	uint16_t newAddress = indYAddress(address);
	A = A ^ memory[newAddress];
	setZeroSignFlags(A);
}
/*
 ============================================================================
 Decrement memory
 ============================================================================
 */
void decZero(uint8_t address) {
	memory[address & 0xFF]--;
	setZeroSignFlags(memory[address & 0xFF]);
}
void decZeroX(uint8_t address) {
	memory[(address + X) & 0xFF]--;
	setZeroSignFlags(memory[(address + X) & 0xFF]);
}
void decAbs(uint16_t address) {
	memory[address]--;
	setZeroSignFlags(memory[address]);
}
void decAbsX(uint16_t address) {
	memory[(address + X) & 0xFFFF]--;
	setZeroSignFlags(memory[(address + X) & 0xFFFF]);
}
/*
 ============================================================================
 Compare Y
 ============================================================================
 */
void cmpY(uint8_t address) {
	compare(Y, address);
}
void cmpYZero(uint8_t address) {
	compare(Y, memory[address & 0xFF]);
}
void cmpYAbs(uint16_t address) {
	compare(Y, memory[address]);
}
/*
 ============================================================================
 Compare X
 ============================================================================
 */
void cmpX(uint8_t address) {
	compare(X, address);
}
void cmpXZero(uint8_t address) {
	compare(X, memory[address & 0xFF]);
}
void cmpXAbs(uint16_t address) {
	compare(X, memory[address]);
}

/*
 ============================================================================
 Compare
 ============================================================================
 */

void compare(uint8_t A, uint8_t B) {
	if (A >= B) SR = SR | CARRY_FLAG;
	else SR = SR & (~CARRY_FLAG);

	if (A == B) SR = SR | ZERO_FLAG;
	else SR = SR & (~ZERO_FLAG);

	if ((A - B) & 0x80) SR = SR | SIGN_FLAG;
	else SR = SR & (~SIGN_FLAG);
}
void cmp(uint8_t address) {
	compare(A, address);
}
void cmpZero(uint8_t address) {
	compare(A, memory[address & 0xFF]);
}
void cmpZeroX(uint8_t address) {
	compare(A, memory[(address + X) & 0xFF]);
}
void cmpAbs(uint16_t address) {
	compare(A, memory[address]);
}
void cmpAbsX(uint16_t address) {
	compare(A, memory[(address + X) & 0xFFFF]);
}
void cmpAbsY(uint16_t address) {
	compare(A, memory[(address + Y) & 0xFFFF]);
}
void cmpIndX(uint8_t address) {
	uint16_t newAddress = indXAddress(address);
	compare(A, memory[newAddress]);
}
void cmpIndY(uint8_t address) {
	uint16_t newAddress = indYAddress(address);
	compare(A, memory[newAddress]);
}
/*
 ============================================================================
 Bit test
 ============================================================================
 */
void bitZero(uint8_t address) {
	if ((A & memory[address & 0xFF]) == 0) SR = SR | ZERO_FLAG;
	else SR = SR & ~ZERO_FLAG;

	if (memory[address & 0xFF] & OVERFLOW_FLAG) SR = SR | OVERFLOW_FLAG;
	else SR = SR & ~OVERFLOW_FLAG;

	if (memory[address & 0xFF] & SIGN_FLAG) SR = SR | SIGN_FLAG;
	else SR = SR & ~SIGN_FLAG;
}
void bitAbs(uint16_t address) {
	if ((A & memory[address]) == 0) SR = SR | ZERO_FLAG;
	else SR = SR & ~ZERO_FLAG;

	if (memory[address] & OVERFLOW_FLAG) SR = SR | OVERFLOW_FLAG;
	else SR = SR & ~OVERFLOW_FLAG;

	if (memory[address] & SIGN_FLAG) SR = SR | SIGN_FLAG;
	else SR = SR & ~SIGN_FLAG;
}
/*
 ============================================================================
 Arithmetic shift left
 ============================================================================
 */
void asl() {
	// set the carry flag to whatever was in bit 7 of A
	if ((A >> 7) & CARRY_FLAG) SR = SR | CARRY_FLAG;
	else SR = SR & ~CARRY_FLAG;

	A = A << 1;
	setZeroSignFlags(A);
}
void aslZero(uint8_t address) {
	uint8_t value = memory[address & 0xFF];
	if ((value >> 7) & CARRY_FLAG) SR = SR | CARRY_FLAG;
	else SR = SR & ~CARRY_FLAG;

	memory[address & 0xFF] = value << 1;
	setZeroSignFlags(memory[address & 0xFF]);
}
void aslZeroX(uint8_t address) {
	uint8_t value = memory[(address + X) & 0xFF];
	if ((value >> 7) & CARRY_FLAG) SR = SR | CARRY_FLAG;
	else SR = SR & ~CARRY_FLAG;

	memory[(address + X) & 0xFF] = value << 1;
	setZeroSignFlags(memory[(address + X) & 0xFF]);
}
void aslAbs(uint16_t address) {
	uint8_t value = memory[address];
	if ((value >> 7) & CARRY_FLAG) SR = SR | CARRY_FLAG;
	else SR = SR & ~CARRY_FLAG;

	memory[address] = value << 1;
	setZeroSignFlags(memory[address]);
}
void aslAbsX(uint16_t address) {
	uint8_t value = memory[(address + X) & 0xFFFF];
	if ((value >> 7) & CARRY_FLAG) SR = SR | CARRY_FLAG;
	else SR = SR & ~CARRY_FLAG;

	memory[(address + X) & 0xFFFF] = value << 1;
	setZeroSignFlags(memory[(address + X) & 0xFFFF]);
}
/*
 ============================================================================
 Logical And
 ============================================================================
 */
void and(uint8_t address) {
	A = A & address;
	setZeroSignFlags(A);
}
void andZero(uint8_t address) {
	A = A & memory[address & 0xFF];
	setZeroSignFlags(A);
}
void andZeroX(uint8_t address) {
	A = A & memory[(address + X) & 0xFF];
	setZeroSignFlags(A);
}
void andAbs(uint16_t address) {
	A = A & memory[address];
	setZeroSignFlags(A);
}
void andAbsX(uint16_t address) {
	A = A & memory[(address + X) & 0xFFFF];
	setZeroSignFlags(A);
}
void andAbsY(uint16_t address) {
	A = A & memory[(address + Y) & 0xFFFF];
	setZeroSignFlags(A);
}
void andIndX(uint8_t address) {
	uint16_t newAddress = indXAddress(address);
	A = A & memory[newAddress];
	setZeroSignFlags(A);
}
void andIndY(uint8_t address) {
	uint16_t newAddress = indYAddress(address);
	A = A & memory[newAddress];
	setZeroSignFlags(A);
}

/*
 ============================================================================
 Add with Carry
 ============================================================================
 */
void setAdcFlags(uint8_t A, uint8_t B, uint8_t result) {
	if (result == 0) SR = SR | ZERO_FLAG;
	else SR = SR & ~ZERO_FLAG;

	if (result < A) SR = SR | CARRY_FLAG;
	else SR = SR & ~CARRY_FLAG;

	if (result & 0x80) SR = SR | SIGN_FLAG;
	else SR = SR & ~SIGN_FLAG;

	setOverflow(A, B, result);
}

/* one byte address for immediate mode */
void adc(uint8_t address) {
	uint8_t oldA = A;
	A = A + address + (SR & CARRY_FLAG);
	setAdcFlags(oldA, address, A);
}
/* one byte address for zero page mode */
void adcZero(uint8_t address) {
	uint8_t oldA = A;
	A = A + memory[address & 0xFF] + (SR & CARRY_FLAG);
	setAdcFlags(oldA, memory[address & 0xFF], A);
}
/* one byte address zero page + X with zero page wrap around */
void adcZeroX(uint8_t address) {
	uint8_t oldA = A;
	A = A + memory[(address + X) & 0xFF] + (SR & CARRY_FLAG);
	setAdcFlags(oldA, memory[(address + X) & 0xFF], A);
}
/* two byte absolute address */
void adcAbs(uint16_t address) {
	uint8_t oldA = A;
	A = A + memory[address] + (SR & CARRY_FLAG);
	setAdcFlags(oldA, memory[address], A);
}
/* two byte absolute address + X */
void adcAbsX(uint16_t address) {
	uint8_t oldA = A;
	A = A + memory[(address + X) & 0xFFFF] + (SR & CARRY_FLAG);
	setAdcFlags(oldA, memory[(address + X) & 0xFFFF], A);
}
/* two byte absolute address + Y */
void adcAbsY(uint16_t address) {
	uint8_t oldA = A;
	A = A + memory[(address + Y) & 0xFFFF] + (SR & CARRY_FLAG);
	setAdcFlags(oldA, memory[(address + Y) & 0xFFFF], A);
}
/* one byte indirect address + X with zero page wrap around */
void adcIndX(uint8_t address) {
	uint16_t newAddress = indXAddress(address);
	uint8_t oldA = A;
	A = A + memory[newAddress] + (SR & CARRY_FLAG);
	setAdcFlags(oldA, memory[newAddress], A);
}
/* one byte indirect address + Y */
void adcIndY(uint8_t address) {
	uint16_t newAddress = indYAddress(address);
	uint8_t oldA = A;
	A = A + memory[newAddress] + (SR & CARRY_FLAG);
	setAdcFlags(oldA, memory[newAddress], A);
}
/*
 ============================================================================
 No Op
 ============================================================================
 */
void nop() {
}
void nopImm(uint8_t address) {
}
void nopZero(uint8_t address) {
}
void nopZeroX(uint8_t address) {
}
void nopAbs(uint16_t address) {
}
void nopAbsX(uint16_t address) {
}
void nopAbsY(uint16_t address) {
}
void nopIndX(uint8_t address) {
}
void nopIndY(uint8_t address) {
}

/*
 ============================================================================
 Other implied
 ============================================================================
 */
void pha() {
	memory[SP--] = A;
}
void php() {
	memory[SP--] = SR | BREAK_FLAG;
}
void pla() {
	SP++;
	A = memory[SP];
	setZeroSignFlags(A);
}
void plp() {
	SP++;
	SR = memory[SP] & ~(BREAK_FLAG);
	SR = SR | 0x20;
}
void tax() {
	X = A;
	setZeroSignFlags(X);
}
void tay() {
	Y = A;
	setZeroSignFlags(Y);
}
void tsx() {
	X = SP & 0xFF;
	setZeroSignFlags(X);
}
void txa() {
	A = X;
	setZeroSignFlags(A);
}
void txs() {
	SP = (X & 0x1FF) | 0x100;
}
void tya() {
	A = Y;
	setZeroSignFlags(A);
}
void brk() {
	SR = SR | BREAK_FLAG;
}
/*
 ============================================================================
 Inc/Dec X, Y
 ============================================================================
 */
void dex() {
	X--;
	setZeroSignFlags(X);
}
void dey() {
	Y--;
	setZeroSignFlags(Y);
}
void inx() {
	X++;
	setZeroSignFlags(X);
}
void iny() {
	Y++;
	setZeroSignFlags(Y);
}
/*
 ============================================================================
 Set flags
 ============================================================================
 */
void sec() {
	SR = SR | CARRY_FLAG;
}
void sed() {
	SR = SR | DECIMAL_FLAG;
}
void sei() {
	SR = SR | INTERRUPT_FLAG;
}
/*
 ============================================================================
 Clear flags
 ============================================================================
 */
void clc() {
	SR = SR & ~CARRY_FLAG;
}
void cld() {
	SR = SR & ~DECIMAL_FLAG;
}
void cli() {
	SR = SR & ~INTERRUPT_FLAG;
}
void clv() {
	SR = SR & ~OVERFLOW_FLAG;
}
/*
 ============================================================================
 Branches
 ============================================================================
 */
void bcc(int8_t displacement) {
	if ((SR & CARRY_FLAG) == 0) PC += displacement;
}
void bcs(int8_t displacement) {
	if (SR & CARRY_FLAG) PC += displacement;
}
void beq(int8_t displacement) {
	if (SR & ZERO_FLAG) PC += displacement;
}
void bmi(int8_t displacement) {
	if (SR & SIGN_FLAG) PC += displacement;
}
void bne(int8_t displacement) {
	if ((SR & ZERO_FLAG) == 0) PC += displacement;
}
void bpl(int8_t displacement) {
	if ((SR & SIGN_FLAG) == 0) PC += displacement;
}
void bvc(int8_t displacement) {
	if ((SR & OVERFLOW_FLAG) == 0) PC += displacement;
}
void bvs(int8_t displacement) {
	if (SR & OVERFLOW_FLAG) PC += displacement;
}
/*
 ============================================================================
 Helpers
 ============================================================================
 */
void dump() {
	printf("A:%.2X ", A);
	printf("X:%.2X ", X);
	printf("Y:%.2X ", Y);
	printf("P:%.2X ", SR);
	printf("SP:%.2X\n", SP & 0xFF);
}
void setZeroSignFlags(uint8_t reg) {
	if (reg == 0) SR = SR | ZERO_FLAG;
	else SR = SR & (~ZERO_FLAG);

	if (reg & 0x80) SR = SR | SIGN_FLAG;
	else SR = SR & (~SIGN_FLAG);
}
void setSbcOverflow(uint8_t one, uint8_t two, uint8_t result) {
	SR = SR & ~OVERFLOW_FLAG;

	if ((one & 0x80) != (two & 0x80) && (result & 0x80) == (two & 0x80)) SR = SR | OVERFLOW_FLAG;
}

void setOverflow(uint8_t one, uint8_t two, uint8_t result) {
	SR = SR & ~OVERFLOW_FLAG;

	if ((one & 0x80) == (two & 0x80) && (result & 0x80) != (one & 0x80)) SR = SR | OVERFLOW_FLAG;
}
uint16_t indXAddress(uint8_t address) {
	uint16_t result = memory[(address + X) & 0xFF];
	result = result | (memory[((address + X + 1) & 0xFF)] << 8);
	return result;
}
uint16_t indYAddress(uint8_t address) {
	uint16_t result = memory[address & 0xFF];
	result = result | (memory[(address + 1) & 0xFF] << 8);
	result += Y;
	return result;
}

