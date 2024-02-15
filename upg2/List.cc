#include "List.h"
#include <vector>
#include <initializer_list>
#include <string>
#include <sstream>
#include <iostream>
#include <exception>

using namespace std;

List::List(initializer_list<int> list)
    :first {} , last{}
{
    for (int value : list)
    {
        insert(value);
    }
}

List::List() 
    :first {nullptr}, last {nullptr}
{
}

List::~List()
{
    while(first != nullptr)
    {
        Node* node = first;
        first = first -> next;
        delete node;
    }
    last = nullptr;
}

List::List(List const& other)
    : first{}, last{}
{
    Node* other_curr = other.first;

    while(other_curr != nullptr)
    {
        insert(other_curr -> value);
        other_curr = other_curr -> next;
    }
}

List& List::operator=(List const& other)
{
    while(first != nullptr)
    {
        Node* node = first;
        first = first -> next;
        delete node;
    }
    last = nullptr;

    Node* other_curr = other.first;
  
    while(other_curr != nullptr)
    {
        insert(other_curr -> value);
        other_curr = other_curr -> next;
    }
  
    return *this;
}

List::List(List && other)
    :first{other.first}, last{other.last}
{
    other.first = nullptr;
    other.last = nullptr;
}

List& List::operator=(List && other)
{
    swap(first, other.first);
    swap(last, other.last);
    return *this;
}

string List::to_string() const
{
    ostringstream oss {};
    Node* tmp {first};

    while(tmp != nullptr)
    {
        
        oss << tmp -> value << ' ';
        tmp = tmp -> next;
    }

    return oss.str();
}

List List::sub(initializer_list<int> list)
{
    List l2{};
    Node* curr_node {first};
    Node* curr_l2_node {};
    int curr_index {};
    
    for(int index : list)
    {
        while(index != curr_index)
        {
            if(index < curr_index) throw invalid_argument("You have to put the index in rising order");
            if(curr_node == nullptr) throw out_of_range("Index does not exsist");
            curr_index++;
            curr_node = curr_node -> next;
            
        }

        if( l2.first == nullptr )
        {
            l2.first = new Node{curr_node -> value, nullptr, nullptr};
            l2.last = l2.first;
            curr_l2_node = l2.first;
        }
        else if(curr_l2_node == l2.last)
        {
            curr_l2_node = new Node{curr_node -> value, nullptr, l2.last};
            l2.last -> next = curr_l2_node;
            l2.last = curr_l2_node;
        }
       
    }

    swap(first, l2.first);

    swap(last, l2.last);

    return *this;
    
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

int List::length() const
{
    Node* node = first;
    int len {};
    while(node != nullptr)
    {
        len ++;
        node = node -> next;
    }
    return len;
}

int List::at(int const index) const
{
    Node* node = first;
    int curr_index {};
    while(node != nullptr)
    {
        if(index == curr_index) return node -> value;
        node = node -> next;
        curr_index++;
    }
    throw out_of_range("index to high");
}

void List::remove_node(int const index)
{
    Node* node = first;
    int lap {0};
    while(node != nullptr)
    {
        if(lap == index)
	{
            if(node != first && node != last)
	    {
                node -> next -> previus = node -> previus;
                node -> previus -> next = node -> next;
	    }
	  
            if(first == node)
	    {
                if(node -> next != nullptr) node -> next -> previus = nullptr;
                first = node -> next;
	    }
            if(last == node)
	    {
                if(node -> previus != nullptr) node -> previus -> next = nullptr;
                last = node -> previus;
	    }

            delete node;
            return;
	}
        node = node -> next;
        lap++;
    }
    throw out_of_range("The index is to high");
}

void List::insert(int const v,Node* node)
{
    if(node == nullptr)
    {
        node = new Node{v, nullptr, last};
        last -> next = node;
        last = node;
        return;
    }
    
    if(v <= (node -> value))
    {
        // new Node before the one node_pointer is on
        Node* new_node = new Node{v ,node, node -> previus };
        if(node == first)
        {
            first = new_node;
        }
        else
        {
            new_node -> previus -> next = new_node; 
        }
	node -> previus = new_node;     
        return;
    }
    else if(v > (node -> value))
    {
        return insert(v, (node -> next));        
    }
}
