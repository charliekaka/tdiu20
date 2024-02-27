#include "ghost.h"
#include <string>

using namespace std;

// BASKLASS GHOST
Ghost::Ghost(Pacman& pm, Point ghost_pos, Point scatter_pos)
	: pacman(pm), pos {ghost_pos}, scatter_pos {scatter_pos}
{}

Point Ghost::get_position() const {
	return pos;
}

void Ghost::set_position(Point p) {
	pos = p;
}

// BLINKY //////////////
bool Blinky::is_angry() const{
	return angry;
}

void Blinky::set_angry(bool b) {
	angry = b;
}

Point Blinky::get_chase_point() const {
	// spelare pos
	return pacman.get_position();
}

Point Blinky::get_scatter_point() const {
	// om arg chase point annars övre högra hörnet
	if(angry) {
		return get_chase_point();
	}
	return scatter_pos;
}

string Blinky::get_color() const {
	return "red";
}

// PINKY //////////////
Point Pinky::get_chase_point() const {
	// två steg franför spelaren i dens riktning
	Point pacman_dir {pacman.get_direction()};
	Point pacman_pos {pacman.get_position()};
	Point pinky_chase {pacman_pos.x + (pacman_dir.x*2), pacman_pos.y + (pacman_dir.y*2)};
	if(pinky_chase.x > WIDTH-1) pinky_chase.x = WIDTH-1;
	if(pinky_chase.y > HEIGHT-1) pinky_chase.y = HEIGHT-1;
	return pinky_chase;
}

Point Pinky::get_scatter_point() const {
	// övre vänstra hörnet
	return scatter_pos;
}

string Pinky::get_color() const {
	return "pink";
}

// CLYDE ///////////////
Clyde::Clyde(Pacman& pm, Point pos, Point scatter_pos, int attack)
// MÅSVINGAR
    : Ghost(pm, pos, scatter_pos), attack_steps {attack}
{}

Point Clyde::get_chase_point() const {
	// spelare om clyde är mer en n steg ifrån den annars scattermål
	Point clyde_chase {get_scatter_point()};
	Point pacman_pos {pacman.get_position()};
	Point clyde_pos {get_position()};

	int x_diff {pacman_pos.x - clyde_pos.x};
	int y_diff {pacman_pos.y - clyde_pos.y};

	if(abs(x_diff) + abs(y_diff) > attack_steps)
	{
		clyde_chase = pacman_pos;
	}

	return clyde_chase;
}

Point Clyde::get_scatter_point() const {
	// nedre vänstra hörnet
	return scatter_pos;
}

string Clyde::get_color() const {
	return "orange";
}

// INKY
Inky::Inky(Pacman& pm, Point pos, Point scatter_pos, Blinky& bl)
// MÅSVINGAR
    : Ghost(pm, pos, scatter_pos), blinky(bl)
{}

Point Inky::get_chase_point() const {
	Point pacman_pos {pacman.get_position()};
	Point pacman_dir {pacman.get_direction()};
	Point blinky_pos {blinky.get_position()};
	Point inky_chase {};

	pacman_pos = {pacman_pos.x + (pacman_dir.x*2), pacman_pos.y + (pacman_dir.y*2)};

	int x_diff {abs(pacman_pos.x - blinky_pos.x)};
	int y_diff {abs(pacman_pos.y - blinky_pos.y)};

	if(pacman_pos.x >= blinky_pos.x) 
	{
		inky_chase.x = pacman_pos.x + x_diff;
	} else 
	{
		inky_chase.x = pacman_pos.x - x_diff;
	}

	if(pacman_pos.y >= blinky_pos.y)
	{
		inky_chase.y = pacman_pos.y + y_diff;
	} else 
	{
		inky_chase.y = pacman_pos.y - y_diff;
	}

	if(inky_chase.x > WIDTH-1) inky_chase.x = WIDTH-1;
	if(inky_chase.x < 0) inky_chase.x = 0;
	if(inky_chase.y > HEIGHT-1) inky_chase.y = HEIGHT-1;
	if(inky_chase.y < 0) inky_chase.y = 0;

	return inky_chase;
}

Point Inky::get_scatter_point() const {
	return scatter_pos;
}

string Inky::get_color() const {
	return "blue";
}