# 16 Bit Computer Emulator

The 16 Bit Disassembler was  was the third programming assignment for the class CS210 - Computer Systems and Architecture.
The aim of the exercise was to implement & test a disassembler in C.

I recieved full marks for the exercise.

## User Guide
The program must be run with an argument specifying which way memory should be loaded. This can be one of the following options:
1. '-d': Loads default memory and requires no further input from the user. The default memory will run through each 'opcode' at least once.
2. '-c': Prompts the user to enter input for each line of memory. Will stop taking in memory when the user enters 'exit'.
3. '-f': Prompts the user to enter a file name (explicitly) and loads memory from that file.


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
