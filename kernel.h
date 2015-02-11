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


/*
 * kernel_init(void)
 *
 * initializes the kernel.
 *
 * Arguments:
 *   None
 * Return Type:
 *   None
 */
void kernel_init(void);


/*
 * kernel_start(void)
 *
 * starts the kernel and system ticker.
 *
 * Arguments:
 *   None
 * Return Type:
 *   None
 */
void kernel_start(void);


/*
 * kernel_spawn(pCode code, unsigned int time)
 *
 * executes the scheduling code.
 * The method should not be executed from user code
 *
 * Arguments:
 *   code    : process function to be executed
 *   priority: the process priority
 * Return Type:
 *   pid : returns the pid of the process
 */
pid kernel_spawn(pCode code, pPriority priority);


/*
 * kernel_run_scheduler(void)
 *
 * executes the scheduling code.
 * The method should not be executed from user code
 *
 * Arguments:
 *   None
 * Return Type:
 *   None
 */
void kernel_run_scheduler(void);


/*
 * kernel_yield(void)
 * 
 * yields the processor and invokes the schedular to run another process
 * The method blocks the process
 *
 * Arguments:
 *   None
 * Return Type:
 *   None
 */
void kernel_yield(void);


#ifdef USE_MAILBOX

/*
  * kernel_send(pid process, unsigned char * message, unsigned char length)
  *
  * Send message to a process.
  * The method block the process if the mailbox of receiving process is already full.
  *
  * Arguments:
  *   toProcess: pid of the receiving process
  *   message  : the byte array of message to be passed
  *   length   :  the length of the passed message. The length should be less than the max length specified in kconfig.h under MESSAGE_SIZE param
  * Return Type:
  *   None
 */
void kernel_send(pid toProcess, unsigned char * message, unsigned char length);


 /*
  * kernel_receive()
  *
  * Read message from the mailbox.
  * The method block the process if the mailbox empty.
  *
  * Arguments:
  *   None
  * Return Type:
  *   ipcMessage: the received message. see kerndefs.h
 */
ipcMessage * kernel_receive(void);


/*
 * kernel_sleep(unsigned int time)
 *
 * Puts a process on sleep for atleast the given time
 *
 * Arguments:
 *   time   : The number of milliseconds to yield the processor
 * Return Type:
 *   None
 */
void kernel_sleep(unsigned int time);

#endif

#endif /* defined(__utos__kernel__) */
