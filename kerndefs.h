//
//  kerndefs.h
//  utos
//
//  Created by Anuj Jamwal on 2/9/15.
//  Copyright (c) 2015 Anuj Jamwal. All rights reserved.
//

#ifndef utos_kerndefs_h
#define utos_kerndefs_h

typedef enum {Running, Waiting, Ready, Blocked, Sleeping} pStatus;

typedef unsigned char pStack;
typedef unsigned char pid;

typedef void (*pCode) (void);

#ifdef USE_MAILBOX

typedef struct {
    unsigned char length;
    pid senderPid;
    unsigned char content[MESSAGE_SIZE];
} ipcMessage;

typedef struct {
    ipcMessage curr;
    ipcMessage box[MAILBOX_SIZE];
    volatile unsigned char head;
    volatile unsigned char tail;
} mailbox;
#endif


typedef struct {
    volatile pStack * topOfStack;
    pid pid;
    pStack stack[PROCESS_STACK_SIZE];
    pCode code;
    
    
    unsigned int waitTicks;
    volatile pStatus status;
    volatile unsigned int elapsedTicks;
    
#ifdef USE_MAILBOX
    mailbox mail;
#endif
    
} pCtrlBlock;
#endif
