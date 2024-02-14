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
      remove_node(length() - 1);
    }
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
      remove_node(length() - 1);
    }

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

int List::at(int const i)
{
  Node* node = first;

  for(int j = 0; j < i; j++)
    {
      if(node == nullptr) throw out_of_range("Index to high");
      node = node -> next;
    }
  return node -> value;
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

void List::insert(int const v,Node* node_pointer)
{
    if(node_pointer == nullptr)
    {
        node_pointer = new Node{v, nullptr, last};
        last -> next = node_pointer;
        last = node_pointer;
        return;
    }
    
    if(v <= (node_pointer -> value))
    {
        // new Node before the one node_pointer is on
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
        return insert(v, (node_pointer -> next));        
    }
}
