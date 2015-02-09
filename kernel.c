//
//  kernel.c
//  utos
//
//  Created by Anuj Jamwal on 2/7/15.
//  Copyright (c) 2015 Anuj Jamwal. All rights reserved.
//

#include "kernel.h"
#include "kconfig.h"
#include "port.h"
#include "ipc.h"


pCtrlBlock processes[PROCESS_COUNT+1];
volatile pCtrlBlock * volatile context;
volatile pid pInd = 0;

void _kernel_housekeeping(void);
void _kernel_init_pcb(pCode code, pCtrlBlock *pcb, unsigned int time);
pCtrlBlock * _kernel_process_with_max_priority(pCtrlBlock * process, pCtrlBlock * lastProcess);


void kernel_init(void) {
    kernel_spawn(_kernel_housekeeping, 0);
}

void kernel_start(void) {
    port_start_timer();
}

pid kernel_spawn(pCode code, unsigned int time) {
    port_cli();
    
    pCtrlBlock * pcb = &processes[pInd++];
    
    pcb->pid = pInd - 1;
    pcb->code = code;
    pcb->waitTicks = time % SYSTEM_TICK > 0 ? time / SYSTEM_TICK + 1 : time / SYSTEM_TICK;
    pcb->elapsedTicks = 0;
    pcb->status = Waiting;
    
    port_init_context(pcb);
    port_sei();
    return pcb->pid;
}

void kernel_run_scheduler(void) {
    
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

pCtrlBlock * _kernel_process_with_max_priority(pCtrlBlock * process, pCtrlBlock * lastProcess) {
    return process;
}
                                               
void kernel_send(pid process, unsigned char * message, unsigned char length) {
    mailbox * mail = &processes[process].mail;
    message_send(mail, context->pid, message, length);
}

ipcMessage * kernel_receive(void) {
    return message_receive((mailbox *)&context->mail);
}
                                               
void _kernel_housekeeping(void) {
    while (1) {
        ;
    }
}
