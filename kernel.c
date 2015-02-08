//
//  kernel.c
//  utos
//
//  Created by Anuj Jamwal on 2/7/15.
//  Copyright (c) 2015 Anuj Jamwal. All rights reserved.
//

#include "kernel.h"
#include "kconfig.h"


// functions to be ported by individual platform code
extern void port_setup_timer(void);
extern void port_kernel_tick(void);
extern void port_start_timer(void);
extern void port_init_context(pCtrlBlock * pcb);



pCtrlBlock processes[PROCESS_COUNT];
volatile pCtrlBlock * volatile context;



void _kernel_housekeeping(void);
void _kernel_init_pcb(pCode code, pCtrlBlock *pcb, unsigned int time);
pCtrlBlock * _kernel_process_with_max_priority(pCtrlBlock * process, pCtrlBlock * lastProcess);



void kernel_init(void) {
    kernel_spawn(_kernel_housekeeping, 0);
}

void kernel_start(void) {
    port_start_timer();
}

void kernel_spawn(pCode code, unsigned int time) {
    static unsigned char pInd = 0;
    
    pCtrlBlock * pcb = &processes[pInd++];
    
    pcb->code = code;
    pcb->waitTicks = time % SYSTEM_TICK > 0 ? time / SYSTEM_TICK + 1 : time / SYSTEM_TICK;
    pcb->elapsedTicks = 0;
    pcb->status = Waiting;
    
    port_init_context(pcb);
}

void kernel_run_schedular(void) {
    
    static unsigned char i;
    static pCtrlBlock * tmp, *candidate;
    
    candidate = 0;
    
    for(i = 1; i < PROCESS_COUNT+1; i++) {
        tmp = &processes[i];
        
        if (tmp->status == Running) {
            tmp->status = Waiting;
            tmp->elapsedTicks = 0;
        } else if(tmp->status == Waiting) {
            tmp->elapsedTicks++;
            
            if(tmp->elapsedTicks >= tmp->waitTicks)
                candidate = _kernel_process_with_max_priority(tmp, candidate);
        }
    }
    
    if(candidate == 0) candidate = &processes[0];
    
    context = candidate;
    context->status = Running;
}

pCtrlBlock * _kernel_process_with_max_priority(pCtrlBlock * process,
    return process;
}

void _kernel_housekeeping(void) {
    while (1) {
        ;
    }
}
