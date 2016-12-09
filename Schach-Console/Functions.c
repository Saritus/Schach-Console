#include "Functions.h"

void gotoXY(int x, int y) {
	HANDLE  hConsoleOutput; COORD koords;
	koords.X = x; koords.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, koords);
}

int getArrowKey(void)
{
	char c;
	/* Display message until key is pressed. */
	cputs("Hit me!! ");

	/* Use _getch to throw key away. */
	while (1) {
		while (!kbhit());
		if (getch() == 224) {
			printf("\nEditiertaste!!!\n");
			switch (c = getch()) {
			case 75:
				printf("\nlinks"); break;
			case 72:
				printf("\noben"); break;
			case 77:
				printf("\nrechts"); break;
			case 80:
				printf("\nunten"); break;
			default:
				printf("\nKey struck was '%d'\n", c);
			}
		}
		else
			break;
		return 1;
	}
}