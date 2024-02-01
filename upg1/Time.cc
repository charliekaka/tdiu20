#include "Time.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

Time::Time(int h=0, int m=0, int s=0)
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
		h+=12;
	}

	check_times();
}

void Time::check_times() const
{
	if(	h>=24 || m>=60 || s>=60 ||
	   	h<0   || m<0   || s<0)
	{
		throw out_of_range("felaktiga tider");
	}
}

string Time::to_string(bool const am_pm_format) const
{
	ostringstream oss {};
	string postfix {};
	int temp_h {h};

	if(am_pm_format){
		if(is_am()){
			postfix = "am";
		}else{
			temp_h -= 12;
			postfix = "pm";
		}
	}

	oss << setw(2) << setfill('0') << temp_h << ":"
	    << setw(2) << setfill('0') << m << ":"
	    << setw(2) << setfill('0') << s << postfix;

	return oss.str();
}

bool Time::is_am() const
{
	return h<13;
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

// PLUS
Time Time::operator+(int const x) const
{
	Time tmp {*this};
	tmp += x;
	return tmp;
}

// PLUS EQUALS
Time& Time::operator+=(int const x)
{
	if(s+x < 0){
		*this-=abs(x);
		return *this;
	}

	s+=x;
	while(s >= 60){
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
	return *this;
}

// MINUS
Time Time::operator-(int const x) const
{
	Time tmp {*this};
	tmp -= x;
	return tmp;
}

// MINUS EQUALS
Time& Time::operator-=(int const x)
{
	if(s-x > 0){
		*this+=abs(x);
		return *this;
	}

	s -= x;
	while(s < 0){
		m--;
		if(m < 0){
			h--;
			m = 59;
			if(h < 0){
				h = 23;
			}
		}
		s+=60;
	}
	return *this;
}

// PRE INCREMENT
Time& Time::operator++()
{
	s++;
	if(s == 60){
		s = 0;
		m++;
		if(m == 60){
			m = 0;
			h++;
			if(h == 24){
				h = 0;
			}
		}
	}
	return *this;
}

// POST INCREMENT
Time Time::operator++(int)
{
	Time tmp {*this};
	++(*this);
	return tmp;
}

// PRE DECREMENT
Time& Time::operator--(){
	s--;
	if(s < 0){
		s = 59;
		m--;
		if(m < 0){
			m = 59;
			h--;
			if(h < 0){
				h = 23;
			}
		}
	}
	return *this;
}

// POST DECREMENT
Time Time::operator--(int){
	Time tmp {*this};
	--(*this);
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

// VALUE SETTER FOR ">>"
void Time::set_time_values(istream& is){
	char c;
	is >> h >> c >> m >> c >> s;
	check_times();
}

// STANDARD OUTPUT
istream& operator>>(istream& is, Time& item){
	item.set_time_values(is);
	return is;
}

