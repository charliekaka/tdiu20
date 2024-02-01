#ifndef TIME_H
#define TIME_H

#include <string>
#include <sstream>

class Time {
public:
	// CONSTRUCTOR FUNCTIONS
	Time(int h, int m, int s);
	Time(std::string const& str_time); // STANDARD FORMAT
					   // HH:MM:SS OR HH:MM:SS:(AM/PM)
	Time() = default;

	std::string to_string(bool const am_pm_format = false) const; // TO_STRING STANDARD OR AM/PM

	// GETTERS
	bool is_am() const;
	int get_hour() const;
	int get_minute() const;
	int get_second() const;

	// ARITHMETIC OPERATORS
	Time operator+(int const x) const;	// PLUS
	Time& operator+=(int const x);		// PLUS EQUALS
	Time operator-(int const x) const;	// MINUS
	Time& operator-=(int const x);		// MINUS EQUALS

	// ONESTEP ARITHMETIC OPERATORS
	Time& operator++();	// PRE  INCREMENT
	Time operator++(int);	// POST INCREMENT
	Time& operator--();	// PRE  DECREMENT
	Time operator--(int);	// POST DECREMENT
	
	// COMPARISON OPERATORS
	bool operator==(const Time& item) const;	// EQUAL
	bool operator!=(const Time& item) const;	// NOT EQUAL
	bool operator>(const Time& item) const;		// GREATER
	bool operator>=(const Time& item) const;	// GREATER OR EQUAL
	bool operator<(const Time& item) const;		// LESSER
	bool operator<=(const Time& item) const;	// LESSER OR EQUAL
							
	void set_time_values(std::istream& is); 	// VALUE SETTER FOR ">>" 

private:
	int h;
	int m;
	int s;

	// VALIDATE DATA
	void check_times() const;
};

// STREAM HANDLER OPERATORS
std::ostream& operator<<(std::ostream& os, Time const& item); // PRINTABLE STRING
std::istream& operator>>(std::istream& is, Time& item);       // STANDARD OUTPUT

#endif
