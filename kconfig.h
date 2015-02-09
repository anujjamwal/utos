//
//  kconfig.h
//  utos
//
//  Created by Anuj Jamwal on 2/7/15.
//  Copyright (c) 2015 Anuj Jamwal. All rights reserved.
//

#ifndef utos_kconfig_h
#define utos_kconfig_h

#define PROCESS_COUNT 2
#define PROCESS_STACK_SIZE 100

/*
 * Every message has a mailbox used to receive messages from other processes.
 * Kernel as of now supports fixed size messages and a fixed lenght mailbox.
 */
#define USE_MAILBOX 1
#define MESSAGE_SIZE 10
#define MAILBOX_SIZE 5

// the length of a tick in milliseconds
#define SYSTEM_TICK 1
#define F_CPU 16000000ul

#define NUM_INSTRUCTION F_CPU*SYSTEM_TICK/1000

#endif
