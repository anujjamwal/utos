//
//  kconfig.h
//  utos
//
//  Created by Anuj Jamwal on 2/7/15.
//  Copyright (c) 2015 Anuj Jamwal. All rights reserved.
//

#ifndef utos_kconfig_h
#define utos_kconfig_h

#define PROCESS_COUNT 3
#define PROCESS_STACK_SIZE 100

// the length of a tick in milliseconds
#define SYSTEM_TICK 1
#define F_CPU 16000000ul

#define NUM_INSTRUCTION F_CPU*SYSTEM_TICK/1000

#endif
