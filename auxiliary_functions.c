#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "auxiliary_functions.h"
#include "opcode_functions.h"


/*
 * Function:  get_default_memory
 * --------------------
 *  Sets the memory of the ACE3 computer to a default set of values. The values will run through each possible opcode
 *  at least once to display all functionality of the ACE3 computer.
 *
 *  parameters: char memory[4096][17]: The memory of the ACE3 Computer.
 *
 *  returns: A modified memory containing a default sequence of values.
 */
void get_default_memory(char memory[4096][17]) {
    char temp_memory[4096][17] = { /* The operations below will occur in order of the int displayed.*/
            "0001000000000001",    // 0: ADD X  | AC = 0010 000000000000
            "0010000000000000",    // 1: SUB X  | AC = 0000 111111111111
            "0011111111111111",    // 2: STORE X| AC = 0000 111111111111
            "0101000000000000",    // 3: INPUT  | AC = XXXX XXXXXXXXXXXX
            "0110000000000000",    // 4: OUTPUT | AC = XXXX XXXXXXXXXXXX
            "0100000000000000",    // 5: LOAD X | AC = 0001 000000000001
            "1000000000001000",    // 6: JUMP X | AC = 0001 000000000000
            "0000000000000001",    // Not visited
            "1001000000000111",    // 7: RLS    | AC = 0000 100000000000
            "1010000000000111",    // 8: LLS    | AC = 0001 000000000000
            "0111000000000000",    // 9: SKIP   | AC = 0001 000000000000
            "1101000000000011",    // 13: CLR   |  AC = 0000 00000000000
            "1011000000010000",    // 11,14: JZE| AC = 0001 000000000000, AC = 0000 000000000000
            "1110000000000000",    // 11: FLP   | AC = 0000 000000001000
            "1100000000001011",    // 12: JNZ   | AC = 0000 000000001000
            "0000000000000000",    // 16: HLT   | AC = 0000 000000000000
            "1111000000000000"     // 15: DEL   | AC = 0000 000000000000
    };

    for(int i = 17; i < 4096; i++) {
        for(int j = 0; j < 16; j++) {
            temp_memory[i][j] = '0';
        }

    }

    for(int i = 0; i < 4096; i++) {
        for(int j = 0; j<16; j++) {
            memory[i][j] = temp_memory[i][j];
        }
    }
}


/*
 * Function:  int_to_twos_comp
 * --------------------
 * Takes in an integer value and converts it to a char array representing a binary string in twos complement form.
 *
 *  parameters: int int_value: The decimal value you are converting to binary.
 *              int number_of_bits: The number of bits in the desired binary string.
 *
 *  returns: A char array representing a binary string in twos complement form.
 */
char * int_to_twos_comp(int int_value, int number_of_bits) { // Combine the other binary conversion functions together
    return binary_to_twoscomp(int_to_unsigned_binary(int_value, number_of_bits));
}


/*
 * Function:  int_to_unsigned_binary
 * --------------------
 * Takes in an integer value and converts it to an unsigned binary string.
 *
 *  parameters: int int_value: The decimal value you are converting to binary.
 *              int number_of_bits: The number of bits in the desired binary string.
 *
 *  returns: A char array representing an unsigned binary string.
 */
char * int_to_unsigned_binary(int int_value, int number_of_bits) {
    int d;
    char *return_value;

    return_value = (char*)malloc(number_of_bits+1);

    int count = 0;
    for (int i = number_of_bits-1; i >= 0 ; i--) {
        d = int_value >> i;
        if (d & 1){
            *(return_value + count) = 1 + '0';
        } else {
            *(return_value + count) = 0 + '0';
        }
        count++;
    }
    *(return_value + count) = '\0';
    return  return_value;
}


/*
 * Function:  binary_to_twoscomp
 * --------------------
 *  Takes in a binary string in twos complement form and converts it to twos complement.
 *
 *  parameters: char * unsigned_binary_string: An unsigned binary string.
 *
 *  returns: A char array representing a twos compliment binary string.
 */
char * binary_to_twoscomp(char * unsigned_binary_string){
    int binary_size = strlen(unsigned_binary_string);
    char * twos_compliment = (char*)malloc(binary_size+1);
    twos_compliment = unsigned_binary_string;

    int is_negative = 0;
    if (*unsigned_binary_string == '1') {
        is_negative = 1;
    }

    if (is_negative == 1) {
        int least_sig_bit = 0;
        for (int i = 0; i<=binary_size; i++) {
            if (*(unsigned_binary_string+i) != '0') {
                least_sig_bit = i;
                break;
            }
        }

        for (int i = 0; i <= least_sig_bit; i++) {
            if (*(unsigned_binary_string+i) == '0') {
                *(twos_compliment+i) = '1';
            } else {
                *(twos_compliment+i) = '0';
            }
        }
        *twos_compliment = '1';
    }
    return twos_compliment;
}


/*
 * Function:  twoscomp_to_int
 * --------------------
 *  Takes in a char array representing a twos complement binary string and converts it to an integer value.
 *
 *  parameters: char * twos_compliment_binary_string: A binary string in twos complement form.
 *
 *  returns: An integer value.
 */
int twoscomp_to_int(char * twos_compliment_binary_string) {
    int binary_length = strlen(twos_compliment_binary_string);
    int is_negative = 0;
    int return_value = 0;

    if (*(twos_compliment_binary_string) == '1') {
        is_negative = 1;

        for (int i=0; i<binary_length; i++) {
            if (*(twos_compliment_binary_string + i) == '1') {
                *(twos_compliment_binary_string + i) = '0';
            } else {
                *(twos_compliment_binary_string + i) = '1';
            }
        }
        for (int i=binary_length-1; i>0; i--) {
            if (twos_compliment_binary_string[i]=='0') {
                twos_compliment_binary_string[i]='1';
                for (++i; i<binary_length; i++) {
                    twos_compliment_binary_string[i]='0';
                }
                break;
            }
        }
    }

    int append_value;
    for (int i=1; i<binary_length; i++) {
        if (twos_compliment_binary_string[i] == '1') {
            append_value = 1;
            for (int j = 1; j < (binary_length - i); j++) {
                append_value *= 2;
            }
            return_value += append_value;
        }
    }

    if (is_negative == 1) {
        return 0 - return_value;
    } else {
        return return_value;
    }
}


/*
 * Function:  unsigned_binary_to_int
 * --------------------
 *  Takes in an unsigned binary string and converts it to an integer value.
 *
 *  parameters: char * unsigned_binary_string: An unsigned binary string.
 *
 *  returns: An integer value.
 */
int unsigned_binary_to_int(char * unsigned_binary_string) {
    int binary_length = strlen(unsigned_binary_string);
    int return_value = 0;
    int append_value = 0;
    for (int i = 0; i < binary_length; i++) {
        if (unsigned_binary_string[i] == '1') {
            append_value = 1;
            for (int j = 1; j < (binary_length - i); j++) {
                append_value *= 2;
            }
            return_value += append_value;
        }
    }
    return return_value;
}


/*
 * Function:  display_memory
 * --------------------
 *  Loops through each row of a matrix, printing the number of the row and then prints each character of that row.
 *
 *  parameters: char memory[4096][17]: The memory of the ACE3 Computer.
 *
 *  returns: N/A
 */
void display_memory(char memory[4096][17]) {
    for (int i = 0; i < 4096; i++) {
        printf("%d. ",i);
        for (int j = 0; j < 16; j++) {
            printf("%c",memory[i][j]);
        }
        printf("\n");
    }
}


/*
 * Function:  user_input
 * --------------------
 *  Prompts the user for input via the console. To finish type "exit" (without quotation marks) into the console.
 *
 *  parameters: char memory[4096][17]: The memory of the ACE3 Computer.
 *
 *  returns: A modified memory array containing the value inputted by the user.
 */
void user_input(char memory[4096][17]) {
    char input[17] = "";
    int line = 0;
    while (line < 4096) {
        printf("%d.\n", line);
        fgets(input,17,stdin);
        if(!strcmp(fgets(input,16,stdin), "exit\n")) break;
        else if (input_checker(input) == 1) {
            printf("Error input has to be 16 bit binary number, Enter Again:");
        }
        else{
            strcpy(memory[line], input);
            line++;
        }
    }

    while (line < 4096) {
        strcpy(memory[line],"0000000000000000");
        line++;
    }
    printf("Memory Loaded Successfully\n");
}


/*
* Function: input_checker
* -----------------------
* Validates that input entered by the user into the console is correct.
*
* Parameters: input[17]: The input from the console given by the user.
*
* Returns: 0 if input is a 16 digit binary number in the form of a char array.
*          1 if input is in an invalid form.
*
*/
int input_checker (char input[17]) {
    int check = 0;
    for(int i = 0; i < 16; i++) {
        if(input[i] != '0' && input[i] != '1') {
            check = 1;
            return check;
        }
    }
    return check;
}


/*
 * Function:  load_from_file
 * --------------------
 *  Loads data from a given file location into the memory of the ACE3 Computer - if it is valid.
 *
 *  parameters: char memory[4096][17]: The memory of the ACE3 Computer.
 *              char filename[]: The file location you are reading from.
 *
 *  returns: A modified memory containing the opcodes and operands from the given file.
 *
 *           An integer value denoting whether the file has been successfully read or not.
 *           A value of 1 indicates it has failed. A value of 0 indicates a success.
 */
int load_from_file(char memory[4096][17], char filename[]) {
    FILE *file;
    char temp_memory[4096][17];
    file = fopen(filename, "r");
    printf("Successfully opened file %s\n", filename);
    int c;

    for (int i=0;i < 4096; i++){
        for (int j=0;j < 16;j++){
            c = fgetc(file);
            printf("%d", c);
            if (c==EOF) {
                return 1;
            }
            temp_memory[i][j] = c;
        }
        c = fgetc(file);
        if (c==EOF) {
            return 1;
        }
    }

    for(int i = 0; i < 4096; i++) {
        for(int j = 0; temp_memory[i][j] != '\0'; j++) {
            memory[i][j] = temp_memory[i][j];
        }
    }
    return 0;
}


// Binary to Assembly
int binary_to_assembly(char * ir, char * mbr, char memory[4096][17], char * mar, char * ac, char * pc, char * InREG, char * OutREG) {
    int opcode_int = 0;
    char opcode[5] = "";
    memcpy(opcode, ir, 4);
    opcode_int = unsigned_binary_to_int(opcode);
    switch (opcode_int) {
        case 0:
            printf("HLT\n"); // HLT - Halt function. Exits the program.
            return 0;        // Execute the instruction.

        case 1:
            printf("ADD\n");                                      // ADD - Add function. Sum of number + AC
            memcpy(mbr, memory[unsigned_binary_to_int(mar)], 16); // Copy the contents at address MAR to MBR
            add(ac,mbr);                                          // Execute the instruction.
            break;

        case 2:
            printf("SUB\n");                                      // SUB - Subtract function. Take number from AC
            memcpy(mbr, memory[unsigned_binary_to_int(mar)], 16); // Copy the contents at address MAR to MBR
            sub(ac,mbr);                                          // Execute the instruction.
            break;

        case 3:
            printf("STO\n");                                      // STO - Store function. Store AC to X
            memcpy(mbr, memory[unsigned_binary_to_int(mar)], 16); // Copy the contents at address MAR to MBR
            load(memory, ac, mar);                                // Execute the instruction.
            break;

        case 4:
            printf("LOD\n");                                     // LOD - Load function. Store memory X to AC
            store(memory, ac, mar);                              // Execute the instruction.
            break;

        case 5:
            printf("INP\n");    // INP - Input function. Gets input from user and puts it into AC.
            input(ac, InREG);   // Execute the instruction.
            break;

        case 6:
            printf("OUT\n");    // OUT - Output function. Print the AC
            output(ac, OutREG); // Execute the instruction.
            break;

        case 7:
            printf("SKP\n");   // SKP - Skip function. Skip next instruction.
            skipcond(ac, pc);  // Execute the instruction.
            break;

        case 8:
            printf("JMP\n");                                      // JMP - Jump function. Jump unconditionally to mar.
            memcpy(mbr, memory[unsigned_binary_to_int(mar)], 16); // Copy the contents at address MAR to MBR
            jump(pc, mar);                                        // Execute the instruction.
            break;
            
        /* Bonus Mark Operations Below */
        case 9:
            printf("RLS\n");                                      // RLS - Left Logical Shift
            memcpy(mbr, memory[unsigned_binary_to_int(mar)], 16); // Copy the contents at address MAR to MBR
            shift_right_logical(ac, twoscomp_to_int(mbr));        // Execute the instruction.
            break;

        case 10:
            printf("LLS\n");                                      // LLS - Right Logical Shift
            memcpy(mbr, memory[unsigned_binary_to_int(mar)], 16); // Copy the contents at address MAR to MBR
            shift_left_logical(ac, twoscomp_to_int(mbr));         // Execute the instruction.
            break;

        case 11:
            printf("JZE\n");                                      // JZE - Jump if 0
            memcpy(mbr, memory[unsigned_binary_to_int(mar)], 16); // Copy the contents at address MAR to MBR
            jump_if_zero(ac, pc, mar);                            // Execute the instruction.
            break;

        case 12:
            printf("JNZ\n");                                      // JNZ - Jump if not
            memcpy(mbr, memory[unsigned_binary_to_int(mar)], 16); // Copy the contents at address MAR to MBR
            jump_if_not_zero(ac, pc, mar);                        // Execute the instruction.
            break;

        case 13:
            printf("CLR\n");         // CLR - Clear AC
            clear(ac);               // Execute the instruction.
            break;

        case 14:
            printf("FLP\n");         // FLP - Flip the AC
            flip(ac);                // Execute the instruction.
            break;

        case 15:
            printf("DEL\n");         // DEL - Decrement the program counter
            dec_program_counter(pc); // Execute the instruction.
            break;
    }
    return 1;
}

