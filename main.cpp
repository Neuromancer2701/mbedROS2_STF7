#include "mbed.h"

DigitalOut led1(LED1);

const int BROADCAST_PORT = 58083;

int main()
{
    while (true)
    {
        led1 = !led1;
        Thread::wait(500);
    }
}


#if 0
// main() runs in its own thread in the OS
// (note the calls to Thread::wait below for delays)
int main()
{

    EthernetInterface eth;
    eth.connect();

    printf("Controller IP Address is %s\r\n", eth.get_ip_address());

    UDPSocket sock;
    sock.init();
    sock.bind(BROADCAST_PORT);
    sock.set_broadcasting();

    Endpoint transmit;
    Endpoint receive;
    receive.set_address("255.255.255.255", BROADCAST_PORT);

    char out_buffer[] = "very important data";
    char buffer[256];

    while (true)
    {
        sock.sendTo(transmit, out_buffer, sizeof(out_buffer));

        printf("\nWait for packet...\n");
        int n = sock.receiveFrom(receive, buffer, sizeof(buffer));
        buffer[n] = '\0';
        printf("Packet from \"%s\": %s\n", receive.get_address(), buffer);

        led1 = !led1;
        Thread::wait(500);
    }
}

#endif

