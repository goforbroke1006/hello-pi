//
// Created by goforbroke on 18.05.2021.
//

// mkdir -p ./cmake-build-debug/src/00-flash-led-test/
// gcc -lstdc++ ./src/00-flash-led-test/main.cpp -o ./cmake-build-debug/src/00-flash-led-test/00-flash-led-test
// echo 26 > /sys/class/gpio/unexport
// sudo ./cmake-build-debug/src/00-flash-led-test/00-flash-led-test

#define MY_GPIO_OUTPUT_BCM 26

#include "../myGPIO.h"

int main() {

    myGPIO::gpioExport(MY_GPIO_OUTPUT_BCM);

    // Set the pin to be an output by writing "out" to /sys/class/gpio/gpio26/direction
    myGPIO::gpioDirection(MY_GPIO_OUTPUT_BCM, myGPIO::GPIODirection::OUT);

    // Toggle LED 50 ms on, 50ms off, 100 times (10 seconds)
    for (int i = 0; i < 100; i++) {
        myGPIO::gpioValue(MY_GPIO_OUTPUT_BCM, myGPIO::ONE);
        usleep(50000);

        myGPIO::gpioValue(MY_GPIO_OUTPUT_BCM, myGPIO::ZERO);
        usleep(50000);
    }

    // Unexport the pin by writing to /sys/class/gpio/unexport
    myGPIO::gpioUnexport(MY_GPIO_OUTPUT_BCM);

    // And exit
    return 0;
}
