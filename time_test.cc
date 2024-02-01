#include "catch.hpp"
#include "Time.h"
#include "sstream"

using namespace std;

TEST_CASE ("Constructors and getters")
{
   SECTION("Default")
   {
      Time empty{};
      CHECK( empty.get_hour()   == 0 );
      CHECK( empty.get_minute() == 0 );
      CHECK( empty.get_second() == 0 );
   }

   SECTION("Integer")
   {
      Time t0{0,0,0};
      Time t1{12,30,30};
      Time t2{23,59,59};

      CHECK_THROWS( Time{13,35,60} );
      CHECK_THROWS( Time{13,60,35} );
      CHECK_THROWS( Time{24,35,35} );
             
      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 );
   }

   SECTION("String")
   {
      Time t0{"00:00:00"};
      Time t1{"12:30:30"};
      Time t2{"23:59:59"};

      CHECK_THROWS( Time{"13:35:60"} );
      CHECK_THROWS( Time{"13:60:35"} );
      CHECK_THROWS( Time{"24:35:35"} );

      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 );  
   }
}

TEST_CASE ("is_am") 
{
   Time t0{"05:00:00"};
   Time t1{"14:00:00"};
   Time t2(12, 05, 10);
   Time t3("11:05:10");
   Time t4("05:00:00pm");
   Time t5("05:00:00am");
   CHECK       ( t0.is_am() );
   CHECK_FALSE ( t1.is_am() );
   CHECK	(t2.is_am() );
   CHECK       (t3.is_am() );
   CHECK_FALSE(t4.is_am());
   CHECK(t5.is_am());
}


TEST_CASE ("to_string")
{
   Time t0{};
   Time t1{11, 59, 59};
   Time t2{12, 0, 0};
   Time t3{13, 0, 0};
   Time t4{23, 59, 59};
   SECTION("24 hour format no argument")
   {
      CHECK(t0.to_string() == "00:00:00");
      CHECK(t1.to_string() == "11:59:59");
      CHECK(t2.to_string() == "12:00:00");
      CHECK(t3.to_string() == "13:00:00");
      CHECK(t4.to_string() == "23:59:59");
   }
   
   SECTION("24 hour format with argument")
   {
      CHECK(t0.to_string(false) == "00:00:00");
      CHECK(t1.to_string(false) == "11:59:59");
      CHECK(t2.to_string(false) == "12:00:00");
      CHECK(t3.to_string(false) == "13:00:00");
      CHECK(t4.to_string(false) == "23:59:59");
   } 

   SECTION("12 hour format")
   {
      CHECK(t0.to_string(true) == "00:00:00am");
      CHECK(t1.to_string(true) == "11:59:59am");
      CHECK(t2.to_string(true) == "12:00:00am");
      CHECK(t3.to_string(true) == "01:00:00pm");
      CHECK(t4.to_string(true) == "11:59:59pm");
   }
}

TEST_CASE("operator")
{
   Time t0{};
   Time t1{11, 59, 59};
   Time t2{12, 0, 0};
   Time t3{23, 59, 59};

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
	output1 << t1;
	CHECK(output1.str() == "11:59:59");
   }

   Time obj1 {};
   Time obj2 {23, 59, 59};
   Time obj3 {13, 37, 13};
   SECTION(">>"){
	stringstream input1 {"10:10:10"};
	stringstream input2 {"00:04:00"};
	stringstream input3 {"50:04:00"};

	input1 >> obj1;
	input2 >> obj2;

	CHECK(obj1.to_string() == "10:10:10");
	CHECK(obj2.to_string() == "00:04:00");
	CHECK_THROWS(input3 >> obj3);
   }

   SECTION("++")
   {
	t0++;
	CHECK(t0.to_string() == "00:00:01");
	t1++;
	CHECK(t1.to_string() == "12:00:00");
	++t2;
	CHECK(t2.to_string() == "12:00:01");
	++t3;
	CHECK(t3.to_string() == "00:00:00");
   }
   
   Time t4{};
   Time t5{11, 0, 59};
   Time t6{12, 0, 0};
   Time t7{13, 0, 0};

   SECTION("--")
   {
	t4--;
	CHECK(t4.to_string() == "23:59:59");
	t5--;
	CHECK(t5.to_string() == "11:00:58");
	--t6;
	CHECK(t6.to_string() == "11:59:59");
	--t7;
	CHECK(t7.to_string() == "12:59:59");
   }

   Time t8{};
   Time t9{11, 0, 59};
   Time t10{23, 59, 50};
   Time t11{1, 5, 0};

   SECTION("+")
   {
	CHECK((t8+5).to_string() == "00:00:05");
	CHECK((t9+20).to_string() == "11:01:19");
	CHECK((t10+10).to_string() == "00:00:00");
	CHECK((t11+(-600)).to_string() == "00:55:00");
   }

   SECTION("+=")
   {
	t8 += 5;
	t9 += 20;
	t10 += 10;
	t11 += (-600);
	
	CHECK((t8).to_string() == "00:00:05");
	CHECK((t9).to_string() == "11:01:19");
	CHECK((t10).to_string() == "00:00:00");
	CHECK((t11).to_string() == "00:55:00");
   }

   Time t12{};
   Time t13{11, 0, 59};
   Time t14{23, 59, 50};
   Time t15{1, 5, 0};

   SECTION("-")
   {
	CHECK((t12-1).to_string() == "23:59:59");
	CHECK((t13-60).to_string() == "10:59:59");
	CHECK((t14-(-10)).to_string() == "00:00:00");
	CHECK((t15-5).to_string() == "01:04:55");
   }

   SECTION("-=")
   {
	t12-=1;
	t13-=60;
	t14-=(-10);
	t15-=5;

	CHECK(t12.to_string() == "23:59:59");
	CHECK(t13.to_string() == "10:59:59");
	CHECK(t14.to_string() == "00:00:00");
	CHECK(t15.to_string() == "01:04:55");
   }
}

