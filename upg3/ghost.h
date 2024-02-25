#ifndef GHOST_H
#define GHOST_H

#include "given.h"
#include <string>

// BASKLASS
class Ghost {

public:
	Ghost(Pacman& pm);
	virtual ~Ghost() = default;

	virtual Point get_chase_point() const = 0;
	virtual Point get_scatter_point() const = 0;
	virtual std::string get_color() const = 0;
	virtual Point get_position() const;
	virtual void set_position(Point);

protected:
	Pacman& pacman;
	Point pos {};
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
	Point pos {};
	bool angry {false};
};

// PINKY
class Pinky : public Ghost {

public:
	using Ghost::Ghost;

	Point get_chase_point() const override;
	Point get_scatter_point() const override;
	std::string get_color() const override;

private:
	Point pos {};
};

// CLYDE
class Clyde : public Ghost {

public:
	using Ghost::Ghost;

	Point get_chase_point() const override;
	Point get_scatter_point() const override;
	std::string get_color() const override;

private:
	Point pos {};
	int attack_steps {6};
};

// INKY
class Inky : public Ghost {

public:
	Inky(Pacman& pm, Blinky& bl);

	Point get_chase_point() const override;
	Point get_scatter_point() const override;
	std::string get_color() const override;

private:
	Point pos {};
	Blinky& blinky;
};


#endif
