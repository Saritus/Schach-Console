#include "Functions.h"

void print_player(int x, int y, int player);
void print_field(char[8][8], int, int);
void reset_field(char[8][8]);
void print_border(int, int);
void load_file(char*, char[8][8]);
void save_file(char*, char[8][8]);
char input(char[8][8], int);
void clear_stdin();
int evaluate_input(char*, int[4]);
int is_letter(char);
int is_number(char);
int execute_move(char[8][8], int[4]);
int is_move_ok(char[8][8], int[4], int);