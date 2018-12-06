#include <stdio.h>

#ifndef ACE3_HARDWARE_H
#define ACE3_HARDWARE_H

void computer_initializer();

typedef struct {
    char memory[4096][17];  // A two dimension char array representation of memory. Contains 4096 16 bit words.
    char ac[17];            // Accumulator : 16 bits - Twos compliment
    char ir[17];            // Input register : 16 bits - Twos compliment
    char mbr[17];           // Memory Buffer register : 16 bits
    char in_reg[17];        // The input register, which holds data from the input device.
    char out_reg[17];       // The output register, which holds data for the output device.
    char pc[13];            // Program counter : 12 bits - Unsigned Binary
    char mar[13];           // Memory Address register : 12 bit integer - Unsigned Binary
}hardware;

#endif //ACE3_HARDWARE_H
