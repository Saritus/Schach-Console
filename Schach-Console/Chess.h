#include "Functions.h"

struct Chessmove{
	bool ok;
	int player;
	int von_spalte;
	int von_zeile;
	int nach_spalte;
	int nach_zeile;
};

void print_surface(int[8][8], int);
void print_player(int, int, int);
void print_field(char[8][8], int, int);
void reset_field(char[8][8]);
void print_letters(int, int);
void print_border(int, int);
void load_file(char*, char[8][8]);
void save_file(char*, char[8][8]);
char input(char[8][8], int);
void clear_stdin();
struct Chessmove evaluate_input(char*);
int is_letter(char);
int is_number(char);
void execute_move(char[8][8], struct Chessmove);

// evaluate moves
bool is_move_ok(char[8][8], struct Chessmove);
bool is_pawn_move_ok(char[8][8], struct Chessmove);

// files
char* readLine(char*, int);
int writeLine(char*, char[8][8]);
void loadLine(char*, int, char[8][8]);