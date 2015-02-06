# µtos
A Real Time Operating System

The Project comes about as my attempt to create a minimal Real Time Operating System. It currently supports AVR but aims to support multiple mcus.
The project also aims to provide well defined hardware and device abstractions to assist easy building of future embedded system projects.

The RTOS aims to 
* Preemptive Scheduling of process
* Response time guarantee per task over fixed priority
* Block Waiting of process for some hardware
* Block Waiting for delays
