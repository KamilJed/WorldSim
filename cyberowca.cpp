// cyberowca.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "World.h"
#include "curses.h"
#include <ctime>

int main() {

	initscr();
	srand(time(NULL));
	keypad(stdscr, true);
	curs_set(0);
	int x, y, row, col;
	getmaxyx(stdscr, row, col);
	mvprintw(row / 2, (col - strlen("Type in the board width: ")) / 2, "%s", "Type in the board width: ");
	scanw("%d", &x);
	clear();
	mvprintw(row / 2, (col - strlen("Type in the board length: ")) / 2, "%s", "Type in the board length: ");
	scanw("%d", &y);
	clear();
	if (has_colors())start_color();
	noecho();
	try {
		World world(x, y);
		world.gameInit();
	}
	catch (std::string error) {
		mvprintw(row / 2, (col - error.size()) / 2, "%s", error.c_str());
		getch();
	}
	catch (std::exception& e) {
		mvprintw(row / 2, (col - strlen(e.what())) / 2, "%s", e.what());
		getch();
	}
	
	endwin();
	return 0;
}