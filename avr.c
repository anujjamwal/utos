/*
 * avr.c
 *
 *  Created on: Feb 6, 2015
 *      Author: Anuj
 */

#include <avr/interrupt.h>
#include "avr.h"
#include "kernel.h"

#define STATUS_REG ((ProcessStack) 0x80)

void port_setup_context(ProcessStack * stack, ProcessCode code, void * params) {
	unsigned short address;

	address = (unsigned short) code;
	*stack = (ProcessStack) address;
	stack --;

	address >>= 8;
	*stack = (ProcessStack) address;
	stack --;

	*stack = ( ProcessStack ) 0x00;	/* R0 */
	stack--;

	*stack = STATUS_REG;
	stack--;

	/* Now the remaining registers.   The compiler expects R1 to be 0. */
	*stack = ( ProcessStack ) 0x00;	/* R1 */
	stack--;
	*stack = ( ProcessStack ) 0x02;	/* R2 */
	stack--;
	*stack = ( ProcessStack ) 0x03;	/* R3 */
	stack--;
	*stack = ( ProcessStack ) 0x04;	/* R4 */
	stack--;
	*stack = ( ProcessStack ) 0x05;	/* R5 */
	stack--;
	*stack = ( ProcessStack ) 0x06;	/* R6 */
	stack--;
	*stack = ( ProcessStack ) 0x07;	/* R7 */
	stack--;
	*stack = ( ProcessStack ) 0x08;	/* R8 */
	stack--;
	*stack = ( ProcessStack ) 0x09;	/* R9 */
	stack--;
	*stack = ( ProcessStack ) 0x10;	/* R10 */
	stack--;
	*stack = ( ProcessStack ) 0x11;	/* R11 */
	stack--;
	*stack = ( ProcessStack ) 0x12;	/* R12 */
	stack--;
	*stack = ( ProcessStack ) 0x13;	/* R13 */
	stack--;
	*stack = ( ProcessStack ) 0x14;	/* R14 */
	stack--;
	*stack = ( ProcessStack ) 0x15;	/* R15 */
	stack--;
	*stack = ( ProcessStack ) 0x16;	/* R16 */
	stack--;
	*stack = ( ProcessStack ) 0x17;	/* R17 */
	stack--;
	*stack = ( ProcessStack ) 0x18;	/* R18 */
	stack--;
	*stack = ( ProcessStack ) 0x19;	/* R19 */
	stack--;
	*stack = ( ProcessStack ) 0x20;	/* R20 */
	stack--;
	*stack = ( ProcessStack ) 0x21;	/* R21 */
	stack--;
	*stack = ( ProcessStack ) 0x22;	/* R22 */
	stack--;
	*stack = ( ProcessStack ) 0x23;	/* R23 */
	stack--;

	/* Place the parameter on the stack in the expected location. */
	address = ( unsigned short ) params;
	*stack = ( ProcessStack ) ( address & ( unsigned short ) 0x00ff );
	stack--;

	address >>= 8;
	*stack = ( ProcessStack ) ( address & ( unsigned short ) 0x00ff );
	stack--;

	*stack = ( ProcessStack ) 0x26;	/* R26 X */
	stack--;
	*stack = ( ProcessStack ) 0x27;	/* R27 */
	stack--;
	*stack = ( ProcessStack ) 0x28;	/* R28 Y */
	stack--;
	*stack = ( ProcessStack ) 0x29;	/* R29 */
	stack--;
	*stack = ( ProcessStack ) 0x30;	/* R30 Z */
	stack--;
	*stack = ( ProcessStack ) 0x031;	/* R31 */
	stack--;
}

ISR(TIMER1_COMPA_vect, ISR_NAKED)
{
    kernel_on_tick();

    asm volatile ( "reti" );
}

void port_setup_system_ticker() {
	cli();
	TCCR1B |= (1 << WGM12)|(1 << CS11)|(1 << CS10);
	TCNT1 = 0;
	TIMSK |= (1 << OCIE1A);

		// initialize compare value
	OCR1A = 40000;
}

void port_ticker_start() {
	sei();
}

