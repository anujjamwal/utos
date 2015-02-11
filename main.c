#include <avr/io.h>

#include "kernel.h"

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
    
    p1 = kernel_spawn(process1, Med);
    p2 = kernel_spawn(process2, Med);
    
    kernel_start();
}

int main(void) {
	setup();

	while (1) {
	}
}
