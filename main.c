#include <avr/io.h>

#include "kernel.h"

pid p1, p2, p3;

void process1(void) {
    char * m = "0";
    PORTC = 0x00;
    
    
    while(1) {
        
        Send(p2, m, 1);
        m[0] ++;
        Sleep(2);
    }
}

void process2(void) {
    PORTB = 0x00;
    
    while(1) {
        Receive({
            PORTB = msg->content[0];
        }, 100, {
            PORTC ^= 0x11;
        });
    }
}

void setup(void) {
    kernel_init();
    
    p1 = kernel_spawn(process1, Med);
    p2 = kernel_spawn(process2, High);
    
    kernel_start();
}

int main(void) {
	setup();

	while (1) {
	}
}
