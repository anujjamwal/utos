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
    process->elapsedTicks++;
    
    switch (process->status) {
        case Running:
            process_change_status(process, Ready);
            break;
            
        case Sleeping:
            if(process->waitTicks <= process->elapsedTicks)
                process_change_status(process, Ready);
            
            break;
            
        case Waiting:
            
            switch (process->waitFor) {
                case MsgSend:
                    if (is_full(process->mail.outMail) == 0) {
                        process_change_status(process, Ready);
                    }
                    break;
                    
                case MsgReceive:
                    if (is_empty(&process->mail) == 0) {
                        process_change_status(process, Ready);
                    }
                    break;
                    
                default:
                    break;
            }
            
            break;
            
        default:
            break;
    }
}

void process_change_status(pCtrlBlock * process, pStatus status) {
    if (process->status != status) {
        process->elapsedTicks = 0;
        
        if (process->status == Sleeping) {
            process->waitTicks = 0;
        }
    }
    
    process->status = status;
}
