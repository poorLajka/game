#include <iostream>
#include <curses.h>
#include <unistd.h>

#include <physics.h>

int main() {

    physics::PhysicsState state;
    physics::PhysicsObject obj1;
    physics::PhysicsObject obj2;

    physics::add_state_object(state, obj1);
    physics::add_state_object(state, obj2);

    initscr();

    int x_1 = 15;

	
    int y_1 = 15;

    int x_2 = 20;
    int y_2 = 15;

    while (true) {

	clear();
	sleep(1);
	char st_1 = 'O';
	char st_2 = 'X';
	mvprintw(x_1,y_1,"%c", st_1);
	mvprintw(x_2,y_2,"%c",st_2);
	refresh();
	x_1++;
        physics::update_state(state, 0.1);
    }	
    getch();	
    endwin();
    return 0;
	
	
}
