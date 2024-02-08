#ifndef LIST_H
#define LIST_H

#include <vector>
#include <initializer_list>
#include <string>

class List 
{

public:
    List(std::initializer_list<int> l);
    
    List();
    
    void insert(int const v);

    std::string to_string() const;
private:
    struct Node
    {
        int value {};
        Node* next;
        Node* previus;
    };
	
    Node* first;
    Node* last;
    
    void insert(int const v, Node* tmp_pointer);
};


#endif
