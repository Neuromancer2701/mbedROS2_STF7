#include "mbed.h"
#include "lwip-interface/EthernetInterface.h"

#include <string>
DigitalOut led1(LED1);


using std::string;
const int BROADCAST_PORT_T = 58080;
const int BROADCAST_PORT_R = 58081;
EthernetInterface eth;



void transmit()
{
    UDPSocket socket(&eth);
    socket.set_broadcasting();
    string out_buffer = "very important data";
    SocketAddress transmit("255.255.255.255", BROADCAST_PORT_T);

    while (true)
    {
        int ret = socket.sendto(transmit, out_buffer.c_str(), out_buffer.size());

        printf("sendto return: %d\n", ret);
        Thread::wait(500);
    }
}

void receive()
{
    SocketAddress receive("255.255.255.0", BROADCAST_PORT_R);
    UDPSocket socket(&eth);

    socket.bind(BROADCAST_PORT_R);
    socket.set_broadcasting();

    char buffer[256];
    while (true)
    {
        printf("\nWait for packet...\n");
        int n = socket.recvfrom(&receive, buffer, sizeof(buffer));
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
    eth.connect();

    printf("Controller IP Address is %s\r\n", eth.get_ip_address());

    transmitter.start(transmit);
    //receiver.start(receive);

    while (true)
    {
        led1 = !led1;
        Thread::wait(500);
    }
}
