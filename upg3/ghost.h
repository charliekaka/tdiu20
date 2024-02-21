#ifndef GHOST_H
#define GHOST_H

#include "given.h"
#include <string>

class Ghost {

public:
	virtual Point get_chase_point() const;
	virtual Point get_scatter_point() const;
	virtual std::string get_color() const;
	virtual Point get_position() const;
	virtual void set_position(Point);

};


class Blinky : public Ghost {

public:
	Point get_chase_point() const override;
	Point get_scatter_point() const override;
	std::string get_color() const override;
	Point get_position() const override;
	void set_position(Point) override;

private:
	Point pos {};
	Point dir {};
};


class Pinky : public Ghost {

public:
	Point get_chase_point() const override;
	Point get_scatter_point() const override;
	std::string get_color() const override;
	Point get_position() const override;
	void set_position(Point) override;

private:
	Point pos {};
	Point dir {};

};


class Clyde : public Ghost {

public:
	Point get_chase_point() const override;
	Point get_scatter_point() const override;
	std::string get_color() const override;
	Point get_position() const override;
	void set_position(Point) override;

private:
	Point pos {};
	Point dir {};

};

#endif
