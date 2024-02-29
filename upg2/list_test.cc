#include "catch.hpp"
#include "List.h"
#include "sstream"

using namespace std;

// Komplettering: En testfil ska pröva de funktioner som
// ni har skapat. Det innebär att man vill pröva alla
// möjliga fall (även specialfall). Vi vill ju vara säkra
// på att vi har en funktion som fungerar. En bra fråga är:
// "Övertygar detta den som rättar att er funktion
// fungerar utan att kolla i List.cc-filen?"

// Komplettering: Det saknar tester för insättning/borttagning/åtkomst. Ni behöver testa alla olika
//   fall som kan uppstå. Tex insättning först, sist, i mitten och i tom lista.
// Done ish

TEST_CASE("List")
{
  List l0 {};
    List l1 {1};
    List l2 {1, 2, 3};
    List l3 {3, 2, 1};
    List l4 {4, 2, 1, -10};
    
    
    SECTION("To_string and constructer tests")
    {
      stringstream output0;
      stringstream output1;
      stringstream output2;
      stringstream output3;
      stringstream output4;

      output0 << l0;
      output1 << l1;
      output2 << l2;
      output3 << l3;
      output4 << l4;

      CHECK(output0.str() == "");
      CHECK(output1.str() == "1 ");
      CHECK(output2.str() == "1 2 3 ");
      CHECK(output3.str() == "1 2 3 ");
      CHECK(output4.str() == "-10 1 2 4 ");
    }

    SECTION("Insert and remove tests")
    {
      l0.insert(1000); //Insert tom lista
      CHECK(l0.to_string() == "1000 ");
      
      l1.insert(5); //Insert sist
      CHECK(l1.to_string() == "1 5 ");

      l2.insert(0); //Insert först
      l2.insert(2); //Insert i mitten
      l2.insert(2); //Insert i mitten
      CHECK(l2.to_string() == "0 1 2 2 2 3 ");

      l2.remove(2); //Remove i mitten
      CHECK(l2.to_string() == "0 1 2 2 3 ");
      
      l1.remove(0); //Remove först
      l1.remove(0); //Remove med ett objekt i listan
      CHECK_THROWS(l1.remove(3)); //Remove tom lista
      CHECK(l1.to_string() == ""); //Se att listan är tom

      l2.remove(4); //Remove sist
      CHECK_THROWS(l2.remove(4)); //Remove utanför index
      CHECK(l2.to_string() == "0 1 2 2 ");
      
    }

    SECTION("Copy and move tests")
    {
        List l5 {l1};
        List l6 {l3};
        CHECK(l5.to_string() == "1 ");
	l1.insert(30);//Kontroll djup kopiering
	CHECK(l1.to_string() == "1 30 ");

	l3.insert(30);//Kontroll djup kopiering
	CHECK(l3.to_string() == "1 2 3 30 ");
        CHECK(l6.to_string() == "1 2 3 ");

        l5 = l2;
        CHECK(l5.to_string() == l2.to_string());
        l5.insert(3); //Kontroll djup kopiering
        CHECK(l5.to_string() == "1 2 3 3 ");
	CHECK(l2.to_string() == "1 2 3 ");

        List l7 {move(l5)};
        CHECK(l5.to_string() == "");
        CHECK(l7.to_string() == "1 2 3 3 ");

        l7 = move(l2);
        CHECK(l2.to_string() == "1 2 3 3 ");
        CHECK(l7.to_string() == "1 2 3 ");
    }

    SECTION("Length and at index tests")
    {
        CHECK(l4.length() == 4);
        l4.insert(3);
        CHECK(l4.length() == 5);

	//CHECK(output4.str() == "-10 1 2 4 ");

	
        CHECK(l4.at(2) == 2);
        CHECK(l4.at(0) == -10);
        CHECK_THROWS(l4.at(5));
        CHECK_THROWS(l4.at(10));
      
    }
    
    List s1 {-5, 0, 0, 2225, -2333, 11, -11};
    List s2 {5,5,5};
    List s3 {1,2,5};

    SECTION("Sub function tests")
    {
        List sub_list{l4.sub({0,1})};
	List sl1;
	List sl2 {s2.sub({0,1,1,2})};
	List sl3 {s3.sub({0})};

        
        CHECK(sub_list.to_string() == "-10 1 ");
	CHECK_THROWS(sl1.sub({1,0}));
	CHECK_THROWS(sl1.sub({1,99}));
	CHECK(sl2.to_string() == "5 5 5 5 ");
	CHECK(sl3.to_string() == "1 ");

        
    }
  
}
