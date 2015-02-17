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
#include "schedul.h"


pCtrlBlock processes[PROCESS_COUNT+1];
volatile pCtrlBlock * volatile context;
volatile pCtrlBlock * volatile nextProcess;
volatile pCtrlBlock scheduler;

volatile pid pInd = 0;
unsigned char pCount = 0;

/* 
 * The System Processes to be run
 */
void kernel_housekeeping(void);
void scheduler_process(void);

inline void kernel_yield (void) __attribute__((always_inline));

void kernel_init(void) {
    scheduler.pid = pInd - 1;
    scheduler.code = scheduler_process;
    scheduler.elapsedTicks = 0;
    scheduler.status = Ready;
    scheduler.priority = 100;
    
    port_init_context((pCtrlBlock *) &scheduler);
    
    kernel_spawn(kernel_housekeeping, VLow);
}

void scheduler_process(void) {
    unsigned char i;
    while (1) {

        for(i = 1; i < pCount; i++) {
            process_run_state_machine(&processes[i]);
        }
        
        nextProcess = scheduler_next_process(processes, pCount);
        process_change_status((pCtrlBlock*)context, Running);
        port_switch_context();
    }
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
    pcb->elapsedTicks = 0;
    pcb->status = Ready;
    pcb->priority = priority;
    
    port_init_context(pcb);
    port_sei();
    return pcb->pid;
}
                                               
void kernel_send(pid process, unsigned char * message, unsigned char length) {
    mailbox * mail = &processes[process].mail;
    message_send(mail, context->pid, message, length);
}

ipcMessage * kernel_receive(unsigned int wait, unsigned char* timeout) {
    ipcMessage * msg;
    context->waitTicks = wait / SYSTEM_TICK;
    msg = message_receive((mailbox *)&context->mail);
    
    if(msg == 0) *timeout = 1;
    
    context->waitTicks = 0;
    
    return msg;
}

void kernel_sleep(unsigned int time) {
    context->waitTicks = time / SYSTEM_TICK;
    kernel_wait(Sleeping);
}

void kernel_wait(pWait reason) {
    context->waitFor = reason;
    process_change_status((pCtrlBlock *)context, Waiting);
    kernel_yield();
}

void kernel_yield(void) {
    nextProcess = &scheduler;
    port_switch_context();
}
                                               
void kernel_housekeeping(void) {
    while (1) {
        ;
    }
}
