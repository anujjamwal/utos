/*
 * kernel.c
 *
 *  Created on: Feb 5, 2015
 *      Author: Anuj
 */

#include "kernel.h"

unsigned char pIndex = 0, pIter, pCount = 2, pSchIndex = 0;
ProcessControlBlock * activeProcess, *pTemp;
//replace with list
ProcessControlBlock * processes[2];


extern void port_setup_context(ProcessStack * stack, ProcessCode code, void * params);
extern void port_setup_system_ticker();
extern void port_ticker_start();


void _k_update_tick();
ProcessControlBlock * _k_next_process();
void _k_allocate_and_initialize_stack(ProcessControlBlock * pcb, void * params);


void kernel_init() {
	port_setup_system_ticker();
}

void kernel_start() {
	port_ticker_start();
}

void kernel_spawn_process(ProcessCode code, void * params, unsigned int maxTicks) {
	ProcessControlBlock block;
	block.code = code;
	block.status = New;
	block.ticksLeft = maxTicks;
	block.maxTicks = maxTicks;

	_k_allocate_and_initialize_stack(&block, params);

	//replace with list operation
	processes[pIndex++] = &block;
}

void kernel_on_tick() {
	PORT_SAVE_CONTEXT(activeProcess->topOfStack);

	_k_update_tick();
    activeProcess = _k_next_process();

	PORT_RESTORE_CONTEXT(activeProcess->topOfStack);
	PORT_RETURN();
}

void _k_update_tick() {
	for(pIter = 0; pIter < pCount; pIter++) {
		pTemp = processes[pIter];

		if(pTemp->status == Running) {
			/*
			 * change the status of a running process to Waiting
			 * and reset the leftTicks to max Value
			 */
			pTemp->status = Waiting;
			pTemp->ticksLeft = pTemp->maxTicks;
		} else if(pTemp->status == Waiting) {
			// Decrement the number of ticks
			pTemp->ticksLeft -= 1;
		}
	}
}

ProcessControlBlock * _k_next_process() {
	// add some better scheduling logic
	pSchIndex = (pSchIndex + 1) / pCount;
	return processes[pSchIndex];
}

void _k_allocate_and_initialize_stack(ProcessControlBlock * pcb, void * params) {
	ProcessStack stack[MAX_STACK_SIZE];
	pcb->startOfStack = stack;
	pcb->topOfStack = pcb->baseOfStack = stack + MAX_STACK_SIZE-1;
	pcb->topOfStack --; // decrement from first location

	port_setup_context(pcb->topOfStack, pcb->code, params);
}

