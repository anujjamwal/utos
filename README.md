# µtos
A Real Time Operating System

The Project comes about as my attempt to create a minimal Real Time Operating System. It currently supports AVR but aims to support multiple mcus.
The project also aims to provide well defined hardware and device abstractions to assist easy building of future embedded system projects.

The RTOS aims to 
* Preemptive Scheduling of process
* Block Waiting of process for some hardware
* Block Process for delays

## Example:
Define the process count in kconfig.h as PROCESS_COUNT

```c
#include <avr/io.h>
#include "kernel.h"

void process1(void) {
    while(1) {
        PORTB = 0xff;
        Sleep(1);
    }
}
void process2(void) {
    while(1) {
        PORTB = 0x00;
        Sleep(1);
    }

}

void setup(void) {
    kernel_init();
    
    kernel_spawn(process1, Med);
    kernel_spawn(process2, Med);
    
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
    Send(p2, m, 1);
    m[0] ++;
    Sleep(3);
  }
}

void process2(void) {
  PORTB = 0x00;
	                
  while(1) {
    Receive({
        // msg of type ipcMessage* is available here
        PORTB = msg->content[0];
    }, 1000, {
    	// executed on timeout
    });
  }
}

void setup(void) {
  kernel_init();
  p1 = kernel_spawn(process1, Med);
  p2 = kernel_spawn(process2, Med);
	                    
  kernel_start();
}

int main(void) {
  setup();

  while (1) {
  }
}

```
