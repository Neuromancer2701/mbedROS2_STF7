#include "mbed.h"
#include "EthernetInterface.h"

DigitalOut led1(LED1);

// main() runs in its own thread in the OS
// (note the calls to Thread::wait below for delays)
int main()
{

    EthernetInterface eth;
    eth.connect();

    printf("TCP client IP Address is %s\r\n", eth.get_ip_address());

    while (true)
    {
        led1 = !led1;
        Thread::wait(500);
    }
}

