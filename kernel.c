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
#include "process.h"


pCtrlBlock processes[PROCESS_COUNT+1];
volatile pCtrlBlock * volatile context;
volatile pid pInd = 0;
unsigned char pCount = 0;

void _kernel_housekeeping(void);
void _kernel_init_pcb(pCode code, pCtrlBlock *pcb, unsigned int time);
pCtrlBlock * kernel_next_process(pCtrlBlock * process) ;


void kernel_init(void) {
    kernel_spawn(_kernel_housekeeping, VLow);
}

void kernel_start(void) {
    port_start_timer();
}

pid kernel_spawn(pCode code, pPriority priority) {
    port_cli();
    pCount++;
    
    pCtrlBlock * pcb = &processes[pInd++];
    
    pcb->pid = pInd - 1;
    pcb->code = code;
    // pcb->waitTicks = time % SYSTEM_TICK > 0 ? time / SYSTEM_TICK + 1 : time / SYSTEM_TICK;
    pcb->elapsedTicks = 0;
    pcb->status = Ready;
    pcb->priority = priority;
    
    port_init_context(pcb);
    port_sei();
    return pcb->pid;
}

void kernel_run_scheduler(void) {
    
    unsigned char i;
    
    for(i = 1; i < pCount; i++) {
        process_run_state_machine(&processes[i]);
    }
    
    context = kernel_next_process(processes);
    process_change_status((pCtrlBlock*)context, Running);
}

pCtrlBlock * kernel_next_process(pCtrlBlock * process) {
    pCtrlBlock * p = 0, *t;
    unsigned char i;
    
    for(i = 1; i < pCount; i++) {
        t = &process[i];
        if (t->status == Ready) {
            if (p == 0) {
                p = t;
            } else if(p->priority < t->priority) {
                p = t;
            } else if(p->priority == t->priority && p->elapsedTicks < t->elapsedTicks) {
                p = t;
            }
        }
    }
    
    if (p == 0) {
        p = &process[0];
    }
    
    return p;
}
                                               
void kernel_send(pid process, unsigned char * message, unsigned char length) {
    mailbox * mail = &processes[process].mail;
    message_send(mail, context->pid, message, length);
}

ipcMessage * kernel_receive(void) {
    return message_receive((mailbox *)&context->mail);
}

void kernel_sleep(unsigned int time) {
    context->status = Sleeping;
    context->waitTicks = time / SYSTEM_TICK;
    kernel_yield();
}
                                               
void _kernel_housekeeping(void) {
    while (1) {
        ;
    }
}
