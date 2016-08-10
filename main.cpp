#include "mbed.h"
#include "lwip-interface/EthernetInterface.h"

#include <string>
DigitalOut led1(LED1);


using std::string;
const int BROADCAST_PORT = 58083;

int main()
{
    EthernetInterface eth;
    eth.connect();

    printf("Controller IP Address is %s\r\n", eth.get_ip_address());

    UDPSocket sock;
    sock.bind(BROADCAST_PORT);
    sock.set_broadcasting();

    SocketAddress transmit("255.255.255.255", BROADCAST_PORT);
    SocketAddress receive;

    string out_buffer = "very important data";
    char buffer[256];

    while (true)
    {
        sock.sendto(transmit, out_buffer.c_str(), out_buffer.size());

        printf("\nWait for packet...\n");
        int n = sock.recvfrom(&receive, buffer, sizeof(buffer));
        buffer[n] = '\0';
        printf("Packet from \"%s\": %s\n", receive.get_ip_address(), buffer);

        led1 = !led1;
        Thread::wait(500);
    }
}
