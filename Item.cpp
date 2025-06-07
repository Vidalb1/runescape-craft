/*****************************************
** File: Item.cpp
** Project: Runescape Crafting
** Author: Vidal Bickersteth
** Date: 5/3/25
**
** This program is the Item.cpp file of Runescape Crafting.
** This is the Hero's inventory.
** This file creates an Item object.
** This files stores the item's name and the requirements
** needed to create a new item.
** This class is needed to create the Hero's item
**
**
***********************************************/

#include <string>
#include <vector>
#include "Item.h"
using namespace std;

// Name: Item(const string& name, const vector<string>& requirements)
// Description: Constructs a new Item with the given name and
//              a list of crafting requirements.
// Preconditions: ‘name’ must be a valid, non-empty string;
//                ‘requirements’ must contain valid item names.
// Postconditions: m_name is initialized to name;
//                 m_req is initialized to a copy of requirements.
Item::Item(const string& name, const vector<string>& requirements){
    //Stores the name and the requirements of that item
    m_name = name;
    m_req = requirements;
}

// Name: GetName()
// Description: Retrieves the name of this item.
// Preconditions: None.
// Postconditions: Returns the value of m_name.
string Item::GetName() const{
    //Returns the name of item
    return m_name;
}

// Name: GetReq()
// Description: Retrieves the list of crafting requirements for this item.
// Preconditions: None.
// Postconditions: Returns a const reference to m_req
//                 (the requirements vector).
const vector<string>& Item::GetReq() const{
    //Returns the list of recipes required to create a new item
    return m_req;
}