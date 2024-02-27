#ifndef GHOST_H
#define GHOST_H

#include "given.h"
#include <string>

// BASKLASS
class Ghost {

public:
	Ghost(Pacman& pm, Point ghost_pos, Point scatter_pos);
	virtual ~Ghost() = default;

	virtual Point get_chase_point() const = 0;
	virtual Point get_scatter_point() const = 0;
	virtual std::string get_color() const = 0;
	virtual Point get_position() const;
	virtual void set_position(Point);

protected:
	Pacman& pacman;
	Point pos {};
	Point scatter_pos {};
};

// BLINKY
class Blinky : public Ghost {

public:
	using Ghost::Ghost;

	Point get_chase_point() const override;
	Point get_scatter_point() const override;
	std::string get_color() const override;
	void set_angry(bool);
	bool is_angry() const;

private:
	bool angry {false};
};

// PINKY
class Pinky : public Ghost {

public:
	using Ghost::Ghost;

	Point get_chase_point() const override;
	Point get_scatter_point() const override;
	std::string get_color() const override;
};

// CLYDE
class Clyde : public Ghost {

public:
	Clyde(Pacman& pm, Point pos, Point scatter_pos, int attack);

	Point get_chase_point() const override;
	Point get_scatter_point() const override;
	std::string get_color() const override;

private:
	int attack_steps {};
};

// INKY
class Inky : public Ghost {

public:
	Inky(Pacman& pm, Point pos, Point scatter_pos, Blinky& bl);

	Point get_chase_point() const override;
	Point get_scatter_point() const override;
	std::string get_color() const override;

private:
	Blinky& blinky;
};


#endif
