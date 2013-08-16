/*
 * cpu.h
 *
 *  Created on: Jun 17, 2013
 *      Author: n0210015
 */
#ifndef CPU_H_
#define CPU_H_

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "rom.h"
#include "ppu.h"

#define CARRY_FLAG 0x01
#define ZERO_FLAG 0x02
#define INTERRUPT_FLAG 0x04
#define DECIMAL_FLAG 0x08
#define BREAK_FLAG 0x10
#define OVERFLOW_FLAG 0x40
#define SIGN_FLAG 0x80

#define UPPER_ROM_BANK 0xC000
#define LOWER_ROM_BANK 0x8000
#define CARTRIDGE_RAM 0x6000
#define EXPANSION_MODULES 0x5000
#define INPUT_OUTPUT 0x2000
#define CPU_RAM 0x0000

#define PIXEL_ADDRESS 0x0200

extern uint8_t A; /* accumulator register */
extern uint8_t X; /* index X register */
extern uint8_t Y; /* index Y register */
extern uint8_t SR; /* status register */
extern uint16_t SP; /* stack pointer */
extern uint16_t PC;/* program counter */

extern uint8_t memory[0x10000];

extern ppu_t *ppu;

extern uint16_t pixelMap;

/*
 ============================================================================
 Main
 ============================================================================
 */
void cpu_load_rom(rom_t *rom);
void run_6502();
void run_nes(ppu_t *ppu);
/*
 ============================================================================
 Interrupts
 ============================================================================
 */
void rti();
/*
 ============================================================================
 Subroutines
 ============================================================================
 */
void jsrAbs(uint16_t address);
void rts();
/*
 ============================================================================
 Store Y Register
 ============================================================================
 */
void styZero(uint8_t address);
void styZeroX(uint8_t address);
void styAbs(uint16_t address);
/*
 ============================================================================
 Store X Register
 ============================================================================
 */
void stxZero(uint8_t address);
void stxZeroY(uint8_t address);
void stxAbs(uint16_t address);
/*
 ============================================================================
 Store Accumulator
 ============================================================================
 */
void staZero(uint8_t address);
void staZeroX(uint8_t address);
void staAbs(uint16_t address);
void staAbsX(uint16_t address);
void staAbsY(uint16_t address);
void staIndX(uint8_t address);
void staIndY(uint8_t address);
/*
 ============================================================================
 Subtract with Carry
 ============================================================================
 */
void setSbcFlags(uint8_t A, uint8_t B, uint8_t result);
void sbc(uint8_t address);
void sbcZero(uint8_t address);
void sbcZeroX(uint8_t address);
void sbcAbs(uint16_t address);
void sbcAbsX(uint16_t address);
void sbcAbsY(uint16_t address);
void sbcIndX(uint8_t address);
void sbcIndY(uint8_t address);
/*
 ============================================================================
 Rotate right
 ============================================================================
 */
void ror();
void rorZero(uint8_t address);
void rorZeroX(uint8_t address);
void rorAbs(uint16_t address);
void rorAbsX(uint16_t address);
/*
 ============================================================================
 Rotate left
 ============================================================================
 */
void rol();
void rolZero(uint8_t address);
void rolZeroX(uint8_t address);
void rolAbs(uint16_t address);
void rolAbsX(uint16_t address);
/*
 ============================================================================
 Logical Or
 ============================================================================
 */
void ora(uint8_t address);
void oraZero(uint8_t address);
void oraZeroX(uint8_t address);
void oraAbs(uint16_t address);
void oraAbsX(uint16_t address);
void oraAbsY(uint16_t address);
void oraIndX(uint8_t address);
void oraIndY(uint8_t address);
/*
 ============================================================================
 Logical shift right
 ============================================================================
 */
void lsr();
void lsrZero(uint8_t address);
void lsrZeroX(uint8_t address);
void lsrAbs(uint16_t address);
void lsrAbsX(uint16_t address);
/*
 ============================================================================
 Load Y Register
 ============================================================================
 */
void ldy(uint8_t address);
void ldyZero(uint8_t address);
void ldyZeroX(uint8_t address);
void ldyAbs(uint16_t address);
void ldyAbsX(uint16_t address);
/*
 ============================================================================
 Load X Register
 ============================================================================
 */
void ldx(uint8_t address);
void ldxZero(uint8_t address);
void ldxZeroY(uint8_t address);
void ldxAbs(uint16_t address);
void ldxAbsY(uint16_t address);
/*
 ============================================================================
 Load Accumulator
 ============================================================================
 */
void lda(uint8_t address);
void ldaZero(uint8_t address);
void ldaZeroX(uint8_t address);
void ldaAbs(uint16_t address);
void ldaAbsX(uint16_t address);
void ldaAbsY(uint16_t address);
void ldaIndX(uint8_t address);
void ldaIndY(uint8_t address);
/*
 ============================================================================
 Jump
 ============================================================================
 */
void jmpAbs(uint16_t address);
void jmpInd(uint16_t address);
/*
 ============================================================================
 Increment memory
 ============================================================================
 */
void incZero(uint8_t address);
void incZeroX(uint8_t address);
void incAbs(uint16_t address);
void incAbsX(uint16_t address);
/*
 ============================================================================
 Exclusive Or
 ============================================================================
 */
void eor(uint8_t address);
void eorZero(uint8_t address);
void eorZeroX(uint8_t address);
void eorAbs(uint16_t address);
void eorAbsX(uint16_t address);
void eorAbsY(uint16_t address);
void eorIndX(uint8_t address);
void eorIndY(uint8_t address);
/*
 ============================================================================
 Decrement memory
 ============================================================================
 */
void decZero(uint8_t address);
void decZeroX(uint8_t address);
void decAbs(uint16_t address);
void decAbsX(uint16_t address);
/*
 ============================================================================
 Compare Y
 ============================================================================
 */
void cmpY(uint8_t address);
void cmpYZero(uint8_t address);
void cmpYAbs(uint16_t address);
/*
 ============================================================================
 Compare X
 ============================================================================
 */
void cmpX(uint8_t address);
void cmpXZero(uint8_t address);
void cmpXAbs(uint16_t address);
/*
 ============================================================================
 Compare
 ============================================================================
 */
void compare(uint8_t A, uint8_t address);
void cmp(uint8_t address);
void cmpZero(uint8_t address);
void cmpZeroX(uint8_t address);
void cmpAbs(uint16_t address);
void cmpAbsX(uint16_t address);
void cmpAbsY(uint16_t address);
void cmpIndX(uint8_t address);
void cmpIndY(uint8_t address);
/*
 ============================================================================
 Bit test
 ============================================================================
 */
void bitZero(uint8_t address);
void bitAbs(uint16_t address);
/*
 ============================================================================
 Arithmetic shift left
 ============================================================================
 */
void asl();
void aslZero(uint8_t address);
void aslZeroX(uint8_t address);
void aslAbs(uint16_t address);
void aslAbsX(uint16_t address);
/*
 ============================================================================
 Logical And
 ============================================================================
 */
void and(uint8_t address);
void andZero(uint8_t address);
void andZeroX(uint8_t address);
void andAbs(uint16_t address);
void andAbsX(uint16_t address);
void andAbsY(uint16_t address);
void andIndX(uint8_t address);
void andIndY(uint8_t address);
/*
 ============================================================================
 Add with Carry
 ============================================================================
 */
void setAdcFlags(uint8_t A, uint8_t B, uint8_t result);
void adc(uint8_t address);
void adcZero(uint8_t address);
void adcZeroX(uint8_t address);
void adcAbs(uint16_t address);
void adcAbsX(uint16_t address);
void adcAbsY(uint16_t address);
void adcIndX(uint8_t address);
void adcIndY(uint8_t address);

/*
 ============================================================================
 No Op
 ============================================================================
 */
void nop();
void nopImm(uint8_t address);
void nopZero(uint8_t address);
void nopZeroX(uint8_t address);
void nopAbs(uint16_t address);
void nopAbsX(uint16_t address);
void nopAbsY(uint16_t address);
void nopIndX(uint8_t address);
void nopIndY(uint8_t address);

/*
 ============================================================================
 Other implied
 ============================================================================
 */
void pha();
void php();
void pla();
void plp();
void tax();
void tay();
void tsx();
void txa();
void txs();
void tya();
void brk();

/*
 ============================================================================
 Branches
 ============================================================================
 */
void bcc(int8_t displacement);
void bcs(int8_t displacement);
void beq(int8_t displacement);
void bmi(int8_t displacement);
void bne(int8_t displacement);
void bpl(int8_t displacement);
void brk();
void bvc(int8_t displacement);
void bvs(int8_t displacement);
/*
 ============================================================================
 Set flags
 ============================================================================
 */
void sec();
void sed();
void sei();
/*
 ============================================================================
 Clear flags
 ============================================================================
 */
void clc();
void cld();
void cli();
void clv();
/*
 ============================================================================
 Inc/Dec X, Y
 ============================================================================
 */
void dex();
void dey();
void inx();
void iny();

/*
 ============================================================================
 Helpers
 ============================================================================
 */
void dump();
void setZeroSignFlags(uint8_t reg);
void setSbcOverflow(uint8_t one, uint8_t two, uint8_t result);
void setOverflow(uint8_t one, uint8_t two, uint8_t result);
uint16_t indXAddress(uint8_t address);
uint16_t indYAddress(uint8_t address);
void drawPixels();
void drawRects();

#endif /* CPU_H_ */
