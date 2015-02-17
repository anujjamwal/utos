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


#ifdef __cplusplus
extern "C" {
#endif

    
#define Sleep(time) kernel_sleep(time)

#define Send(process, message, length) kernel_send(process, (unsigned char *)message, length)

#define Receive(block1, waitTime, block2) \
    unsigned char timeout = 0; \
    ipcMessage * msg = kernel_receive(waitTime, &timeout); \
    if(timeout == 0) \
        block1 \
    else \
        block2

/*
 * kernel_init(void)
 *
 * initializes the kernel. Creates the Os Specific processes.
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
 * kernel_receive(unsigned int wait, unsigned char* timeout)
 *
 * Read message from the mailbox.
 * The method block the process if the mailbox empty. The block timesout after the wait time and timeout flag is set
 *
 * Arguments:
 *   None
 * Return Type:
 *   ipcMessage: the received message. see kerndefs.h
 */
ipcMessage * kernel_receive(unsigned int wait, unsigned char* timeout);


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


/*
 * kernel_wait(pWait reason)
 *
 * Blocks the current process for some reason.
 * The process state is set to Waiting. In this state the scheduler checks for reason specific conditions to be met.
 * Once ready the scheduler marks the process as Ready and is run later by scheduler.
 *
 * Arguments:
 *   reason   : The reason must be one of the pWait reasons
 * Return Type:
 *   None
 */
void kernel_wait(pWait reason);
    
#ifdef __cplusplus
}
#endif

#endif /* defined(__utos__kernel__) */
