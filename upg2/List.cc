#include "List.h"
#include <vector>
#include <initializer_list>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

List::List(initializer_list<int> list)
    :first {} , last{}
{
    for (int value : list)
    {
        insert(value);
        
        cout << "x";
    }
}

List::List() 
    :first {nullptr}, last {nullptr}
{
	
}

string List::to_string() const
{
    stringstream ss {};
    Node* tmp {first};

    while(tmp != nullptr)
    {
        
        ss << tmp -> value << ' ';
        tmp = tmp -> next;
        cout << "y";
    }

    return ss.str();
}

void List::insert(int const v)
{
    if( first == nullptr )
    {
        first = new Node{v, nullptr, nullptr};
        last = first;
    }
    else
    {
        insert(v,first);
    }
}

void List::insert(int const v,Node* node_pointer)
{
    if(node_pointer == nullptr)
    {
        cout << "z";
        node_pointer = new Node{v, nullptr, last};
        last -> next = node_pointer;
        last = node_pointer;
        return;
    }
    
    if(v <= (node_pointer -> value))
    {
        // ny Node innan den jag tittar på
        Node* new_node = new Node{v ,node_pointer, node_pointer -> previus };
        if(node_pointer == first)
        {
            first = new_node;
        }
        else
        {
            new_node -> previus -> next = new_node; 
        }
	node_pointer -> previus = new_node;     
        return;
    }
    else if(v > (node_pointer -> value))
    {
        cout << "b";
        return insert(v, (node_pointer -> next));
        
    }
}
