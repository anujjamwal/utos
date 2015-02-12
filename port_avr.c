//
//  avr.c
//  utos
//
//  Created by Anuj Jamwal on 2/7/15.
//  Copyright (c) 2015 Anuj Jamwal. All rights reserved.
//

#include <avr/interrupt.h>
#include "port.h"
#include "kernel.h"

#define SAVE_CONTEXT() \
    asm volatile (	"push	r0						\n\t"	\
    "in		r0, __SREG__			\n\t"	\
    "cli							\n\t"	\
    "push	r0						\n\t"	\
    "push	r1						\n\t"	\
    "clr	r1						\n\t"	\
    "push	r2						\n\t"	\
    "push	r3						\n\t"	\
    "push	r4						\n\t"	\
    "push	r5						\n\t"	\
    "push	r6						\n\t"	\
    "push	r7						\n\t"	\
    "push	r8						\n\t"	\
    "push	r9						\n\t"	\
    "push	r10						\n\t"	\
    "push	r11						\n\t"	\
    "push	r12						\n\t"	\
    "push	r13						\n\t"	\
    "push	r14						\n\t"	\
    "push	r15						\n\t"	\
    "push	r16						\n\t"	\
    "push	r17						\n\t"	\
    "push	r18						\n\t"	\
    "push	r19						\n\t"	\
    "push	r20						\n\t"	\
    "push	r21						\n\t"	\
    "push	r22						\n\t"	\
    "push	r23						\n\t"	\
    "push	r24						\n\t"	\
    "push	r25						\n\t"	\
    "push	r26						\n\t"	\
    "push	r27						\n\t"	\
    "push	r28						\n\t"	\
    "push	r29						\n\t"	\
    "push	r30						\n\t"	\
    "push	r31						\n\t"	\
    "lds	r26, context		\n\t"	\
    "lds	r27, context + 1	\n\t"	\
    "in		r0, 0x3d				\n\t"	\
    "st		x+, r0					\n\t"	\
    "in		r0, 0x3e				\n\t"	\
    "st		x+, r0					\n\t"	\
    );

#define RESTORE_CONTEXT() \
    asm volatile (	"lds	r26, context		\n\t"	\
    "lds	r27, context + 1	\n\t"	\
    "ld		r28, x+					\n\t"	\
    "out	__SP_L__, r28			\n\t"	\
    "ld		r29, x+					\n\t"	\
    "out	__SP_H__, r29			\n\t"	\
    "pop	r31						\n\t"	\
    "pop	r30						\n\t"	\
    "pop	r29						\n\t"	\
    "pop	r28						\n\t"	\
    "pop	r27						\n\t"	\
    "pop	r26						\n\t"	\
    "pop	r25						\n\t"	\
    "pop	r24						\n\t"	\
    "pop	r23						\n\t"	\
    "pop	r22						\n\t"	\
    "pop	r21						\n\t"	\
    "pop	r20						\n\t"	\
    "pop	r19						\n\t"	\
    "pop	r18						\n\t"	\
    "pop	r17						\n\t"	\
    "pop	r16						\n\t"	\
    "pop	r15						\n\t"	\
    "pop	r14						\n\t"	\
    "pop	r13						\n\t"	\
    "pop	r12						\n\t"	\
    "pop	r11						\n\t"	\
    "pop	r10						\n\t"	\
    "pop	r9						\n\t"	\
    "pop	r8						\n\t"	\
    "pop	r7						\n\t"	\
    "pop	r6						\n\t"	\
    "pop	r5						\n\t"	\
    "pop	r4						\n\t"	\
    "pop	r3						\n\t"	\
    "pop	r2						\n\t"	\
    "pop	r1						\n\t"	\
    "pop	r0						\n\t"	\
    "out	__SREG__, r0			\n\t"	\
    "pop	r0						\n\t"	\
    );

extern volatile pCtrlBlock * volatile context;
extern volatile pCtrlBlock * volatile nextProcess;
extern volatile pCtrlBlock scheduler;

void port_switch_context(void) __attribute__ ((naked));
void port_switch_context(void) {
    SAVE_CONTEXT();
    
    context = nextProcess;
    
    RESTORE_CONTEXT();
    sei();
    
    asm volatile ( "ret" );
}

ISR(TIMER1_COMPA_vect, ISR_NAKED)
{
    cli();
    
    nextProcess = &scheduler;
    port_switch_context();
    asm volatile ( "reti" );
}

void port_start_timer(void) {
    cli();
    // Timer in CTC mode WGM12
    // Prescalar of 64 (1 << CS11)|(1 << CS10)
    
    TCCR1B |= (1 << WGM12)|(1 << CS11)|(1 << CS10);
    TCNT1 = 0;
    TIMSK |= (1 << OCIE1A);
    
    // initialize compare value
    OCR1A = NUM_INSTRUCTION / 64;
    
    sei();
}


void port_init_context(pCtrlBlock * pcb) {
    pStack *stackbase = pcb->stack;
    unsigned char stacksize = 100;
    unsigned short address;
    address = (unsigned short) pcb->code;
    
    stackbase[--stacksize] = (pStack) ( address & (unsigned short) 0x00ff );
    address >>= 8;
    stackbase[--stacksize] = (pStack) ( address & (unsigned short) 0x00ff );
    stackbase[--stacksize] = (pStack) ( 0 ); /* R0 */
    stackbase[--stacksize] = (pStack) ( 0x80 ); /* SREG */
    stackbase[--stacksize] = (pStack) ( 0x0 ); /* R1 */
    stackbase[--stacksize] = (pStack) ( 2 ); /* R2 */
    stackbase[--stacksize] = (pStack) ( 3 ); /* R3 */
    stackbase[--stacksize] = (pStack) ( 4 ); /* R4 */
    stackbase[--stacksize] = (pStack) ( 5 ); /* R5 */
    stackbase[--stacksize] = (pStack) ( 6 ); /* R6 */
    stackbase[--stacksize] = (pStack) ( 7 ); /* R7 */
    stackbase[--stacksize] = (pStack) ( 8 ); /* R8 */
    stackbase[--stacksize] = (pStack) ( 9 ); /* R9 */
    stackbase[--stacksize] = (pStack) ( 10 ); /* R10 */
    stackbase[--stacksize] = (pStack) ( 11 ); /* R11 */
    stackbase[--stacksize] = (pStack) ( 12 ); /* R12 */
    stackbase[--stacksize] = (pStack) ( 13 ); /* R13 */
    stackbase[--stacksize] = (pStack) ( 14 ); /* R14 */
    stackbase[--stacksize] = (pStack) ( 15 ); /* R15 */
    stackbase[--stacksize] = (pStack) ( 16 ); /* R16 */
    stackbase[--stacksize] = (pStack) ( 17 ); /* R17 */
    stackbase[--stacksize] = (pStack) ( 18 ); /* R18 */
    stackbase[--stacksize] = (pStack) ( 19 ); /* R19 */
    stackbase[--stacksize] = (pStack) ( 20 ); /* R20 */
    stackbase[--stacksize] = (pStack) ( 21 ); /* R21 */
    stackbase[--stacksize] = (pStack) ( 22 ); /* R22 */
    stackbase[--stacksize] = (pStack) ( 23 ); /* R23 */
    /* Place the parameter on the stack in the expected location. */
    stackbase[--stacksize] = (pStack) 0;
    stackbase[--stacksize] = (pStack) 0;
    stackbase[--stacksize] = (pStack) 26; /* R26 X */
    stackbase[--stacksize] = (pStack) 27; /* R27 */
    stackbase[--stacksize] = (pStack) 28; /* R28 Y */
    stackbase[--stacksize] = (pStack) 29; /* R29 */
    stackbase[--stacksize] = (pStack) 30; /* R30 Z */
    stackbase[--stacksize] = (pStack) 31; /* R31 */
    pcb->topOfStack = &stackbase[--stacksize];
}

void port_sei(void) __attribute__((naked));
void port_sei(void) {
    sei();
    asm volatile ( "ret" );
}

void port_cli(void) __attribute__((naked));
void port_cli(void) {
    cli();
    asm volatile ( "ret" );
}
