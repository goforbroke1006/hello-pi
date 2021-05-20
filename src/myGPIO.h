//
// Created by goforbroke on 19.05.2021.
//

#ifndef HELLO_PI_MYGPIO_H
#define HELLO_PI_MYGPIO_H

#include <string>
#include <cstdio>    // perror() open()
#include <fcntl.h>   // O_WRONLY
#include <unistd.h>  // write() exit()
#include <cstdlib>   // exit()
#include <stdexcept> // logic_error()

namespace myGPIO {
    int __openFD(const std::string &filename) {
        int fd = open(filename.c_str(), O_WRONLY);
        if (fd == -1) {
            std::string err = std::string("Unable to open ") + filename;
            perror(err.c_str());
            return -1;
        }
        return fd;
    }

    void gpioExport(int bcm) {
        int fd = __openFD("/sys/class/gpio/export");
        if (fd == -1) {
            throw std::logic_error("GPIO export problem");
        }

        const std::string &phrase = std::to_string(bcm);
        if (write(fd, phrase.c_str(), phrase.length()) != phrase.length()) {
            perror("Error writing to /sys/class/gpio/export");
            close(fd);
            throw std::logic_error("GPIO export problem");
        }

        close(fd);
    }

    enum GPIODirection {
        IN, OUT
    };

    void gpioDirection(int bcm, GPIODirection direction) {

        std::string directionFile = std::string("/sys/class/gpio/gpio") + std::to_string(bcm) + "/direction";
        int fd = __openFD(directionFile.c_str());
        if (fd == -1) {
            throw std::logic_error("GPIO direction problem");
        }

        std::string phrase;
        if (direction == GPIODirection::OUT)
            phrase = "out";
        else
            phrase = "in";

        if (write(fd, phrase.c_str(), phrase.length()) != phrase.length()) {
            perror("Error writing");
            close(fd);
            throw std::logic_error("GPIO direction problem");
        }

        close(fd);
    }

    enum GPIOValue {
        ONE, ZERO
    };

    void gpioValue(int bcm, GPIOValue value) {
        std::string valueFile = std::string("/sys/class/gpio/gpio") + std::to_string(bcm) + "/value";
        int fd = __openFD(valueFile.c_str());
        if (fd == -1) {
            throw std::logic_error("GPIO value problem");
        }

        std::string phrase;
        if (value == ONE) {
            phrase = "1";
        } else
            phrase = "0";

        if (write(fd, phrase.c_str(), phrase.length()) != phrase.length()) {
            perror("Error writing");
            close(fd);
            throw std::logic_error("GPIO value problem");
        }

        close(fd);
    }

    void gpioUnexport(int bcm) {
        int fd = __openFD("/sys/class/gpio/unexport");
        if (fd == -1) {
            throw std::logic_error("GPIO unexport problem");
        }

        const std::string &phrase = std::to_string(bcm);

        if (write(fd, phrase.c_str(), phrase.length()) != phrase.length()) {
            perror("Error writing to /sys/class/gpio/unexport");
            close(fd);
            throw std::logic_error("GPIO unexport problem");
        }

        close(fd);
    }
}

#endif //HELLO_PI_MYGPIO_H
