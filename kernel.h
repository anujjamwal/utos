//
//  kernel.h
//  utos
//
//  Created by Anuj Jamwal on 2/7/15.
//  Copyright (c) 2015 Anuj Jamwal. All rights reserved.
//

#ifndef __utos__kernel__
#define __utos__kernel__

typedef unsigned char pStack;

typedef void (*pCode) (void);

typedef struct {
    volatile pStack * topOfStack;
    pStack stack[100];
    pCode code;
} pCtrlBlock;

void kernel_init(void);
void kernel_start(void);
void kernel_spawn(pCode code);
void kernel_run_schedular(void);
void kernel_yield(void);

#endif /* defined(__utos__kernel__) */
