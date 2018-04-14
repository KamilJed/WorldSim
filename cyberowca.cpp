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
	if (has_colors())start_color();
	noecho();
	World world(20, 20);
	world.drawWorld();
	world.setZn(getch());
	while (world.getZn() != ESC) {

		world.newTurn();
		if (!world.ifHuman()) {

			world.setZn(getch());
		}
		if (world.getZn() == 's' || world.getZn() == 'S')world.saveWorld();
		else if (world.getZn() == 'l' || world.getZn() == 'L')world.loadWorld();
	}
	
	endwin();
	return 0;
}