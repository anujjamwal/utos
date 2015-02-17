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

inline void mailbox_init(mailbox * mail) __attribute__((always_inline));
void mailbox_init(mailbox * mail) {
    mail->head = 0;
    mail->tail = 0;
}

unsigned char is_empty(mailbox * mail) {
    return mail->head == mail->tail;
}

unsigned char is_full(mailbox * mail) {
    unsigned char next = (unsigned char)((mail->head + 1) % MAILBOX_SIZE);
    return next == mail->tail;
}

void message_send(mailbox * tomail, pid fromPid, unsigned char * content, unsigned char length) {
    ipcMessage * msg;
    unsigned char next = (unsigned char)((tomail->head + 1) % MAILBOX_SIZE);
    
    port_cli();
    context->mail.outMail = tomail;
    
    while (is_full(tomail)) {
        // mailbox is full. Block the process till mailbox has some space
        kernel_wait(MsgSend);
    }
    port_cli();
        
    // mailbox has room for new message
    msg = &tomail->box[tomail->head];
    msg->length = length;
    msg->senderPid = fromPid;
    
    while (length-- > 0) {
        msg->content[length] = content[length];
    }
    
    tomail->head = next;
    
    context->mail.outMail = 0;
    
    port_sei();
}

ipcMessage * message_receive(mailbox * mail) {
    ipcMessage * msg;
    unsigned char length;
    
    port_cli();

    while (is_empty(mail)) {
        // empty mailbox. Block the process will some message is present
        kernel_wait(MsgReceive);
    }
    port_cli();
    
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
