#include "catch.hpp"
#include "List.h"

using namespace std;

TEST_CASE("List")
{
    SECTION("LISTening")
    {
        List l1 {1};
        List l2 {1, 2, 3};
        List l3 {3, 2, 1};
	List l4 {4, 2, 1, -10};
        CHECK(l1.to_string() == "1 ");
        CHECK(l2.to_string() == "1 2 3 ");
        CHECK(l3.to_string() == "1 2 3 ");

        l1.insert(5);
        CHECK(l1.to_string() == "1 5 ");

        l2.insert(0);
        CHECK(l2.to_string() == "0 1 2 3 ");
    }
}
