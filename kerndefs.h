//
//  kerndefs.h
//  utos
//
//  Created by Anuj Jamwal on 2/9/15.
//  Copyright (c) 2015 Anuj Jamwal. All rights reserved.
//

#ifndef utos_kerndefs_h
#define utos_kerndefs_h

#include "kconfig.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef enum {Running, Waiting, Ready} pStatus;
typedef enum {VLow, Low, Med, High, VHigh} pPriority;
typedef enum {MsgSend, MsgReceive, Sleeping} pWait;

typedef unsigned char pStack;
typedef unsigned char pid;

typedef void (*pCode) (void);

typedef struct {
    unsigned char length;
    pid senderPid;
    unsigned char content[MESSAGE_SIZE];
} ipcMessage;

typedef struct mailbox_ {
    ipcMessage curr;
    ipcMessage box[MAILBOX_SIZE];
    volatile unsigned char head;
    volatile unsigned char tail;
    struct mailbox_ * outMail;
} mailbox;


typedef struct {
    volatile pStack * topOfStack;
    pid pid;
    pStack stack[PROCESS_STACK_SIZE];
    pCode code;
    
    pPriority priority;
    pWait waitFor;
    
    unsigned int waitTicks;
    volatile pStatus status;
    volatile unsigned int elapsedTicks;
    
    mailbox mail;
    
} pCtrlBlock;
    
    
#ifdef __cplusplus
}
#endif


#endif

