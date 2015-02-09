# µtos
A Real Time Operating System

The Project comes about as my attempt to create a minimal Real Time Operating System. It currently supports AVR but aims to support multiple mcus.
The project also aims to provide well defined hardware and device abstractions to assist easy building of future embedded system projects.

The RTOS aims to 
* Preemptive Scheduling of process
* Response time guarantee per task over fixed priority
* Block Waiting of process for some hardware
* Block Waiting for delays

## Example:
Define the process count in kconfig.h as PROCESS_COUNT

```c
#include <avr/io.h>
#include "kernel.h"

void process1(void) {
    while(1) {
        PORTB = 0xff;
        kernel_yield();
    }
}
void process2(void) {
    while(1) {
        PORTB = 0x00;
        kernel_yield();
    }

}

void setup(void) {
    kernel_init();
    
    kernel_spawn(process1);
    kernel_spawn(process2);
    
    kernel_start();
}

int main(void) {
	setup();

	while (1) {
	}
}
```

## Message Passing
utos message passing is inspired from erlang style message passing.
The example below shows the implementation of a synchronized producer consumer
processes.

```c
pid p1, p2;

void process1(void) {
  char * m = "0";
  PORTC = 0x00;

  while(1) {
    kernel_send(p2, (unsigned char *)m, 1);
    m[0] ++;
    kernel_yield();
  }
}

void process2(void) {
  ipcMessage * msg;
  
  PORTB = 0x00;
	                
  while(1) {
    msg = kernel_receive();
    PORTB = msg->content[0];
  }
}

void setup(void) {
  kernel_init();
  p1 = kernel_spawn(process1, 1);
  p2 = kernel_spawn(process2, 1);
	                    
  kernel_start();
}

int main(void) {
  setup();

  while (1) {
  }
}

```
