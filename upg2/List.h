#ifndef LIST_H
#define LIST_H

#include <vector>
#include <initializer_list>
#include <string>

class List 
{

public:
    List(std::initializer_list<int> list);
    List();

    ~List();
  
    List(List const& other);
    List& operator=(List const& other);

    List(List && other);
    List& operator=(List && other);

    std::string to_string() const;
    
    List sub(std::initializer_list<int> list);
  
    void insert(int const v);

    int length() const;

    int at(int const index) const;
  
    void remove_node(int const index);
    
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
