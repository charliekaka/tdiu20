#include "List.h"
#include <vector>

using namespace std;

List::List(vector<int>)
	:List_p {/* Addressen till första Node */}
{
	
}

List::List() 
	: List_p {nullptr}
{
	
}
