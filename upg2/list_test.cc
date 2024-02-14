#include "catch.hpp"
#include "List.h"

using namespace std;

TEST_CASE("List")
{

  List l1 {1};
  List l2 {1, 2, 3};
  List l3 {3, 2, 1};
  List l4 {4, 2, 1, -10};
  SECTION("To_string and constructer tests")
    {
      CHECK(l1.to_string() == "1 ");
      CHECK(l2.to_string() == "1 2 3 ");
      CHECK(l3.to_string() == "1 2 3 ");
      CHECK(l4.to_string() == "-10 1 2 4 ");
    }

  SECTION("Insert and remove tests")
    {
      l1.insert(5);
      CHECK(l1.to_string() == "1 5 ");

      l2.insert(0);
      l2.insert(2);
      l2.insert(2);
      CHECK(l2.to_string() == "0 1 2 2 2 3 ");

      l2.remove_node(2);
      CHECK(l2.to_string() == "0 1 2 2 3 "); //Only the first value found gets removed
      
      l1.remove_node(0);
      l1.remove_node(0);
      CHECK_THROWS(l1.remove_node(3));
      CHECK(l1.to_string() == "");
    }

  SECTION("Copy and move tests")
    {
      List l5 {l1};
      List l6 {l3};
      CHECK(l5.to_string() == "1 ");
      CHECK(l3.to_string() == "1 2 3 ");

      l5 = l2;
      CHECK(l5.to_string() == l2.to_string());
    }
  
}
