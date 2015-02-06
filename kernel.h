/*
 * kernel.h
 *
 *  Created on: Feb 5, 2015
 *      Author: Anuj
 */

#ifndef KERNEL_H_
#define KERNEL_H_

// Implement the Timer Interrupt for kernel to use
// platform specific

#ifndef PORT_SAVE_CONTEXT
	#define PORT_SAVE_CONTEXT(sp) ;
#endif

#ifndef PORT_RESTORE_CONTEXT
	#define PORT_RESTORE_CONTEXT(sp) ;
#endif

#ifndef PORT_RETURN
	#define PORT_RETURN() ;
#endif

#define MAX_STACK_SIZE 100


typedef void (* ProcessCode) (void *);
typedef enum {New, Running, Waiting} ProcessStatus;
typedef volatile unsigned char ProcessStack;
typedef struct {
	ProcessCode code;
	volatile ProcessStatus status;

	ProcessStack* baseOfStack;
	ProcessStack* startOfStack;
	ProcessStack* topOfStack;

	unsigned int ticksLeft;
	unsigned int maxTicks;
} ProcessControlBlock;


void kernel_init();
void kernel_start();
void kernel_spawn_process(ProcessCode code, void * params, unsigned int maxTicks);
void kernel_on_tick() __attribute__ ((naked));

#endif /* KERNEL_H_ */
