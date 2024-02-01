#ifndef LIST_H
#define LIST_H

#include <vector>

class List 
{

public:
	List(std::vector<int>);

	List();

	
private:
	struct Node {
		int value {};
		Node* next;
		Node* previus;
	}
	
	Node* List_p;
};


#endif
