#include "Functions.h"

void print_field(char[8][8], int, int);
void reset_field(char[8][8]);
void print_border(int, int);
void load_file(char*, char[8][8]);
void save_file(char*, char[8][8]);
char input();
void clear_stdin();
void evaluate_input(char*);
int is_letter(char);
int is_number(char);