#include "catch.hpp"
#include "Time.h"
#include <sstream>

using namespace std;

TEST_CASE ("Constructors and getters")
{
   SECTION("Default")
   {
      Time empty{};
      CHECK(empty.get_hour() == 0 );
      CHECK(empty.get_minute() == 0 );
      CHECK(empty.get_second() == 0 );
   }

   SECTION("Integer")
   {
      Time t0{0,0,0};
      Time t1{12,30,30};
      Time t2{23,59,59};

      CHECK_THROWS(Time{13,35,60});
      CHECK_THROWS(Time{13,60,35});
      CHECK_THROWS(Time{24,35,35});
             
      CHECK(t0.get_hour() == 0);
      CHECK(t0.get_minute() == 0);
      CHECK(t0.get_second() == 0);
      CHECK(t1.get_hour() == 12);
      CHECK(t1.get_minute() == 30);
      CHECK(t1.get_second() == 30);
      CHECK(t2.get_hour() == 23);
      CHECK(t2.get_minute() == 59);
      CHECK(t2.get_second() == 59);
   }

   SECTION("String")
   {
      Time t0{"00:00:00"};
      Time t1{"12:30:30"};
      Time t2{"23:59:59"};

      CHECK_THROWS(Time{"13:35:60"});
      CHECK_THROWS(Time{"13:60:35"});
      CHECK_THROWS(Time{"24:35:35"});

      CHECK(t0.get_hour() == 0);
      CHECK(t0.get_minute() == 0);
      CHECK(t0.get_second() == 0);
      CHECK(t1.get_hour() == 12);
      CHECK(t1.get_minute() == 30);
      CHECK(t1.get_second() == 30);
      CHECK(t2.get_hour() == 23);
      CHECK(t2.get_minute() == 59);
      CHECK(t2.get_second() == 59);  
   }
}

TEST_CASE ("is_am") 
{
	Time t0 {"00:00:00"};
	Time t1 {"00:59:59"};
	Time t2 {"01:00:00"};
	Time t3 {"11:59:59"};

	Time t4 {"12:00:00"};
	Time t5 {"12:59:59"};
	Time t6 {"13:00:00"};
	Time t7 {"23:59:59"};

	CHECK(t0.is_am());
	CHECK(t1.is_am());
	CHECK(t2.is_am());
	CHECK(t3.is_am());

	CHECK_FALSE(t4.is_am());
	CHECK_FALSE(t5.is_am());
	CHECK_FALSE(t6.is_am());
	CHECK_FALSE(t7.is_am());
}


TEST_CASE ("to_string")
{
   Time t0 {};
   Time t1 {"00:59:59"};
   Time t2 {"01:00:00"};
   Time t3 {"11:59:59"};
   Time t4 {"12:00:00"};
   Time t5 {"12:59:59"};
   Time t6 {"13:00:00"};
   Time t7 {"23:59:59"};

   SECTION("24 hour format no argument")
   {
      CHECK(t0.to_string() == "00:00:00");
      CHECK(t1.to_string() == "00:59:59");
      CHECK(t2.to_string() == "01:00:00");
      CHECK(t3.to_string() == "11:59:59");
      CHECK(t4.to_string() == "12:00:00");
   }
   
   SECTION("24 hour format with argument")
   {
      CHECK(t0.to_string(false) == "00:00:00");
      CHECK(t1.to_string(false) == "00:59:59");
      CHECK(t2.to_string(false) == "01:00:00");
      CHECK(t3.to_string(false) == "11:59:59");
      CHECK(t4.to_string(false) == "12:00:00");
   } 

   SECTION("12 hour format")
   {
      CHECK(t0.to_string(true) == "12:00:00am");
      CHECK(t1.to_string(true) == "12:59:59am");
      CHECK(t2.to_string(true) == "01:00:00am");
      CHECK(t3.to_string(true) == "11:59:59am");
      CHECK(t4.to_string(true) == "12:00:00pm");
      CHECK(t5.to_string(true) == "12:59:59pm");
      CHECK(t6.to_string(true) == "01:00:00pm");
      CHECK(t7.to_string(true) == "11:59:59pm");
   }
}

TEST_CASE("operator")
{
   Time t0{};
   Time t1{11, 59, 59};
   Time t2{12, 0, 0};
   Time t3{23, 59, 59};
   Time t4{0, 59, 59};

   SECTION("==")
   {
	CHECK(t1 == t1);
	CHECK_FALSE(t1 == t2);
   }

   SECTION("!=")
   {
	CHECK(t1 != t2);
	CHECK(t0 != t3);
   }

   SECTION("<")
   {
	CHECK(t1 < t2);
	CHECK(t0 < t3);
	CHECK_FALSE(t3 < t0);
	CHECK_FALSE(t2 < t2);

	CHECK(t2 <= t2);
   }

   SECTION(">")
   {
	CHECK(t2 > t0);
	CHECK(t2 > t1);
	CHECK_FALSE(t1 > t2);
	CHECK_FALSE(t0 > t0);

	CHECK(t2 >= t2);
   }

   SECTION("<<")
   {
	stringstream output1;
	stringstream output2;
	stringstream output3;

	output1 << t1;
	output2 << t2;
	output3 << t0;
	CHECK(output1.str() == "11:59:59");
	CHECK(output2.str() == "12:00:00");
	CHECK(output3.str() == "00:00:00");
   }

   SECTION(">>"){
	stringstream input0 {"10:10:10"};
	stringstream input1 {"00:04:00"};
	stringstream input2 {"40:04:00"};

	input0 >> t0;
	input1 >> t1;
	input2 >> t2;

	CHECK(t0.to_string() == "10:10:10");
	CHECK(t1.to_string() == "00:04:00");
	CHECK(t2.to_string() == "12:00:00"); // Behåller sitt originella värde då ogiltigt värde matas in
   }

   SECTION("++")
   {
	   Time t1res {12, 0, 0};

	   CHECK_FALSE(++t2 == t2++);
	   CHECK_FALSE(t0++ == t0);
	   CHECK(++t1 == t1res);
	   t3++;
	   ++t4;
	   CHECK(t3.to_string() == "00:00:00");
	   CHECK(t4.to_string() == "01:00:00");
   }
   
   SECTION("--")
   {
	   Time t1res {11, 59, 58};

	   CHECK_FALSE(--t2 == t2--);
	   CHECK_FALSE(t0-- == t0);
	   CHECK(--t1 == t1res);
	   t3--;
	   --t4;
	   CHECK(t3.to_string() == "23:59:58");
	   CHECK(t4.to_string() == "00:59:58");
   }


   SECTION("+")
   {
	Time t0t {t0+305};

	CHECK(t0t.to_string() == "00:05:05");
	CHECK(1+t1 == t2);
	CHECK(t1+1 == t2);
	CHECK(1+t3 == t0);
   }

   SECTION("+=")
   {
	t0 += 60;
	t1 += 61;
	t2 += -30;
	t3 += 11;
	t4 += -60;

	CHECK(t0.to_string() == "00:01:00");
	CHECK(t1.to_string() == "12:01:00");
	CHECK(t2.to_string() == "11:59:30");
	CHECK(t3.to_string() == "00:00:10");
	CHECK(t4.to_string() == "00:58:59");
   }

   SECTION("-")
   {
	Time t0t {t0-10};

	CHECK(t0t.to_string() == "23:59:50");
	CHECK(-1-t1 == t2);
	CHECK(t1-(-1) == t2);
	CHECK(-1-t3 == t0);
   }

   SECTION("-=")
   {
	t0 -= 60;
	t1 -= 9;
	t2 -= -30;
	t3 -= -11;
	t4 -= 60;

	CHECK(t0.to_string() == "23:59:00");
	CHECK(t1.to_string() == "11:59:50");
	CHECK(t2.to_string() == "12:00:30");
	CHECK(t3.to_string() == "00:00:10");
	CHECK(t4.to_string() == "00:58:59");
   }
}

