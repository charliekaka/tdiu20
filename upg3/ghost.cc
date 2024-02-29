#include "ghost.h"
#include <string>

using namespace std;

// BASKLASS GHOST
Ghost::Ghost(Pacman& pm, Point ghost_pos, Point scatter_pos, string color)
	: pacman{pm}, pos {ghost_pos}, scatter_pos {scatter_pos}, color {color}
{}

Point Ghost::get_position() const {
	return pos;
}

Point Ghost::get_scatter_point() const {
	return scatter_pos;
}

void Ghost::set_position(Point p) {
	if(p.x > WIDTH-1) p.x = WIDTH-1;
	if(p.x < 0) p.x = 0;
	if(p.y > HEIGHT-1) p.y = HEIGHT-1;
	if(p.y < 0) p.y = 0;

	pos = p;
}

string Ghost::get_color() const {
	return color;
}

// BLINKY //////////////
Blinky::Blinky(Pacman& pm, Point pos, Point scatter_pos)
	: Ghost{pm, pos, scatter_pos, "red"}
{}

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

// PINKY //////////////
Pinky::Pinky(Pacman& pm, Point pos, Point scatter_pos)
	: Ghost{pm, pos, scatter_pos, "pink"}
{}

Point Pinky::get_chase_point() const {
	// två steg franför spelaren i dens riktning
	Point pacman_dir {pacman.get_direction()};
	Point pacman_pos {pacman.get_position()};
	Point pinky_chase {pacman_pos.x + (pacman_dir.x*2), pacman_pos.y + (pacman_dir.y*2)};

	return pinky_chase;
}

// CLYDE ///////////////
Clyde::Clyde(Pacman& pm, Point pos, Point scatter_pos, int attack)
    : Ghost{pm, pos, scatter_pos, "orange"}, attack_steps {attack}
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

// INKY
Inky::Inky(Pacman& pm, Point pos, Point scatter_pos, Blinky& bl)
    : Ghost{pm, pos, scatter_pos, "blue"}, blinky{bl}
{}

Point Inky::get_chase_point() const {
	Point pacman_pos {pacman.get_position()};
	Point pacman_dir {pacman.get_direction()};
	Point blinky_pos {blinky.get_position()};
	Point inky_chase {};

	pacman_pos = {pacman_pos.x + (pacman_dir.x*2), pacman_pos.y + (pacman_dir.y*2)};

	int x_diff {pacman_pos.x - blinky_pos.x};
	int y_diff {pacman_pos.y - blinky_pos.y};

	inky_chase.x = pacman_pos.x + x_diff;
	inky_chase.y = pacman_pos.y + y_diff;

	return inky_chase;
}
