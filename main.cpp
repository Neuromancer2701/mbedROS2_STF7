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
    string out_buffer = "very important data";
    SocketAddress transmit("192.168.1.159", BROADCAST_PORT_T);

    while (true)
    {
        int ret = socket.sendto(transmit, out_buffer.c_str(), out_buffer.size());
        printf("sendto return: %d\n", ret);

        Thread::wait(5000);
    }
}

void receive()
{
    SocketAddress receive;
    UDPSocket socket(&eth);
    int bind = socket.bind(BROADCAST_PORT_R);
    printf("bind return: %d\n", bind);

    char buffer[256];
    while (true)
    {
        printf("\nWait for packet...\n");
        int n = socket.recvfrom(&receive, buffer, sizeof(buffer));
        buffer[n] = '\0';
        printf("Packet from \"%s\": %s\n", receive.get_ip_address(), buffer);

        Thread::wait(500);
    }
}


int main()
{
    Thread transmitter;
    Thread receiver;
    eth.connect();

    printf("Controller IP Address is %s\r\n", eth.get_ip_address());
    Thread::wait(5000);

    transmitter.start(transmit);
    receiver.start(receive);

    while (true)
    {
        led1 = !led1;
        Thread::wait(500);
    }
}
