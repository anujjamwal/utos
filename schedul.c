//
//  scheduler.c
//  utos
//
//  Created by Anuj Jamwal on 2/12/15.
//  Copyright (c) 2015 Anuj Jamwal. All rights reserved.
//

#include "schedul.h"

inline pCtrlBlock * scheduler_next_process(pCtrlBlock * processes, unsigned char pCount) __attribute__((always_inline));


/*
 *  @Description
 *
 *  Scheduler Selects the process as:
 *  1. Select the Process with max priority
 *  2. For processes with same priority:
 *      -  if one process is running and other is ready, Select the ready process
 *      -  if both the processes are ready, select the process that has spent
 *         most time in ready queue
 *
 */
pCtrlBlock * scheduler_next_process(pCtrlBlock * processes, unsigned char pCount) {
    pCtrlBlock * p = 0, *t;
    unsigned char i;
    
    for(i = 0; i < pCount; i++) {
        t = &processes[i];
        
        if (t->status == Ready || t->status == TimeoutReady || t->status == Running) {
            if (p == 0) {
                p = t;
            } else if(p->priority < t->priority) {
                p = t;
            } else if(p->priority == t->priority) {
                if (p->status == Running ||  p->elapsedTicks > t->elapsedTicks) {
                    p = t;
                }
            }
        }
    }
    
    return p;
}
