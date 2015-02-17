//
//  ipc.h
//  utos
//
//  Created by Anuj Jamwal on 2/9/15.
//  Copyright (c) 2015 Anuj Jamwal. All rights reserved.
//

#ifndef utos_ipc_h
#define utos_ipc_h

#include "kconfig.h"
#include "kerndefs.h"

#ifdef __cplusplus
extern "C" {
#endif


void mailbox_init(mailbox * mail);
void message_send(mailbox * tomail, pid fromPid, unsigned char * content, unsigned char length);
ipcMessage * message_receive(mailbox * mail);
unsigned char is_empty(mailbox * mail);
unsigned char is_full(mailbox * mail);

#ifdef __cplusplus
}
#endif
    
#endif
