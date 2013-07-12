/*
 * cpu.c
 *
 *  Created on: Jun 17, 2013
 *      Author: n0210015
 */

#include "cpu.h"

uint8_t A = 0; /* accumulator register */
uint8_t X = 0; /* index X register */
uint8_t Y = 0; /* index Y register */
uint8_t SR = 0x24; /* status register 00100000 */
uint16_t SP = 0x01FF; /* stack pointer to the low byte of the stack */
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
	printf("%x ", result);
	PC += 2;
	return result;
}
uint8_t readByte() {
	uint8_t result = memory[PC];
	printf("%x ", result);
	PC++;
	return result;
}

int processIns(uint8_t ins) {

	int done = 0;
	switch (ins) {
	case 0x0:
		brk();
		printf("BREAK: done...\n");
		done = 1;
		break;
	case 0x1:
		oraIndX(readByte());
		break;
	case 0x03:
		printf("done...\n");
		done = 1;
		break;
	case 0x5:
		oraZero(readByte());
		break;
	case 0x6:
		aslZero(readByte());
		break;
	case 0x8:
		php();
		break;
	case 0x9:
		ora(readByte());
		break;
	case 0xA:
		asl();
		break;
	case 0xD:
		oraAbs(readTwoBytes());
		break;
	case 0xE:
		aslAbs(readTwoBytes());
		break;
	case 0x10:
		bpl(readByte());
		break;
	case 0x11:
		oraIndY(readByte());
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
	case 0x3D:
		andAbsY(readTwoBytes());
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
	case 0x7D:
		adcAbsX(readTwoBytes());
		break;
	case 0x7E:
		rorAbsX(readTwoBytes());
		break;
	case 0x81:
		staIndX(readByte());
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

void run(char* filename) {

	srand(time(NULL));
	for (int i = 0; i < 0x10000; i++) {
		memory[i] = 0x00;
	}

	FILE *file = fopen(filename, "rb");
	if (file == NULL) {
		printf("Unable to open file\n");
		return;
	}

	fseek(file, 16, SEEK_SET);

	// load memory with file
	int startPC = PC;
	for (int i = 0; i < 16384; i++) {
		memory[startPC++] = fgetc(file);
	}

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Surface* screen = SDL_SetVideoMode(256, 256, 8, SDL_SWSURFACE);
	SDL_WM_SetCaption("6502 Emulator", NULL);


	SDL_Event event;
	int rate = 200;
	int done = 0;
	while (!done) {

		printf("PC: %x\t\t", PC);
		uint8_t ins = readByte();

		done = processIns(ins);
		dump();
		if (rate-- == 0) {
			drawRects(screen, screen->w / 32);
			rate = 200;
		}


		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			SDL_Quit();
			return;
		}
	}
	drawRects(screen, screen->w / 32);
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

void drawRects(SDL_Surface* screen, int size) {

	SDL_Rect rect;
	uint8_t pixel;
	uint8_t color;

	for (int y = 0; y < screen->w; y += size) {
		for (int x = 0; x < screen->h; x += size) {
			rect.x = x;
			rect.y = y;
			rect.w = size;
			rect.h = size;
			pixel = memory[pixelMap++];
			color = 0x00;
			switch (pixel & 0xF) {
			case 0:
				color = 0x00;
				break;
			case 1:
				color = 0xff;
				break;
			case 2:
				color = 0xe0;
				break;
			case 3:
				color = 0x1f;
				break;
			case 4:
				color = 0x82;
				break;
			case 5:
				color = 0x1c;
				break;
			case 6:
				color = 0x03;
				break;
			case 7:
				color = 0xfc;
				break;
			case 8:
				color = 0xf0;
				break;
			case 9:
				color = 0x84;
				break;
			case 10:
				color = 0xe3;
				break;
			case 11:
				color = 0x49;
				break;
			case 12:
				color = 0x92;
				break;
			case 13:
				color = 0xbf;
				break;
			case 14:
				color = 0x0f;
				break;
			case 15:
				color = 0xd2;
				break;
			}
			SDL_FillRect(screen, &rect, color);
		}
	}
	pixelMap = PIXEL_ADDRESS;
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

void drawPixel(SDL_Surface* screen) {

	uint8_t *pixels = (uint8_t *) screen->pixels;
	uint16_t pixelNum = pixelMap;
	for (int y = 0; y < screen->w; y++) {
		for (int x = 0; x < screen->h; x++) {
			uint8_t pixel = memory[pixelNum++];
			switch (pixel) {
			case 0:
				pixels[(y * screen->w) + x] = 0x00;
				break;
			case 1:
				pixels[(y * screen->w) + x] = 0xff;
				break;
			case 2:
				pixels[(y * screen->w) + x] = 0xe0;
				break;
			case 3:
				pixels[(y * screen->w) + x] = 0x1f;
				break;
			case 4:
				pixels[(y * screen->w) + x] = 0x82;
				break;
			case 5:
				pixels[(y * screen->w) + x] = 0x1c;
				break;
			case 6:
				pixels[(y * screen->w) + x] = 0x03;
				break;
			case 7:
				pixels[(y * screen->w) + x] = 0xfc;
				break;
			case 8:
				pixels[(y * screen->w) + x] = 0xf0;
				break;
			case 9:
				pixels[(y * screen->w) + x] = 0x84;
				break;
			case 10:
				pixels[(y * screen->w) + x] = 0xe3;
				break;
			case 11:
				pixels[(y * screen->w) + x] = 0x49;
				break;
			case 12:
				pixels[(y * screen->w) + x] = 0x92;
				break;
			case 13:
				pixels[(y * screen->w) + x] = 0xbf;
				break;
			case 14:
				pixels[(y * screen->w) + x] = 0x0f;
				break;
			case 15:
				pixels[(y * screen->w) + x] = 0xd2;
				break;
			}
		}
	}
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}
/*
 ============================================================================
 Interrupts
 ============================================================================
 */
void rti() {
	SR = memory[++SP]; // set SR to previous stack value
	SP += 2;
	PC = *(uint16_t *) (memory + SP); // set PC to previous stack value
}
/*
 ============================================================================
 Subroutines
 ============================================================================
 */
void jsrAbs(uint16_t address) {
	*(uint16_t *) (memory + SP) = PC; // store PC on the stack
	SP -= 2; // next free spot on the stack is 2 bytes down
	PC = address; // set PC to current address
}
void rts() {
	SP += 2;
	PC = *(uint16_t *) (memory + SP); // set PC to previous stack value
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
	memory[address + X] = A;
}
void staAbsY(uint16_t address) {
	memory[address + Y] = A;
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
	if (result == 0)
		SR = SR | ZERO_FLAG;
	else
		SR = SR & (~ZERO_FLAG);

	if (result > A)
		SR = SR & ~CARRY_FLAG;
	else
		SR = SR | CARRY_FLAG;

	if (result & 0x80)
		SR = SR | SIGN_FLAG;
	else
		SR = SR & (~SIGN_FLAG);

	setOverflow(A, B, result);
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
	A = A - memory[address + X] - (1 - (SR & CARRY_FLAG));
	setSbcFlags(oldA, memory[address + X], A);
}
/* two byte absolute address + Y */
void sbcAbsY(uint16_t address) {
	uint8_t oldA = A;
	A = A + memory[address + Y] - (1 - (SR & CARRY_FLAG));
	setSbcFlags(oldA, memory[address + Y], A);
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
	memory[(address + X) & 0xFF] = memory[(address + X) & 0xFF]
			| ((SR & CARRY_FLAG) << 7);
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
	uint8_t oldMem = memory[address + X];
	memory[address + X] = memory[address + X] >> 1;
	memory[address + X] = memory[address + X] | ((SR & CARRY_FLAG) << 7);
	SR = SR | (oldMem & CARRY_FLAG);
	setZeroSignFlags(memory[address + X]);
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
	memory[(address + X) & 0xFF] = memory[(address + X) & 0xFF]
			| (SR & CARRY_FLAG);
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
	uint8_t oldMem = memory[address + X];
	memory[address + X] = memory[address + X] << 1;
	memory[address + X] = memory[address + X] | (SR & CARRY_FLAG);
	SR = SR | ((oldMem & SIGN_FLAG) >> 7);
	setZeroSignFlags(memory[address + X]);
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
	A = A | memory[address + X];
	setZeroSignFlags(A);
}
void oraAbsY(uint16_t address) {
	A = A | memory[address + Y];
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
 Arithmetic shift left
 ============================================================================
 */
void lsr() {
	// set the carry flag to whatever was in bit 7 of A
	SR = SR | (A & CARRY_FLAG);
	A = A >> 1;
	setZeroSignFlags(A);
}
void lsrZero(uint8_t address) {
	SR = SR | (memory[address & 0xFF] & CARRY_FLAG);
	memory[address & 0xFF] = memory[address & 0xFF] >> 1;
	setZeroSignFlags(memory[address & 0xFF]);
}
void lsrZeroX(uint8_t address) {
	SR = SR | (memory[(address + X) & 0xFF] & CARRY_FLAG);
	memory[(address + X) & 0xFF] = memory[(address + X) & 0xFF] << 1;
	setZeroSignFlags(memory[(address + X) & 0xFF]);
}
void lsrAbs(uint16_t address) {
	SR = SR | (memory[address] & CARRY_FLAG);
	memory[address] = memory[address] >> 1;
	setZeroSignFlags(memory[address]);
}
void lsrAbsX(uint16_t address) {
	SR = SR | (memory[address + X] & CARRY_FLAG);
	memory[address + X] = memory[address + X] >> 1;
	setZeroSignFlags(memory[address + X]);
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
	Y = memory[address + X];
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
	X = memory[address + Y];
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
	A = memory[address + X];
	setZeroSignFlags(A);
}
void ldaAbsY(uint16_t address) {
	A = memory[address + Y];
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
	PC = *(uint16_t *) (memory + address);
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
	memory[address + X]++;
	setZeroSignFlags(memory[address + X]);
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
	A = A ^ memory[address + X];
	setZeroSignFlags(A);
}
void eorAbsY(uint16_t address) {
	A = A ^ memory[address + Y];
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
	memory[address + X]--;
	setZeroSignFlags(memory[address + X]);
}
/*
 ============================================================================
 Compare Y
 ============================================================================
 */
void cmpY(uint8_t address) {
	if (Y >= address)
		SR = SR | CARRY_FLAG;
	else
		SR = SR & (~CARRY_FLAG);

	if (Y == address)
		SR = SR | ZERO_FLAG;
	else
		SR = SR & (~ZERO_FLAG);

	if ((Y - address) & 0x80)
		SR = SR | SIGN_FLAG;
	else
		SR = SR & (~SIGN_FLAG);
}
void cmpYZero(uint8_t address) {
	if (Y >= memory[address & 0xFF])
		SR = SR | CARRY_FLAG;
	else
		SR = SR & (~CARRY_FLAG);

	if (Y == memory[address & 0xFF])
		SR = SR | ZERO_FLAG;
	else
		SR = SR & (~ZERO_FLAG);

	if ((Y - memory[address & 0xFF]) & 0x80)
		SR = SR | SIGN_FLAG;
	else
		SR = SR & (~SIGN_FLAG);
}
void cmpYAbs(uint16_t address) {
	if (Y >= memory[address])
		SR = SR | CARRY_FLAG;
	else
		SR = SR & (~CARRY_FLAG);

	if (Y == memory[address])
		SR = SR | ZERO_FLAG;
	else
		SR = SR & (~ZERO_FLAG);

	if ((Y - memory[address]) & 0x80)
		SR = SR | SIGN_FLAG;
	else
		SR = SR & (~SIGN_FLAG);
}
/*
 ============================================================================
 Compare X
 ============================================================================
 */
void cmpX(uint8_t address) {
	if (X >= address)
		SR = SR | CARRY_FLAG;
	else
		SR = SR & (~CARRY_FLAG);

	if (X == address)
		SR = SR | ZERO_FLAG;
	else
		SR = SR & (~ZERO_FLAG);

	if ((X - address) & 0x80)
		SR = SR | SIGN_FLAG;
	else
		SR = SR & (~SIGN_FLAG);
}
void cmpXZero(uint8_t address) {
	if (X >= memory[address & 0xFF])
		SR = SR | CARRY_FLAG;
	else
		SR = SR & (~CARRY_FLAG);

	if (X == memory[address & 0xFF])
		SR = SR | ZERO_FLAG;
	else
		SR = SR & (~ZERO_FLAG);

	if ((X - memory[address & 0xFF]) & 0x80)
		SR = SR | SIGN_FLAG;
	else
		SR = SR & (~SIGN_FLAG);
}
void cmpXAbs(uint16_t address) {
	if (X >= memory[address])
		SR = SR | CARRY_FLAG;
	else
		SR = SR & (~CARRY_FLAG);

	if (X == memory[address])
		SR = SR | ZERO_FLAG;
	else
		SR = SR & (~ZERO_FLAG);

	if ((X - memory[address]) & 0x80)
		SR = SR | SIGN_FLAG;
	else
		SR = SR & (~SIGN_FLAG);
}
/*
 ============================================================================
 Compare
 ============================================================================
 */
void cmp(uint8_t address) {
	if (A >= address)
		SR = SR | CARRY_FLAG;
	else
		SR = SR & (~CARRY_FLAG);

	if (A == address)
		SR = SR | ZERO_FLAG;
	else
		SR = SR & (~ZERO_FLAG);

	if ((A - address) & 0x80)
		SR = SR | SIGN_FLAG;
	else
		SR = SR & (~SIGN_FLAG);
}
void cmpZero(uint8_t address) {
	if (A >= memory[address & 0xFF])
		SR = SR | CARRY_FLAG;
	else
		SR = SR & (~CARRY_FLAG);

	if (A == memory[address & 0xFF])
		SR = SR | ZERO_FLAG;
	else
		SR = SR & (~ZERO_FLAG);

	if ((A - memory[address & 0xFF]) & 0x80)
		SR = SR | SIGN_FLAG;
	else
		SR = SR & (~SIGN_FLAG);
}
void cmpZeroX(uint8_t address) {
	if (A >= memory[(address + X) & 0xFF])
		SR = SR | CARRY_FLAG;
	else
		SR = SR & (~CARRY_FLAG);

	if (A == memory[(address + X) & 0xFF])
		SR = SR | ZERO_FLAG;
	else
		SR = SR & (~ZERO_FLAG);

	if ((A - memory[(address + X) & 0xFF]) & 0x80)
		SR = SR | SIGN_FLAG;
	else
		SR = SR & (~SIGN_FLAG);
}
void cmpAbs(uint16_t address) {
	if (A >= memory[address])
		SR = SR | CARRY_FLAG;
	else
		SR = SR & (~CARRY_FLAG);

	if (A == memory[address])
		SR = SR | ZERO_FLAG;
	else
		SR = SR & (~ZERO_FLAG);

	if ((A - memory[address]) & 0x80)
		SR = SR | SIGN_FLAG;
	else
		SR = SR & (~SIGN_FLAG);
}
void cmpAbsX(uint16_t address) {
	if (A >= memory[address + X])
		SR = SR | CARRY_FLAG;
	else
		SR = SR & (~CARRY_FLAG);

	if (A == memory[address + X])
		SR = SR | ZERO_FLAG;
	else
		SR = SR & (~ZERO_FLAG);

	if ((A - memory[address + X]) & 0x80)
		SR = SR | SIGN_FLAG;
	else
		SR = SR & (~SIGN_FLAG);
}
void cmpAbsY(uint16_t address) {
	if (A >= memory[address + Y])
		SR = SR | CARRY_FLAG;
	else
		SR = SR & (~CARRY_FLAG);

	if (A == memory[address + Y])
		SR = SR | ZERO_FLAG;
	else
		SR = SR & (~ZERO_FLAG);

	if ((A - memory[address + Y]) & 0x80)
		SR = SR | SIGN_FLAG;
	else
		SR = SR & (~SIGN_FLAG);
}
void cmpIndX(uint8_t address) {
	uint16_t newAddress = indXAddress(address);
	if (A >= memory[newAddress])
		SR = SR | CARRY_FLAG;
	else
		SR = SR & (~CARRY_FLAG);

	if (A == memory[newAddress])
		SR = SR | ZERO_FLAG;
	else
		SR = SR & (~ZERO_FLAG);

	if ((A - memory[newAddress]) & 0x80)
		SR = SR | SIGN_FLAG;
	else
		SR = SR & (~SIGN_FLAG);
}
void cmpIndY(uint8_t address) {
	uint16_t newAddress = indYAddress(address);
	if (A >= memory[newAddress])
		SR = SR | CARRY_FLAG;
	else
		SR = SR & (~CARRY_FLAG);

	if (A == memory[newAddress])
		SR = SR | ZERO_FLAG;
	else
		SR = SR & (~ZERO_FLAG);

	if ((A - memory[newAddress]) & 0x80)
		SR = SR | SIGN_FLAG;
	else
		SR = SR & (~SIGN_FLAG);
}
/*
 ============================================================================
 Bit test
 ============================================================================
 */
void bitZero(uint8_t address) {
	if ((A & memory[address & 0xFF]) == 0)
		SR = SR | ZERO_FLAG;
	else
		SR = SR & ~ZERO_FLAG;
	SR = SR | (memory[address & 0xFF] & OVERFLOW_FLAG);
	SR = SR | (memory[address & 0xFF] & SIGN_FLAG);
}
void bitAbs(uint16_t address) {
	if ((A & memory[address]) == 0)
		SR = SR | ZERO_FLAG;
	else
		SR = SR & ~ZERO_FLAG;
	SR = SR | (memory[address] & OVERFLOW_FLAG);
	SR = SR | (memory[address] & SIGN_FLAG);
}
/*
 ============================================================================
 Arithmetic shift left
 ============================================================================
 */
void asl() {
	// set the carry flag to whatever was in bit 7 of A
	SR = SR | ((A & SIGN_FLAG) >> 7);
	A = A << 1;
	setZeroSignFlags(A);
}
void aslZero(uint8_t address) {
	SR = SR | ((memory[address & 0xFF] & SIGN_FLAG) >> 7);
	memory[address & 0xFF] = memory[address & 0xFF] << 1;
	setZeroSignFlags(memory[address & 0xFF]);
}
void aslZeroX(uint8_t address) {
	SR = SR | ((memory[(address + X) & 0xFF] & SIGN_FLAG) >> 7);
	memory[(address + X) & 0xFF] = memory[(address + X) & 0xFF] << 1;
	setZeroSignFlags(memory[(address + X) & 0xFF]);
}
void aslAbs(uint16_t address) {
	SR = SR | ((memory[address] & SIGN_FLAG) >> 7);
	memory[address] = memory[address] << 1;
	setZeroSignFlags(memory[address]);
}
void aslAbsX(uint16_t address) {
	SR = SR | ((memory[address + X] & SIGN_FLAG) >> 7);
	memory[address + X] = memory[address + X] << 1;
	setZeroSignFlags(memory[address + X]);
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
	A = A & memory[address + X];
	setZeroSignFlags(A);
}
void andAbsY(uint16_t address) {
	A = A & memory[address + Y];
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
	if (result == 0)
		SR = SR | ZERO_FLAG;
	else
		SR = SR & ~ZERO_FLAG;

	if (result < A)
		SR = SR | CARRY_FLAG;
	else
		SR = SR & ~CARRY_FLAG;

	if (result & 0x80)
		SR = SR | SIGN_FLAG;
	else
		SR = SR & ~SIGN_FLAG;

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
	A = A + memory[address + X] + (SR & CARRY_FLAG);
	setAdcFlags(oldA, memory[address + X], A);
}
/* two byte absolute address + Y */
void adcAbsY(uint16_t address) {
	uint8_t oldA = A;
	A = A + memory[address + Y] + (SR & CARRY_FLAG);
	setAdcFlags(oldA, memory[address + Y], A);
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
 Other implied
 ============================================================================
 */
void nop() {
}

void pha() {
	memory[SP--] = A;
}
void php() {
	memory[SP--] = SR;
}
void pla() {
	A = memory[++SP];
	setZeroSignFlags(A);
}
void plp() {
	SR = memory[++SP];
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
	SP = X | 0x0100;
}
void tya() {
	A = Y;
	setZeroSignFlags(A);
}
void brk() {

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

	if ((SR & CARRY_FLAG) == 0) {
		PC += displacement;
	}
}
void bcs(int8_t displacement) {

	if (SR & CARRY_FLAG) {
		PC += displacement;
	}
}
void beq(int8_t displacement) {

	if (SR & ZERO_FLAG) {
		PC += displacement;
	}
}
void bmi(int8_t displacement) {

	if (SR & SIGN_FLAG) {
		PC += displacement;
	}
}
void bne(int8_t displacement) {

	if ((SR & ZERO_FLAG) == 0) {
		PC += displacement;
	}
}
void bpl(int8_t displacement) {

	if ((SR & SIGN_FLAG) == 0) {
		PC += displacement;
	}
}
void bvc(int8_t displacement) {

	if ((SR & OVERFLOW_FLAG) == 0) {
		PC += displacement;
	}
}
void bvs(int8_t displacement) {

	if (SR & OVERFLOW_FLAG) {
		PC += displacement;
	}
}
/*
 ============================================================================
 Helpers
 ============================================================================
 */
void dump() {

	printf("\t\tA: %x ", A);
	printf("X: %x ", X);
	printf("Y: %x ", Y);
	printf("P: %x ", SR);
	printf("SP: %x\n", SP);

}
void setZeroSignFlags(uint8_t reg) {
	if (reg == 0)
		SR = SR | ZERO_FLAG;
	else
		SR = SR & (~ZERO_FLAG);

	if (reg & 0x80)
		SR = SR | SIGN_FLAG;
	else
		SR = SR & (~SIGN_FLAG);
}
void setOverflow(uint8_t one, uint8_t two, uint8_t result) {

	SR = SR & ~OVERFLOW_FLAG;
	if ((one & 0x80) && (two & 0x80) && (result & 0x80) == 0) {
		SR = SR | OVERFLOW_FLAG;
	} else if ((one & 0x80) == 0 && (two & 0x80) == 0 && (result & 0x80)) {
		SR = SR | OVERFLOW_FLAG;
	}
}
uint16_t indXAddress(uint8_t address) {
	uint16_t result = *(uint16_t *) (memory + ((address + X) & 0xFF));
	return result;
}
uint16_t indYAddress(uint8_t address) {
	uint16_t result = (*(uint16_t *) (memory + (address & 0xFF))) + Y;
	return result;
}

