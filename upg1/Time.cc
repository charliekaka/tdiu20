#include "Time.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

Time::Time(int h, int m, int s)
	: h{h}, m{m}, s{s}
{
	check_times();
}

Time::Time(string const& str_time)
	: h{}, m{}, s{}
{
	istringstream iss{str_time};
	char c;
	string postfix {};
	iss >> h >> c >> m >> c >> s >> postfix;

	if(postfix == "pm" || postfix == "PM"){
		h += 12;
	}

	check_times();
}

void Time::check_times() const
{
	if(h >= 24 || m >= 60 || s >= 60 ||
	   h < 0   || m < 0   || s < 0)
	{
		throw out_of_range("felaktiga tider");
	}
}

string Time::to_string(bool const am_pm_format) const
{
	ostringstream oss {};
	string postfix {};
	int temp_h {h};

	if(am_pm_format)
	{
		if(is_am())
		{
			if(temp_h == 0) 
			{
				temp_h += 12;
			}
			postfix = "am";
		}else
		{
			if(temp_h != 12) 
			{
				temp_h -= 12;
			}
			postfix = "pm";
		}
	}

	oss << setfill('0') << setw(2)
	    << temp_h << ":" << setw(2) 
	    << m << ":" << setw(2)
	    << s << postfix;

	return oss.str();
}

bool Time::is_am() const
{
	return h < 12;
}

int Time::get_hour() const
{
	return h;
}

int Time::get_minute() const
{
	return m;
}

int Time::get_second() const
{
	return s;
}

// PLUS EQUALS
Time& Time::operator+=(int const x)
{
	s += x;

	while(s >= 60 || s < 0) {
		
		if(s >= 60){
			m++;
			s -= 60;
			if(m == 60){
				h++;
				m = 0;
				if(h == 24){
					h = 0;
				}
			}
		}
		else if(s < 0){
			m--;
			if(m < 0){
				h--;
				m = 59;
				if(h < 0){
					h = 23;
				}
			}
			s += 60;
		}

	}

	return *this;
}

// PLUS
Time Time::operator+(int const x) const
{
	Time tmp {*this};
	tmp += x;
	return tmp;
}

// PRE PLUS
Time operator+(int const x, Time const& t)
{
	return t + x;
}

// MINUS
Time Time::operator-(int const x) const
{
	Time tmp {*this};
	tmp -= x;
	return tmp;
}

// PRE MINUS 
Time operator-(int const x, Time const& t)
{
	return t - x;
}

// MINUS EQUALS
Time& Time::operator-=(int const x)
{
	*this += -1 * x;
	return *this;
}

// PRE INCREMENT
Time& Time::operator++()
{
	return *this += 1;
}

// POST INCREMENT
Time Time::operator++(int)
{
	Time tmp {*this};
	++*this;
	return tmp;
}

// PRE DECREMENT
Time& Time::operator--(){
	return *this -= 1;
}

// POST DECREMENT
Time Time::operator--(int){
	Time tmp {*this};
	--*this;
	return tmp;
}

// EQUAL
bool Time::operator==(const Time& item) const
{
	return (s == item.s && m == item.m && h == item.h);
}

// NOT EQUAL
bool Time::operator!=(const Time& item) const
{
	return !((*this) == item);
}

// GREATER
bool Time::operator>(const Time& item) const
{
	return ((h > item.h) || 
		(h == item.h && m > item.m) || 
		(h == item.h && m == item.m && s > item.s));
}

// GREATER OR EQUAL
bool Time::operator>=(const Time& item) const
{
	return ((*this) > item || (*this) == item);
}

// LESSER
bool Time::operator<(const Time& item) const
{
	return (!(*this > item) && *this != item);
}

// LESSER OR EQUAL
bool Time::operator<=(const Time& item) const
{
	return (!(*this >= item) || *this == item);
}

// PRINTABLE STRING
ostream& operator<<(ostream& os, Time const& item)
{
	os << item.to_string();
	return os;
}

// PUBLIC VALUE SETTER FOR ">>" 
void Time::set_time_values(istream& is)
{
	char c;
	is >> h >> c >> m >> c >> s;
	check_times();
}

// STANDARD OUTPUT
istream& operator>>(istream& is, Time& item) noexcept
{
	Time tmp_time {item}; 
	
	try {
		item.set_time_values(is);
	}
	catch(...){ // CAN HAVE MULTIPLE ERRORS
		// IF INVALID VALUE, SET BACK TO ORIGINAL VALUE
		item = tmp_time;
		is.setstate(ios::failbit);
	}

	return is;
}

