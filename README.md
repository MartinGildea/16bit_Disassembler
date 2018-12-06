# 16 Bit Computer Emulator

The 16 Bit Computer Emulator was the third programming assignment for the class CS210 - Computer Systems and Architecture.
The aim of the exercise was to implement & test a disassembler in C.

I recieved full marks for the exercise.

## User Guide



## TODO
In order to improve my skills in C I would like to implement the following features:
1. Full regester functionality in accordance with a real world disassembler such as MIPS.
2. Modify the program to use a of 'hardware' struct that has the following properties:
	- A memory array containing 4096 'word' structs where each word has a 4bit 'opcode' bitfield and a 12bit 'operand' bitfield.
	- A processor struct implementing all registers as bitfields.
	
3. A user validation system to ensure correct input is entered.

These improvements were outside the scope of the assignment, but I feel they would be the more efficient
and industrial way to do things.

Task '2' is currently in progress. I have created a hardware header file and an initialiser function.
