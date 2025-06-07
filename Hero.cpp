/*****************************************
** File: Hero.cpp
** Project: Runescape Crafting
** Author: Vidal Bickersteth
** Date: 5/3/25
**
** This program is the Hero.cpp file of Runescape Crafting Project.
** This is the creation of our hero character
** This file creates a Hero object.
** This file is neccessary to create our hero and allow it
** to use their item inventory, to move, look, or display their inventory.
** The Hero can gather products from Raw, Natural, Food, or Hunt
** From the combination of these products, The Hero will be able to craft new items 
** if they have the requirements to do so.
**
**
***********************************************/

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "Hero.h"
using namespace std;

// Name: Hero(const string& name)
// Description: Constructs a new Hero with the specified name.
// Preconditions: name must be a valid, non‐empty string.
// Postconditions: m_name is initialized; inventory map is empty.
Hero::Hero(const string& name){
    //Stores Hero's name
    m_name = name;
}

// Name: ~Hero()
// Description: Destructor for Hero.
// Preconditions: None.
// Postconditions: Releases any dynamically allocated items in Hero.
//                 None in this case.
Hero::~Hero(){
    //Empty
}

// Name: GetName()
// Description: Retrieves the hero’s name.
// Preconditions: None.
// Postconditions: Returns the value of m_name.
string Hero::GetName() const{
    //Returns Hero name
    return m_name;
}

// Name: SetName(const string& name)
// Description: Updates the hero’s name.
// Preconditions: name must be a valid string.
// Postconditions: m_name is set to the new value.
void Hero::SetName(const string& name){
    //Stores new Hero name
    m_name = name;
}

// Name: DisplayInventory()
// Description: Prints the hero’s current inventory using overloaded << operator
// Preconditions: Inventory map has been initialized.
// Postconditions: Inventory contents are displayed.
void Hero::DisplayInventory() const{
    //Displays Hero's inventory
    m_inventory.Display();
}

// Name: CollectItem(const string& item)
// Description: If the item exists, in m_inventory, uses Update to increment quantity
//              If the item does not exist in m_inventory, inserts it.
// Preconditions: item must be a valid item name.
// Postconditions: Inventory count for item is incremented by 1.
void Hero::CollectItem(const string& item){
    //If the item exists in Hero's inventory, then it's count will be incremented by 1
    try{
        m_inventory.Update(item, m_inventory.ValueAt(item) + 1);
        cout << "Crafted: " << item << "!" << endl;
        return;
    //If the item does not exist in Hero's inventory, that item gets added to the inventory
    }catch(const out_of_range& error){
        m_inventory.Insert(item, 1);
        cout << "Crafted: " << item << "!" << endl;
    }
}

// Name: CanCraft(const vector<string>& requirements)
// Description: Iterators through the requirements to see if they have quantity in m_inventory
// Preconditions: Requirements vector populated with item names.
// Postconditions: Returns true if every required item has count ≥1.
bool Hero::CanCraft(const vector<string>& requirements) const{
    //If the requirements to make a new item is present,
    //then the Hero can craft the new item.
    try{
        int counter = 0; // The counter
        for(unsigned int i = 0; i < requirements.size(); i++){
            if(m_inventory.ValueAt(requirements.at(i)) >= 1){
                counter++;
            }
        }
        //If there is a count in every requirement element,
        //then the hero can craft an item
        if(counter == int(requirements.size())){
            return true;
        }else{
            throw out_of_range("Item does not have quantity");
        }
    //Otherwise, the Hero can not craft that particular item
    }catch(const out_of_range& error){
        return false;
    }
    return false;
}

// Name: Craft(const string& result, const vector<string>& requirements)
// Description: Consumes the listed requirements and adds the
//              crafted "result" (iterates through requirements and Updates)
// Preconditions: Call to CanCraft(requirements) must return true.
// Postconditions: Each requirement’s count is decremented by 1;
//                 Result of crafting is added.
void Hero::Craft(const string& result, const vector<string>& requirements){
    //If the hero can craft the item, then the item gets added to their inventory.
    if(CanCraft(requirements)){
        CollectItem(result);
        //Each required element count gets decreased by 1.
        for(unsigned int i = 0; i < requirements.size(); i++){
            m_inventory.Update(requirements.at(i), m_inventory.ValueAt(requirements.at(i)) - 1);
        }
    //Otherwise, the hero can not craft the item.
    }else{
        cout << "Cannot create " << result << ". Missing requirements." << endl;
    }
}

// Name: Raw()
// Description: Simulates mining for raw materials. Passes values
//              and calls Gather function.
// Preconditions: Random number generator seeded.
// Postconditions: Possibly adds a random raw material
//                 to inventory or reports none found.
void Hero::Raw(){
    //Gathers a random raw material if found
    Gather(RawProducts, "You mined and found nothing", "You mined and found some ");
}

// Name: Natural()
// Description: Simulates foraging for natural resources. Passes values
//              and calls Gather function.
// Preconditions: Random number generator seeded.
// Postconditions: Possibly adds a random natural resource
//                 or reports none found.
void Hero::Natural(){
    // Gathers a random natural material if found
    Gather(NaturalProducts, "You searched and found nothing", "You searched and harvested some ");
}

// Name: Food()
// Description: Simulates gathering food items. Passes values
//              and calls Gather function.
// Preconditions: Random number generator seeded.
// Postconditions: Possibly adds a random food item or reports none found.
void Hero::Food(){
    // Gathers a random food material if found
    Gather(FoodProducts, "You searched and found nothing", "You searched and harvested some ");
}

// Name: Hunt()
// Description: Simulates hunting for creature drops. Passes values
//              and calls Gather function.
// Preconditions: Random number generator seeded.
// Postconditions: Possibly adds a random creature drop
//                 or reports none found.
void Hero::Hunt(){
    // Gathers a random hunt product if found
    Gather(HuntProducts, "You hunted and found nothing", "You went hunting and got some ");
}

// Name: Gather
// Description: Randomly selects an item from vector products passed.
//              If selection equals list size, prints 'noItemMsg';
//              otherwise prints foundMsg + item and adds it
//              to the hero's inventory.
// Preconditions: 'products' must contain valid item names.
// Postconditions: Inventory is incremented for the selected
//               item if found; message printed.
void Hero::Gather(const vector<string>& products, const string& noItemMsg,
    const string& foundMsg){
    int random_item = rand() % (products.size()+1); // A randomizer from 0-4
    //If the random number is equal to the product's size,
    //then no item is found
    if(random_item == int(products.size())){
        cout << noItemMsg << endl;
    }else{
        //Otherwise, the item is found
        //then gets added to the Hero's inventory or increases it's count
        cout << foundMsg << products.at(random_item) << "!" << endl;
        try{
            m_inventory.Update(products.at(random_item), m_inventory.ValueAt(products.at(random_item))+1);
        }catch(const out_of_range&){
            m_inventory.Insert(products.at(random_item), 1);
        }
    }
}