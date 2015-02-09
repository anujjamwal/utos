//
//  kernel.h
//  utos
//
//  Created by Anuj Jamwal on 2/7/15.
//  Copyright (c) 2015 Anuj Jamwal. All rights reserved.
//

#ifndef __utos__kernel__
#define __utos__kernel__

#include "kconfig.h"
#include "kerndefs.h"

void kernel_init(void);
void kernel_start(void);
pid kernel_spawn(pCode code, unsigned int time);
void kernel_run_scheduler(void);
void kernel_yield(void);

#ifdef USE_MAILBOX
void kernel_send(pid process, unsigned char * message, unsigned char length);
ipcMessage * kernel_receive(void);
#endif

#endif /* defined(__utos__kernel__) */
