/*****************************************
** File: Map.cpp
** Project: Runescape Crafting
** Author: Vidal Bickersteth
** Date: 5/3/25
**
** This program is the Map.cpp file of Runescape Crafting Project.
** This is a templated class. 
** This file allows you to Update, Insert, or Display your node
** You can also get your Node or your key's value.
** This file contains Nodes, which are linked lists.
** You can check if a Node is empty or not
** Map ultilizes Nodes to create Map objects and a hero's inventory.
** Map is crucial for Hero.
**
**
***********************************************/

#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <stdexcept>
#include "Node.cpp"
using namespace std;

template <typename K, typename V>
class Map {
public:
  // Name: Map()
  // Description: Default constructs an empty map.
  // Preconditions: None.
  // Postconditions: m_head is set to nullptr; m_size is initialized to 0.
  Map();
  // Name: ~Map()
  // Description: Destroys the map, freeing all nodes.
  // Preconditions: None.
  // Postconditions: All nodes are deleted; m_head is nullptr; m_size is 0.
  ~Map();
  // Name: Map(const Map& other)
  // Description: Copy constructor; deep copies another map’s contents.
  // Preconditions: other must be a valid Map<K,V>.
  // Postconditions: This map contains the same key/value pairs, in order.
  Map(const Map& other);
  // Name: operator=(const Map& other)
  // Description: Assignment operator; clears this map and deep copies other.
  // Preconditions: other is a valid Map<K,V>; self-assignment is handled.
  // Postconditions: This map contains a copy of other’s elements.
  Map<K,V>& operator=(const Map& other);
  // Name: Insert(const K& key, const V& value)
  // Description: Inserts or updates a key → value pair, keeping
  //              nodes ordered by key.
  // Preconditions: key and value are valid; map may be empty.
  // Postconditions: New node inserted at sorted position, or
  //                 existing node’s value updated; m_size adjusted.
  void Insert(const K& key, const V& value);
  // Name: Update(const K& key, const V& value)
  // Description: Changes the value for an existing key.
  // Preconditions: key must exist in the map.
  // Postconditions: Corresponding node’s value is set to
  //                 value; throws out_of_range if key not found.
  void Update(const K& key, const V& value);
  // Name: ValueAt(const K& key) const
  // Description: Retrieves a const reference to the value for key.
  // Preconditions: key must exist in the map.
  // Postconditions: Returns reference to the value;
  //                 throws out_of_range if not found.
  const V& ValueAt(const K& key) const;
  // Name: At(const K& key) const
  // Description: Returns a pointer to the node for key.
  // Preconditions: key must exist in the map.
  // Postconditions: Returns pointer to the Node<K,V>;
  //                 throws out_of_range if not found.
  Node<K,V>* At(const K& key) const;
  // Name: GetSize() const
  // Description: Reports the number of key‑value pairs in the map.
  // Preconditions: None.
  // Postconditions: Returns the value of m_size.
  int GetSize() const;
  // Name: IsEmpty() const
  // Description: Checks whether the map contains no elements.
  // Preconditions: None.
  // Postconditions: Returns true if m_size == 0
  //                 (m_head == nullptr); false otherwise.
  bool IsEmpty() const;
  // Name: Display() const
  // Description: Prints each key:value pair to cout, one per line.
  // Preconditions: ostream cout is available.
  // Postconditions: Map contents are written to standard output.
  void Display() const;
  // Name: operator<<
  // Description: Streams all key:value pairs into os, one per line.
  // Preconditions: os is a valid ostream; map is a valid Map<K,V>.
  // Postconditions: os contains serialized map contents;
  //                returns os by reference.
  // PROVIDED
  friend ostream& operator<<(ostream& os, const Map<K, V>& map){
    Node<K,V>* current = map.m_head; //The first Node
    //Overloads the operator <<
    while (current != nullptr) {
      os << current->GetKey() << ":" << current->GetValue() << endl;
      current = current->GetNext();
    }
    return os;
  }
private:
  // Name: Clear()
  // Description: Deletes all nodes in the linked list,
  //              freeing their memory and resetting the map.
  // Preconditions: None.
  // Postconditions: All dynamically allocated nodes are deleted;
  //                 m_head is set to nullptr; m_size is reset to 0.
  void Clear();  
  Node<K,V>* m_head; //Pointer to the first node in the Map
  int m_size; //Tracks the size of the Map (number of nodes)
};
#endif

// Name: Map()
// Description: Default constructs an empty map.
// Preconditions: None.
// Postconditions: m_head is set to nullptr; m_size is initialized to 0.
template <typename K, typename V>
Map<K,V>::Map(){
  //Default values initialized
  m_head = nullptr;
  m_size = 0;
}

// Name: ~Map()
// Description: Destroys the map, freeing all nodes.
// Preconditions: None.
// Postconditions: All nodes are deleted; m_head is nullptr; m_size is 0.
template <typename K, typename V>
Map<K,V>::~Map(){
  Node<K,V> *curr = m_head; // The current node
  //Dynamically deallocates all memory of the linked list
  while(curr != nullptr){
    m_head = m_head -> GetNext();
    delete curr;
    curr = m_head;
  }
  //Sets to nullptr and 0 for m_size
  m_head = nullptr;
  m_size = 0;
}

// Name: Map(const Map& other)
// Description: Copy constructor; deep copies another map’s contents.
// Preconditions: other must be a valid Map<K,V>.
// Postconditions: This map contains the same key/value pairs, in order.
template <typename K, typename V>
Map<K,V>::Map(const Map& other){
  Node<K,V> *curr = other.m_head; // The other map current node
  //If empty, then all variables are set to it's default values
  if(other.GetSize() == 0){
    m_head = nullptr;
    m_size = 0;
  }else{
    //If not empty, all variables are initialized and deep copies another map's nodes.
    m_head = nullptr;
    m_size = 0;
    while(curr != nullptr){
      Insert(curr -> GetKey(), curr -> GetValue());
      curr = curr -> GetNext();
    }
  }
}

// Name: Clear()
// Description: Deletes all nodes in the linked list,
//              freeing their memory and resetting the map.
// Preconditions: None.
// Postconditions: All dynamically allocated nodes are deleted;
//                 m_head is set to nullptr; m_size is reset to 0.
template <typename K, typename V>
void Map<K,V>::Clear(){
  Node<K,V> *curr = m_head; // The map's current node
  //Dynamically deallocates all memory
  while(curr != nullptr){
    curr = curr -> GetNext();
    delete curr;    
    curr = nullptr;
  }
  //Variables are set to their default values
  m_head = nullptr;
  m_size = 0;
}

// Name: Insert(const K& key, const V& value)
// Description: Inserts or updates a key → value pair, keeping
//              nodes ordered by key.
// Preconditions: key and value are valid; map may be empty.
// Postconditions: New node inserted at sorted position, or
//                 existing node’s value updated; m_size adjusted.
template <typename K, typename V>
void Map<K,V>::Insert(const K& key, const V& value){
  Node<K,V> *temp = new Node(key, value); // The new node
  Node<K,V> *curr = m_head; // The current node
  Node<K,V> *prev = m_head; // The previous node
  //If map is empty, then the new node becomes the first node of map
  if(IsEmpty()){
    m_head = temp;
    m_size++;
  }else if(GetSize() == 1){
    //If the map only have one element
    //then the new node is set to next node after current node
    //if the key of the new node is greater than the current's key
    if(temp -> GetKey() > curr -> GetKey()){
      curr -> SetNext(temp);
      m_size++;
    }else{
      temp -> SetNext(curr);
      m_head = temp;
      m_size++;
    }
  }else{
    //If the map have multiple elements and the key is greater, 
    // than the curr node, then new node gets added before 
    // the current node key
    if(temp -> GetKey() < curr -> GetKey()){
      temp -> SetNext(curr);
      m_head = temp;
      m_size++;
    }else{
    //Traverses through the linked list 
    //To ensure that the new node gets added after
    //the current node
      while(curr -> GetNext() != nullptr
          && (temp -> GetKey() > curr -> GetKey())){
          prev = curr;
          curr = curr -> GetNext();
      }
      //If the new node key is greater than the curr key
      //then new node gets added as the last node.
      //otherwise, becomes the second-to-last node.
      if(curr -> GetNext() == nullptr){
        if(temp -> GetKey() > curr -> GetKey()){
          curr -> SetNext(temp);
          prev -> SetNext(curr);
          m_size++;
        }else{
          temp -> SetNext(curr);
          prev -> SetNext(temp);
          m_size++;
        }
      }else{
        //Handles the placing of nodes at the middle/between
        //of the linked list
        prev -> SetNext(temp);
        temp -> SetNext(curr);
        m_size++;
      }
    }
  }
}

// Name: operator=(const Map& other)
// Description: Assignment operator; clears this map and deep copies other.
// Preconditions: other is a valid Map<K,V>; self-assignment is handled.
// Postconditions: This map contains a copy of other’s elements.
template <typename K, typename V>
Map<K,V>& Map<K,V>::operator=(const Map& other){
  Node<K,V> *curr = other.m_head; //The other map's first Node
  //If both maps are the same, then the first map gets returned
  if(this == &other){
    return *this;
  //If the other map is empty, then current map gets cleared
  }else if(other.GetSize() == 0){
    Clear();
    m_head = nullptr;
  }else{
    //Deeps copies the other map 
    //Then current map becomes the other map
    Clear();
    while(curr != nullptr){
      Insert(curr -> GetKey(), curr -> GetValue());
      curr = curr -> GetNext();
    }
    return *this;
  }
  return *this;
}

// Name: Update(const K& key, const V& value)
// Description: Changes the value for an existing key.
// Preconditions: key must exist in the map.
// Postconditions: Corresponding node’s value is set to
//                 value; throws out_of_range if key not found.
template <typename K, typename V>
void Map<K,V>::Update(const K& key, const V& value){
  Node<K,V> *curr = m_head; // The first node
  int counter = 0; // The counter
  //If the map is empty, then a out_of_range error gets thrown
  if(IsEmpty()){
    throw out_of_range("There is no map to update");
  }else if(m_size == 1){
    //If only one node, then the first node stores the new value
    m_head -> SetValue(value);
  }else{
    //Traverses through the linked list
    //Until it finds the key that the user
    //wants to update with a new value
    while(curr != nullptr){
      if(curr -> GetKey() == key){
        curr -> SetValue(value);
        counter++;
      }
      curr = curr -> GetNext();
    }
    //If key not found, then an out_of_range error gets thrown
    if(counter <= 0){
      throw out_of_range("Your key does not exist");
    }
  }
}

// Name: ValueAt(const K& key) const
// Description: Retrieves a const reference to the value for key.
// Preconditions: key must exist in the map.
// Postconditions: Returns reference to the value;
//                 throws out_of_range if not found.
template <typename K, typename V>
const V& Map<K,V>::ValueAt(const K& key) const{
  Node<K,V> *curr = m_head; // The first node
  //If the map is empty, then a out_of_range error gets thrown
  if(IsEmpty()){
    throw out_of_range("There is no map to find value");
  }
  //Traverses through the linked list
  //Until it finds the key that the user
  //wants to get it's value
  while(curr != nullptr){
    if(curr -> GetKey() == key){
      return curr -> GetValue();
    }
    curr = curr -> GetNext();
  }
  //If key not found, then an out_of_range error gets thrown
  throw out_of_range("Your key does not exist in the map");
}

// Name: At(const K& key) const
// Description: Returns a pointer to the node for key.
// Preconditions: key must exist in the map.
// Postconditions: Returns pointer to the Node<K,V>;
//                 throws out_of_range if not found.
template <typename K, typename V>
Node<K,V>* Map<K,V>::At(const K& key) const{
  Node<K,V> *curr = m_head; // The first node
  //If the map is empty, then a out_of_range error gets thrown
  if(IsEmpty()){
    throw out_of_range("There is no map to find at");
  }
  //If only one node, then that node gets returned
  if(m_size == 1){
    return m_head;
  }
  //Traverses through the linked list
  //Until it finds the key that the user wants to access
  while(curr != nullptr){
    if(curr -> GetKey() == key){
      return curr;
    }
    curr = curr -> GetNext();
  }
  //If key not found, then an out_of_range error gets thrown
  throw out_of_range("Your key does not exist in the map");
}

// Name: GetSize() const
// Description: Reports the number of key‑value pairs in the map.
// Preconditions: None.
// Postconditions: Returns the value of m_size.
template <typename K, typename V>
int Map<K,V>::GetSize() const{
  //Returns the size of the map
  return m_size;
}

// Name: IsEmpty() const
// Description: Checks whether the map contains no elements.
// Preconditions: None.
// Postconditions: Returns true if m_size == 0
//                 (m_head == nullptr); false otherwise.
template <typename K, typename V>
bool Map<K,V>::IsEmpty() const{
  //If there's no node or size is zero, then the map must be empty
  if(m_size == 0 || m_head == nullptr){
    return true;
  }else{
    return false;
  }
}

// Name: Display() const
// Description: Prints each key:value pair to cout, one per line.
// Preconditions: ostream cout is available.
// Postconditions: Map contents are written to standard output.
template <typename K, typename V>
void Map<K,V>::Display() const{
  Node<K,V> *curr = m_head; // The first node
  //If the map is empty, then a out_of_range error gets thrown
  if(m_size == 0){
    cout << "There is nothing to display" << endl;
    return;
  }
  //Traverses through the linked list
  //Prints out the each of map's keys and it's values
  while(curr != nullptr){
    cout << curr -> GetKey() << ":" << curr -> GetValue() << endl;
    curr = curr -> GetNext();
  }
}