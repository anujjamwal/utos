//
//  process.c
//  utos
//
//  Created by Anuj Jamwal on 2/11/15.
//  Copyright (c) 2015 Anuj Jamwal. All rights reserved.
//

#include "process.h"
#include "ipc.h"

void process_run_state_machine(pCtrlBlock * process) {
    // Increment the elapsed time of the process in the given state
    process->elapsedTicks++;
    
    switch (process->status) {
        case Running:
            break;
            
        case Waiting:
            switch (process->waitFor) {
                case MsgSend:
                    if (!is_full(process->mail.outMail)) {
                        process_change_status(process, Ready);
                    }
                    break;
                    
                case MsgReceive:
                    if (!is_empty(&process->mail)) {
                        process_change_status(process, Ready);
                    } else if(process->waitTicks <= process->elapsedTicks) {
                        process_change_status(process, TimeoutReady);
                    }
                    break;
                    
                case Sleeping:
                    if(process->waitTicks <= process->elapsedTicks) {
                        process_change_status(process, Ready);
                    }
                    break;
            }
            break;
        
        case Ready:
            break;
            
        case TimeoutReady:
            break;
            
    }
}

void process_change_status(pCtrlBlock * process, pStatus status) {
    if (process->status != status) {
        process->elapsedTicks = 0;
        
        if (process->status == Waiting) {
            process->waitTicks = 0;
        }
    }
    
    process->status = status;
}
