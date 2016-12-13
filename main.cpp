#include "mbed.h"
#include "lwip-interface/EthernetInterface.h"

#include <string>
#include <array>

using std::string;
using std::array;

DigitalOut led1(LED1);

PwmOut     Speed(D5);       //purple
DigitalOut Direction(D4);   //white
DigitalOut Brake(D3);       //orange

InterruptIn Hall1(PC_9);
InterruptIn Hall2(PB_8);
InterruptIn Hall3(PB_9);

enum constants
{
    Hall1_shift = 8,
    Hall2_shift = 5,
    Hall3_shift = 6,
    HallOutMask = 0x0160,  //pins 8, 6 and 5

};
//PortOut HallOut(PortC, HallOutMask);

int hall1 = 0;
int hall2 = 0;
int hall3 = 0;


array<int, 8> lookup = {0, 0, 0, 0, 0, 0, 0, 0};

static volatile unsigned halls_index = 0;
const int BROADCAST_PORT = 58000;
//const int BROADCAST_PORT_R = 58081;
EthernetInterface eth;


void enableHalls(bool enable)
{
    if(enable)
    {
        Hall1.enable_irq();
        Hall2.enable_irq();
        Hall3.enable_irq();
    }
    else
    {
        Hall1.disable_irq();
        Hall2.disable_irq();
        Hall3.disable_irq();
    }
}

void processHalls()
{
    enableHalls(false);

    unsigned hall1 = Hall1.read();
    unsigned hall2 = Hall2.read();
    unsigned hall3 = Hall3.read();

    halls_index  = hall1 << 2;
    halls_index |= hall2 << 1;
    halls_index |= hall3;

    //HallOut.write(lookup.at(halls_index));
    enableHalls(true);
}


void transmit()
{
    UDPSocket socket(&eth);
    string out_buffer = "very important data";
    SocketAddress transmit("255.255.255.255", BROADCAST_PORT);
    int bind = socket.bind(BROADCAST_PORT);
    printf("bind return: %d\n", bind);

    while (true)
    {
        int ret = socket.sendto(transmit, out_buffer.c_str(), out_buffer.size());
        printf("sendto return: %d \r\n", ret);

        Thread::wait(5000);
    }
}

void receive()
{
    SocketAddress receive;
    UDPSocket socket(&eth);
    int bind = socket.bind(BROADCAST_PORT);
    printf("bind return: %d\n", bind);

    char buffer[256];
    while (true)
    {
        printf("\nWait for packet...\r\n");
        int n = socket.recvfrom(&receive, buffer, sizeof(buffer));
        buffer[n] = '\0';
        printf("Packet from \"%s\": %s\r\n", receive.get_ip_address(), buffer);

        Thread::wait(500);
    }
}


int main()
{
    //Thread transmitter;
    //Thread receiver;
    //eth.connect();

    //printf("Controller IP Address is %s\r\n", eth.get_ip_address());
    //Thread::wait(5000);

   //transmitter.start(transmit);
    //receiver.start(receive);

    printf("Hello, World!!!! \n");

    Hall1.rise(processHalls);
    Hall1.fall(processHalls);

    Hall2.rise(processHalls);
    Hall2.fall(processHalls);

    Hall3.rise(processHalls);
    Hall3.fall(processHalls);

    Direction = 1;
    Brake = 1;

    Speed.period_us(50); // 20khz
    Speed.write(0.50);    // 50% duty cycle


    while (true)
    {
        led1 = !led1;
        Thread::wait(10);

        printf("Hall sensors: %01X \r\n", halls_index);

    }
}
