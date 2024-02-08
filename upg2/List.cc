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
    insert(v,first);
}

void List::insert(int const v,Node* tmp_pointer)
{
    if(tmp_pointer == nullptr)
    {
        cout << "z";
        tmp_pointer = new Node{v, nullptr, nullptr};
        if(first == nullptr)
        {
            first = tmp_pointer;
            last = tmp_pointer;
        }
        else if(first != tmp_pointer)
        {
            tmp_pointer -> previus = last;
            last -> next = tmp_pointer;
            last = tmp_pointer;
                
        }
        return;
    }
    
    if(v <= (tmp_pointer -> value))
    {
        cout << "a";
        // ny Node innan den jag tittar på
        tmp_pointer = new Node{v , tmp_pointer, tmp_pointer};
        (tmp_pointer -> previus) = tmp_pointer;
        return;
    }
    else if(v > (tmp_pointer -> value))
    {
        cout << "b";
        return insert(v, (tmp_pointer -> next));
        
    }
}
