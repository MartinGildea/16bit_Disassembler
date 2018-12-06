# 16 Bit Computer Emulator

The 16 Bit Disassembler was  was the third programming assignment for the class CS210 - Computer Systems and Architecture.
The aim of the exercise was to implement & test a disassembler in C.

I recieved full marks for the exercise.

## User Guide
The program must be run with an argument specifying which way memory should be loaded. This can be one of the following options:
1. '-d': Loads default memory and requires no further input from the user. The default memory will run through each 'opcode' at least once.
2. '-c': Prompts the user to enter input for each line of memory. Will stop taking in memory when the user enters 'exit'.
3. '-f': Prompts the user to enter a file name (explicitly) and loads memory from that file.

The program will then run through memory executing each command it finds according to the first 4 bits of memory (the opcode). If the opcode requires a value to operate on it will either use the 16bit accumulator, the 16bit value stored at the memory address located at the place denoted by final 12 bits of memory(the operand) or both.

It will continue looping through memory until a 'halt' command is reached or the program counter exceeds the number of words in memory and the program will crash. (The program counter exceeding this value is considered an error and this is intentional. Correct error handling is yet to be implemented. Alternatively the program may loop infintely if the correct series of opcodes are used.

## TODO
In order to improve my skills in C I would like to implement the following features:
1. Full register functionality in accordance with a real world disassembler such as MIPS.
2. Modify the program to use a of 'hardware' struct that has the following properties:
	- A memory array containing 4096 'word' structs where each word has a 4bit 'opcode' bitfield and a 12bit 'operand' bitfield.
	- A processor struct implementing all registers as bitfields.
	
3. A user validation system to ensure correct input is entered.

These improvements were outside the scope of the assignment, but I feel they would be the more efficient
and industrial way to do things.

Task '2' is currently in progress. I have created a hardware header file and an initialiser function.
