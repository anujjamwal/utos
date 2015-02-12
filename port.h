//
//  port.h
//  utos
//
//  Created by Anuj Jamwal on 2/9/15.
//  Copyright (c) 2015 Anuj Jamwal. All rights reserved.
//

#ifndef utos_port_h
#define utos_port_h

#include "kernel.h"

// functions to be ported by individual platform code
void port_setup_timer(void);
void port_start_timer(void);
void port_init_context(pCtrlBlock * pcb);
void port_sei(void);
void port_cli(void);
void port_switch_context(void);

#endif
