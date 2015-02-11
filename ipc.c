//
//  ipc.c
//  utos
//
//  Created by Anuj Jamwal on 2/8/15.
//  Copyright (c) 2015 Anuj Jamwal. All rights reserved.
//
#include "ipc.h"
#include "kernel.h"
#include "port.h"
#include "kconfig.h"

extern volatile pCtrlBlock * volatile context;
extern pCtrlBlock * processes;

void mailbox_init(mailbox * mail) {
    mail->head = 0;
    mail->tail = 0;
}

void message_send(mailbox * tomail, pid fromPid, unsigned char * content, unsigned char length) {
    ipcMessage * msg;
    unsigned char next = (unsigned char)((tomail->head + 1) % MAILBOX_SIZE);

    port_cli();

    while(next == tomail->tail) {
        // mailbox is full. Block the process till mailbox has some space
        kernel_yield();
    }
    
    
    // mailbox has room for new message
    msg = &tomail->box[tomail->head];
    msg->length = length;
    msg->senderPid = fromPid;
    
    while (length-- > 0) {
        msg->content[length] = content[length];
    }
    
    tomail->head = next;
    
    port_sei();
}

ipcMessage * message_receive(mailbox * mail) {
    ipcMessage * msg;
    unsigned char length;
    
    port_cli();

    while (mail->head == mail->tail) {
        // empty mailbox. Block the process will some message is present
        kernel_yield();
    }
    
    // mailbox has message
    msg = &mail->box[mail->tail];
    length = mail->curr.length = msg->length;
    mail->curr.senderPid = msg->senderPid;
    
    while (length-- > 0) {
        mail->curr.content[length] = msg->content[length];
    }
    
    mail->tail = (unsigned char)(mail->tail + 1) % MAILBOX_SIZE;
    
    port_sei();
    return &mail->curr;
}
