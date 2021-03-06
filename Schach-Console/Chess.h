#include "Functions.h"

typedef char Field[8][8];

typedef char* String;

#define spalte x
#define zeile y

typedef struct {
	int x;
	int y;
} Position;

typedef struct {
	bool ok;
	int player;
	Position von;
	Position nach;
} Chessmove;

typedef enum { next, undo, save, quit, error } Command;

void print_surface(Field, int);
void print_player(Position, int);
void print_field(Field, Position);
void reset_field(Field);
void print_letters(Position);
void print_border(Position);
Command input(Field, int);
void clear_stdin();
Chessmove evaluate_input(String);
bool is_letter(char);
bool is_number(char);

void execute_move(Field, Chessmove);

// evaluate moves
bool is_player_figur(int, char);
bool is_move_ok(Field, Chessmove);
bool is_pawn_move_ok(Field, Chessmove); // Bauer
bool is_rook_move_ok(Field, Chessmove); // Turm

// files
void load_file(String, Field);
void save_file(String, Field);
String readLine(String, int);
int writeLine(String, Field);
void loadLine(String, int, Field);