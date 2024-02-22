#include "ghost.h"
#include <string>

using namespace std;

// BASKLASS GHOST
Ghost::Ghost(Pacman& pm)
	: pacman {pm}
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

Point Blinky::get_chase_point() const {
	// spelare pos
	return pacman.get_position();
}

Point Blinky::get_scatter_point() const {
	// om arg chase point annars övre högra hörnet
	if(angry) {
		return pacman.get_position();
	}
	Point blinky_scatter = {WIDTH, 0};
	return blinky_scatter;
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
	if(pinky_chase.x > WIDTH) pinky_chase.x = WIDTH;
	if(pinky_chase.y > HEIGHT) pinky_chase.y = HEIGHT;
	return pinky_chase;
}

Point Pinky::get_scatter_point() const {
	// övre vänstra hörnet
	Point pinky_scatter {0,0};
	return pinky_scatter;
}

string Pinky::get_color() const {
	return "pink";
}

// CLYDE ///////////////
Point Clyde::get_chase_point() const {
	// spelare om clyde är mer en n steg ifrån den annars scattermål
	Point pacman_pos {pacman.get_position()};

	int x_diff {pacman_pos.x - pos.x};
	int y_diff {pacman_pos.y - pos.y};
	
	if(x_diff + y_diff > attack_steps) {
		return pacman_pos;
	}
	return get_scatter_point();
}

Point Clyde::get_scatter_point() const {
	// nedre vänstra hörnet
	Point clyde_scatter {0, HEIGHT};
	return clyde_scatter;
}

string Clyde::get_color() const {
	return "orange";
}
