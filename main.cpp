
#include "mbed.h"
#include "rtos.h"

#include <string>
#include <array>

using std::string;
using std::array;

DigitalOut led1(LED1);

PwmOut     Speed(D5);       //purple
DigitalOut Direction(D4);   //white
DigitalOut Brake(D3);       //orange


DigitalIn Hall1(PC_9);
DigitalIn Hall2(PB_8);
DigitalIn Hall3(PB_9);

enum constants
{
    Hall1_shift = 8,
    Hall2_shift = 5,
    Hall3_shift = 6,
    HallOutMask = 0x0160,  //pins 8, 6 and 5

};
//PortOut HallOut(PortC, HallOutMask);

array<int, 8> lookup = {0, 0, 0, 0, 0, 0, 0, 0};

static volatile unsigned halls_index = 0;


void processHalls()
{
    while (true)
    {
        unsigned hall1 = Hall1.read();
        unsigned hall2 = Hall2.read();
        unsigned hall3 = Hall3.read();

        halls_index  = hall1 << 2;
        halls_index |= hall2 << 1;
        halls_index |= hall3;

        printf("Hall sensors: %01X \r\n", halls_index);
    }
}


int main()
{
    Thread halls;

    halls.start(processHalls);

    printf("Hello, World!!!! \n");

    Direction = 1;
    Brake = 1;

    Speed.period_us(50); // 20khz
    Speed.write(0.50);    // 50% duty cycle


    while (true)
    {
        led1 = !led1;
        Thread::wait(1000);
    }
}
