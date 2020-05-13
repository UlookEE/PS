#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <wiringPi.h>

#define GPIO_TRIGGER 4  // BCM 23
#define GPIO_ECHO 5     // BCM 24
#define GPIO_LED 6      // BCM 25, pys 22

int main() {
    unsigned int start, stop;
    int loop = 0, count;
    float f;

    printf("Starting HC-SR04 test\n");
    int status = wiringPiSetup();
    if (status != 0) {
        printf("Failed to wiringPiSetupGpio()\n");
        return 0;
    }
    pinMode(GPIO_TRIGGER, OUTPUT);
    pinMode(GPIO_ECHO, INPUT);
    pinMode(GPIO_LED, OUTPUT);

    digitalWrite(GPIO_TRIGGER, LOW);
    delay(500);

    while (1) {
        printf("loop start\n");
        digitalWrite(GPIO_TRIGGER, HIGH);
        delayMicroseconds(10);
        digitalWrite(GPIO_TRIGGER, LOW);
        while (digitalRead(GPIO_ECHO) == LOW) {
            // do nothong
        }
        start = micros();
        while (digitalRead(GPIO_ECHO) == HIGH) {
            // do nothing
        }
        stop = micros();

        double distance = 34029 * (stop - start) / 2000000.0;
        printf("Distance: %f cm\n", distance);
        if (distance > 10.0) {
            digitalWrite(GPIO_LED, HIGH);
        } else {
            digitalWrite(GPIO_LED, LOW);
        }
        delay(1000);
        if (loop++ == 100)
            break;
    }
    digitalWrite(GPIO_LED, LOW);
    digitalWrite(GPIO_TRIGGER, LOW);

    return 0;
}
