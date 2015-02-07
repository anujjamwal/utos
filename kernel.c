//
//  kernel.c
//  utos
//
//  Created by Anuj Jamwal on 2/7/15.
//  Copyright (c) 2015 Anuj Jamwal. All rights reserved.
//

#include "kernel.h"
#include "kconfig.h"

extern void port_setup_timer(void);
extern void port_kernel_tick(void);
extern void port_start_timer(void);
extern void port_init_context(pCtrlBlock * pcb);

pCtrlBlock processes[PROCESS_COUNT];
volatile pCtrlBlock * volatile context;
volatile unsigned char pInd = 0, ptmp;

void kernel_init(void) {
    
}

void kernel_start(void) {
    port_setup_timer();
    port_start_timer();
    ptmp = 0;
}

void kernel_spawn(pCode code) {
    pCtrlBlock * pcb = &processes[pInd++];
    
    pcb->code = code;
    
    port_init_context(pcb);
}

void kernel_run_schedular(void) {
    ptmp = (ptmp + 1) & 0x01;
    context = &processes[ptmp];
}

