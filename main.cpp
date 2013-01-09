#include <stdlib.h>
#include <string.h>
#include <wirish/wirish.h>

#define TILT_PIN 6
#define PAN_PIN  5
#define BUFFER_SIZE 12
#define LAST_BUFFER_POSITION BUFFER_SIZE - 1
#define COMMAND_TERMINATOR ';'

char cmd[BUFFER_SIZE];

inline void tilt(int value) {
    pwmWrite(TILT_PIN, value);
}

inline void pan(int value) {
    pwmWrite(PAN_PIN, value);
}

void setup() {
    /* Turn on PWM */
    pinMode(TILT_PIN, PWM);
    pinMode(PAN_PIN, PWM);

    /* Set initial tilt and pan */
    tilt(0);
    pan(0);
}

void loop() {
    char c = 0;
    int i = 0;

    memset(cmd, 0, BUFFER_SIZE);

    while(c != COMMAND_TERMINATOR  && i < LAST_BUFFER_POSITION) {
        if(SerialUSB.available()) {
            c = SerialUSB.read();
            cmd[i++] = c;
        }
    }

    if(c != COMMAND_TERMINATOR && i == LAST_BUFFER_POSITION) {
        // buffer is full, but we didn't get full command
        return;
    }

    // change command terminator to zero byte to mark end of string
    cmd[i] = 0;

    // very primitive command parsing
    if(cmd[0] == 'P' && cmd[1] == 'A' && cmd[2] == 'N') {
      pan(atoi(&cmd[4]));
    } else if(cmd[0] == 'T' && cmd[1] == 'I' && cmd[2] == 'L' && cmd[3] == 'T') {
      tilt(atoi(&cmd[5]));
    }
}

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need libmaple may fail.
__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    setup();

    while (true) {
        loop();
    }

    return 0;
}
