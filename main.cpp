#include "mbed.h"
#include "lwip-interface/EthernetInterface.h"

#include <string>
DigitalOut led1(LED1);


using std::string;
const int BROADCAST_PORT = 58083;



UDPSocket socket_g;

void transmit()
{
    string out_buffer = "very important data";
    SocketAddress transmit("255.255.255.255", BROADCAST_PORT);

    while (true)
    {
        socket_g.sendto(transmit, out_buffer.c_str(), out_buffer.size());
        Thread::wait(500);
    }
}

void receive()
{
    SocketAddress receive;
    char buffer[256];
    while (true)
    {
        printf("\nWait for packet...\n");
        int n = socket_g.recvfrom(&receive, buffer, sizeof(buffer));
        if (n > 0)
        {
            buffer[n] = '\0';
            printf("Packet from \"%s\": %s\n", receive.get_ip_address(), buffer);
        }
        Thread::wait(500);
    }
}


int main()
{
    Thread transmitter;
    Thread receiver;
    EthernetInterface eth;
    eth.connect();

    printf("Controller IP Address is %s\r\n", eth.get_ip_address());

    socket_g.bind(BROADCAST_PORT);
    socket_g.set_broadcasting();
    transmitter.start(transmit);
    receiver.start(receive);

    while (true)
    {
        led1 = !led1;
        Thread::wait(500);
    }
}
