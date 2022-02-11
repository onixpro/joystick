#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>
   
    typedef struct joystick {
        int JR_X;
        int JR_Y;
        int JR_B;

        int JL_X;
        int JL_Y;
        int JL_B;
    };
    const byte address[6] = "00001";
    const int payload_size = 12;