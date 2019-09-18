/**************************************************************************
 * Assessment Title: ACE 3
 * Number of Submitted C Files: 5(3 .c files and 2 .h files.)
 * (Added 1 additional file since submission - hardware.h)
 * Date: 23/11/18
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hardware.h"
#include "auxiliary_functions.h"
#include "opcode_functions.h"


int fetch_decode_execute(char memory[4096][17]);
void computer_initializer();

int main(int argc, char **argv) {
    char memory[4096][17];
    if (argc == 2) {
        if (argv[1][0]=='-' && argv[1][2]=='\0') {
            switch(argv[1][1]){
                case 'd':
                    printf("Loading default memory...\n");
                    get_default_memory(memory);
                    display_memory(memory);
                    fetch_decode_execute(memory);
                    break;

                case 'c':
                    printf("Enter the contents of the memory, 16 bits at a time. \n"
                           "To finish inputting type 'exit'.\n");
                    user_input(memory);
                    display_memory(memory);
                    fetch_decode_execute(memory);
                    break;

                case 'f': {
                    char file_name[256];
                    printf("Please enter the name of the file you wish to load. E.g/ file.txt (Ensure explicit)");
                    fgets(file_name, 256, stdin);
                    printf("Loading memory from file...\n");
                    int check = load_from_file(memory, file_name);
                    if (check == 1) {
                        printf("Error - Encountered end of file too early. \n"
                               "Exiting program...\n");
                        break;
                    }
                    display_memory(memory);
                    fetch_decode_execute(memory);
                    break;
                }

                default:  
                    printf("Error: Incorrect input argument entered. Please use one of the following:\n"
                           "-d:\tLoad the default memory.\n"
                           "-c:\tRead the memory from the console.\n"
                           "-f:\tLoad the memory from a file.\n"
                           "Exiting program...\n");
                    break;
            }
        }

    } else {              // Print error saying an input argument is required and exit
        printf("Error: Program requires one input argument:\n"
               "-d:\tLoad the default memory.\n"
               "-c:\tRead the memory from the console.\n"
               "-f:\tLoad the memory from a file.\n"
               "Exiting program...\n");
    }
    return 0;
}


/*
 * Function:  fetch_decode_execute
 * --------------------
 *  The fetch-decode-execute cycle of the ACE3 Computer. It is created according to the specifications in the
 *  assignment brief and is commented to show what code corresponds to which stage of the brief.
 *
 *  parameters: char memory[4096][17]: The memory of the ACE3 Computer.
 *
 */
int fetch_decode_execute(char memory[4096][17]){
    char ac[17]  = "";    // Accumulator : 16 bits - Twos compliment
    char ir[17]  = "";    // Input register : 16 bits - Twos compliment
    char mbr[17] = "";    // Memory Buffer register : 16 bits
    char pc[13]  = "";    // Program counter : 12 bits - Unsigned Binary
    char mar[13] = "";    // Memory Address register : 12 bit integer - Unsigned Binary
    char InREG[17] = "";  // The input register, which holds data from the input device.
    char OutREG[17] = ""; // The output register, which holds data for the output device.
    memcpy(ac, "0000000000000000", 16);
    memcpy(pc, "000000000000", 12);

    printf("Execution begun...\n");
    int exit_check = 1;
    while (exit_check == 1) {

        // Copy the PC to MAR
        memcpy(mar, pc, 12);

        // Copy the contents of memory at address MAR to IR
        memcpy(ir, memory[unsigned_binary_to_int(mar)], 16);

        // Increment PC by 1
        memcpy(pc, int_to_unsigned_binary(unsigned_binary_to_int(pc) + 1 , 12), 12);

        // Place operand in MAR
        memcpy(mar, ir+4, 12);

        // Execute commands.
        exit_check = binary_to_assembly(ir, mbr, memory, mar, ac, pc, InREG, OutREG);
    }
    printf("\nProgram execution has completed. Outputting program state...\n");

    // Display the pc, ir, ac
    printf("PC on machine exit: %s\n", pc);
    printf("IR on machine exit: %s\n", ir);
    printf("AC on machine exit: %s\n", ac);

    // Display the rest of memory
    printf("Memory state on machine exit:\n");
    display_memory(memory);
    return 0;
}

void computer_initializer(){
    hardware computer = { .ac = "0000000000000000",
            .ir = "0000000000000000",
            .mbr = "0000000000000000",
            .in_reg = "0000000000000000",
            .out_reg = "0000000000000000",
            .pc = "000000000000",
            .mar = "000000000000"};
}
