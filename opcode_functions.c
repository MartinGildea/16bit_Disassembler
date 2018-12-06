#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "auxiliary_functions.h"
#include "opcode_functions.h"

/* 1 0001 ADD */ // Add the ac to the operand
void add(char * ac, char * operand) {
    memcpy(ac, int_to_twos_comp(twoscomp_to_int(ac) + twoscomp_to_int(operand), 16), 16);
}


/* 2 0010 SUB */ // Subtract the ac from the operand
void sub(char * ac, char * operand) {
    memcpy(ac, int_to_twos_comp(twoscomp_to_int(ac) - twoscomp_to_int(operand), 16), 16);
}


/* 3 0111 STORE */
void load(char memory[4096][17], char * ac, char * mar) {
    memcpy(memory[unsigned_binary_to_int(mar)], ac, 16);
}


/* 4 0100 LOAD */
void store(char memory[4096][17], char * ac, char * mar) {
    memcpy(ac, memory[unsigned_binary_to_int(mar)], 16);
}

/* 5 0110 INPUT */
void input(char * ac, char * InREG) {
    char input[17] = "";
    printf("Enter the AC:");
    fgets(input,17,stdin);   // Reads the input
    memcpy(InREG, input, 16);
    memcpy(ac, InREG, 16); // set's ac to input
}


/* 6 0110 OUTPUT */
void output(char * ac, char * OutREG) {
    memcpy(OutREG, ac, 16);
    printf("AC: %s\n", OutREG);
}


/* 7 0111 SKIPCOND */ //If AC is positive, skip next instruction.
void skipcond(char * ac, char * pc) {
    if(twoscomp_to_int(ac) > 0) {
        memcpy(pc, int_to_unsigned_binary(unsigned_binary_to_int(pc) + 1 , 12), 12);
    }
}


/* 8 1000 JUMP X */
void jump(char * pc, char * operand) {
    memcpy(pc, int_to_unsigned_binary(unsigned_binary_to_int(operand), 12), 12);
}



/* Bonus Mark Operations Below */

/* 9 1001 Right Logical Shift X*/
void shift_right_logical(char * binary_string, int shift_amount) {
    for (int i = 0; i<shift_amount; ++i) {                 // For number of times digits should be shifted
        for (int j = strlen(binary_string)-1; j>0; --j) {  // For every digit minus the one at start
            *(binary_string+j) = *(binary_string+(j-1));   // Assign every character to the char to its left
        }
    }

    for (int i = 0; i<(shift_amount); ++i) {               // For number of times digits should be shifted
        *(binary_string+i) = '0';                          // Fill voided characters with 0
    }
}


/* 10 1010 Left logical Shift X */
void shift_left_logical(char * binary_string, int shift_amount) {
    for (int i = 0; i<shift_amount; ++i) {                                                   // For number of times digits should be shifted
        for (int j = 1; j<=strlen(binary_string)-1; ++j) {                                   // For every digit minus the one at end
            *(binary_string+(j-1)) = *(binary_string+j);                                     // Assign every character to the char to its right
        }
    }
    for (int i = strlen(binary_string)-1; i>((strlen(binary_string)-1)-shift_amount); --i) { // For number of times digits should be shifted
        *(binary_string+i) = '0';                                                            // Fill voided characters with 0
    }
}


/* 11 1011 Jump if 0 X*/
void jump_if_zero(char * ac, char * pc, char * operand) {
    if(twoscomp_to_int(ac) == 0){
        memcpy(pc, int_to_unsigned_binary(unsigned_binary_to_int(operand), 12), 12);
    }
}


/* 12 1100 Jump if not 0 X*/
void jump_if_not_zero(char * ac, char * pc, char * operand) {
    if(twoscomp_to_int(ac) != 0) {
        memcpy(pc, int_to_unsigned_binary(unsigned_binary_to_int(operand), 12), 12);
    }
}


/* 13 1101 Clear AC to 0 */
void clear(char * ac) {
    memcpy(ac, "0000000000000000", 16);
}


/* 14 1110 Flip AC */
void flip(char* str) {
    for (int i = 0; i < strlen(str); i++) {     // Flip everything until least significant bit
        if (*(str+i) == '0'){
            *(str+i) = '1';
        } else {
            *(str+i) = '0';
        }
    }
}


/* 15 1111 Decrement Program Counter */
void dec_program_counter(char * pc) {
    memcpy(pc, int_to_twos_comp(twoscomp_to_int(pc)-2, 12), 12);
}
