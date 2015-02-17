//
//  scheduler.h
//  utos
//
//  Created by Anuj Jamwal on 2/12/15.
//  Copyright (c) 2015 Anuj Jamwal. All rights reserved.
//

#ifndef __utos__scheduling__
#define __utos__scheduling__

#include "kerndefs.h"

pCtrlBlock * scheduler_next_process(pCtrlBlock * processes, unsigned char pCount);

#endif /* defined(__utos__scheduling__) */
