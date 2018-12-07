#ifndef ACE3_AUXILIARY_FUNCTIONS_H
#define ACE3_AUXILIARY_FUNCTIONS_H

void get_default_memory(char memory[4096][17]);
char * int_to_twos_comp(int dec, int type);
char * int_to_unsigned_binary(int dec, int type);
char * binary_to_twoscomp(char * bin);
int twoscomp_to_int(char * twoscomp);
int unsigned_binary_to_int(char * twoscomp);
void display_memory(char memory[4096][17]);
void user_input(char memory[4096][17]);
int load_from_file(char memory[4096][17], char filename[]);
int binary_to_assembly(char * ir, char * mbr, char memory[4096][17], char * mar, char * ac, char * pc, char * InREG, char * OutREG);

#endif //ACE3_AUXILIARY_FUNCTIONS_H
