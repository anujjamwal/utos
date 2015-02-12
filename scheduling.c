//
//  scheduler.c
//  utos
//
//  Created by Anuj Jamwal on 2/12/15.
//  Copyright (c) 2015 Anuj Jamwal. All rights reserved.
//

#include "scheduling.h"

inline pCtrlBlock * scheduler_next_process(pCtrlBlock * processes, unsigned char pCount) __attribute__((always_inline));

pCtrlBlock * scheduler_next_process(pCtrlBlock * processes, unsigned char pCount) {
    pCtrlBlock * p = 0, *t;
    unsigned char i;
    
    for(i = 1; i < pCount; i++) {
        t = &processes[i];
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
        p = &processes[0];
    }
    
    return p;
}
