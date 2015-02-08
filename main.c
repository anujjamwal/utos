#include <avr/io.h>

#include "kernel.h"

void process1(void) {
    while(1) {
        PORTB = 0xff;
//        kernel_yield();
    }
}
void process2(void) {
    while(1) {
        PORTB = 0x00;
//        kernel_yield();
    }

}

void setup(void) {
    kernel_init();
    
    kernel_spawn(process1, 1);
    kernel_spawn(process2, 1);
    
    kernel_start();
}

int main(void) {
	setup();

	while (1) {
	}
}
