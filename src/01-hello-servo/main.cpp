//
// Created by goforbroke on 18.05.2021.
//

// g++ -Ofast -Wall src/01-hello-servo/main.cpp -lpigpio -o 01-hello-servo
// sudo ./01-hello-servo

#include <cstdio>  // printf()
#include <cstdlib> // EXIT_FAILURE

#include <pigpio.h>
#include "../pigpio.h" // stub for code highlighting

int main() {
    // Red LED: Physical pin 11, BCM GPIO17, and WiringPi pin 0.
    int servoGpioPin = 17;

    printf("Raspberry Pi pigpio (version=%d) test program for GPIO=%d\n", gpioVersion(), servoGpioPin);
    if (gpioInitialise() < 0) {
        perror("  gpioInitialise() failed");
        exit(EXIT_FAILURE);
    }

    if (gpioSetMode(servoGpioPin, PI_OUTPUT) != 0) {
        perror("  gpioSetMode() failed");
        exit(EXIT_FAILURE);
    }

    gpioServo(servoGpioPin, 500); // move to init position
    time_sleep(1);

    for (int angle = 500; angle <= 2500; ++angle) {
        gpioServo(servoGpioPin, angle);
        time_sleep(0.005);
    }

    /* Stop DMA, release resources */
    gpioTerminate();

    return 0;
}