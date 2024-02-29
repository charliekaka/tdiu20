#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <string>
#include <sstream>

// Information om komplettering:
//   Kompletteringen kan gälla hela filen och alla filer i labben,
//   så får ni komplettering på en sak, kan samma sak förekomma på
//   fler ställen utan att jag skrivit det.
//
//   Komplettering lämnas in via sendlab efter senast en (1) vecka
//
//   Har ni frågor om kompletteringen kan ni maila mig på:
//   eric.ekstrom@liu.se


// Komplettering: Funktionen för utskrift ska göra utskriften på en given utström.
//Done

// Kommentar: "remove_node" är ett olämpligt namn eftersom det antyder till hur listan
//   är implementerad. Det ska inte synas i den publika delen.
//Done

// Komplettering: Inkludera endast de bibliotek som används.
//Done

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
  
    void remove(int const index);

    
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
  void delete_all(Node* curr_node);
  
};

std::ostream& operator<<(std::ostream& os, List const& list);



#endif
