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


#ifdef __cplusplus
extern "C" {
#endif


pCtrlBlock * scheduler_next_process(pCtrlBlock * processes, unsigned char pCount);

    
#ifdef __cplusplus
}
#endif

    
#endif /* defined(__utos__scheduling__) */
