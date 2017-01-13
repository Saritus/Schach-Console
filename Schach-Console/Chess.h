#include "Functions.h"

typedef char Field[8][8];

typedef struct {
	int zeile;
	int spalte;
} Position;

typedef struct {
	bool ok;
	int player;
	Position von;
	Position nach;
} Chessmove;

typedef enum { next, undo, save, quit, error } Command;

void print_surface(Field, int);
void print_player(int, int, int);
void print_field(Field, int, int);
void reset_field(Field);
void print_letters(int, int);
void print_border(int, int);
Command input(Field, int);
void clear_stdin();
Chessmove evaluate_input(char*);
bool is_letter(char);
bool is_number(char);

void execute_move(Field, Chessmove);

// evaluate moves
bool is_player_figur(int, char);
bool is_move_ok(Field, Chessmove);
bool is_pawn_move_ok(Field, Chessmove); // Bauer
bool is_rook_move_ok(Field, Chessmove); // Turm

// files
void load_file(char*, Field);
void save_file(char*, Field);
char* readLine(char*, int);
int writeLine(char*, Field);
void loadLine(char*, int, Field);