#ifndef ACE3_OPCODE_FUNCTIONS_H
#define ACE3_OPCODE_FUNCTIONS_H

/* OPCODE FUNCTIONS */
void add(char * ac, char * operand);
void sub(char * ac, char * operand);
void load(char memory[4096][17], char * ac, char * mar);
void store(char memory[4096][17], char * ac, char * mar);
void input(char * binary_string, char * InREG);
void output(char * ac, char * OutREG);
void skipcond(char * ac, char * pc);
void jump(char * pc, char * operand);

/* Bonus Mark Operations Below */
void shift_right_logical(char * binary_string, int shift_amount);
void shift_left_logical(char * binary_string, int shift_amount);
void jump_if_zero(char * ac, char * pc, char * operand);
void jump_if_not_zero(char * ac, char * pc, char * operand);
void clear(char * ac);
void flip(char * str);
void dec_program_counter(char * pc);


#endif //ACE3_OPCODE_FUNCTIONS_H
