//
//  process.h
//  utos
//
//  Created by Anuj Jamwal on 2/11/15.
//  Copyright (c) 2015 Anuj Jamwal. All rights reserved.
//

#ifndef __utos__process__
#define __utos__process__

#include "kerndefs.h"

void process_run_state_machine(pCtrlBlock * process);
void process_change_status(pCtrlBlock * process, pStatus status);

#endif /* defined(__utos__process__) */
