/*****************************************
** File: Game.cpp
** Project: Runescape Crafting
** Author: Vidal Bickersteth
** Date: 5/3/25
**
** This program is the Game.cpp file of Runescape Crafting Project.
** This file implement the Runescrape Crafting Game
** This file creates a Hero object, an Area vector object, an Item vector object
** This file is uses all other files to create the game's function
** This program allows the Hero to Look, Move, UseArea, CraftItem, Display 
** their inventory, or quit the game.
** The Hero's map and items also gets loaded into the game
**
***********************************************/

//Includes of required classes
#include "Area.h"
#include "Hero.h"
#include "Item.h"
#include "Game.h"

//Includes of required libraries
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Name: Game(string filename) - Overloaded Constructor
// Description: Creates a new Game
// Preconditions: None
// Postconditions: Initializes all game variables to defaults (constants)
// including m_myHero (null), mapFile (passed value), craftFile (passed)
// and starting area (START_AREA)
Game::Game(string first, string second){
    m_areaFile = first; //Sets the map txt file
    m_craftFile = second; //Sets the item craft txt file
    m_curArea = START_AREA; //Sets the first area of map
    m_myHero = nullptr; //Sets to nullptr 
}

// Name: ~Game
// Description: Destructor
// Preconditions: None
// Postconditions: Deallocates anything dynamically allocated
//                 in Game
Game::~Game(){
    //The area vector and all of it's elements gets deleted 
    for(unsigned int i = 0; i < m_areas.size(); i++){
        delete m_areas.at(i);
        m_areas.at(i) = nullptr;
    }
    //The items vector and all of it's elements gets deleted
    for(unsigned int j = 0; j < m_items.size(); j++){
        delete m_items.at(j);
        m_items.at(j) = nullptr;
    }
    //Hero gets deleted and set to it's default value
    delete m_myHero;
    m_myHero = nullptr;
    //The .txt variables and m_curArea gets set to its default value
    m_curArea = 0;
    m_craftFile = "";
    m_areaFile = "";
}

// Name: LoadMap()
// Description: Reads area data from the map file and dynamically
//             creates Area objects. Inserts each new Area into
//             m_myMap in the order encountered.
// Preconditions: m_mapFile is set to a valid filename;
//             the file exists and is formatted correctly.
// Postconditions: m_myMap contains all loaded Area pointers;
//             file stream is closed.
void Game::LoadMap(){
    ifstream inputStream; // The input stream variable that will load the 
                          // text file into the document
    string id; // The ID
    string area; // The Area
    string desc; // The Description
    string north; // The North
    string east; // The East
    string west; // The West
    string south; // The South
    inputStream.open(m_areaFile); 
    if(inputStream.is_open()){
        // If the file is open, then 
        // the text file and all of the various areas and their data
        // gets loaded into a pointer vector m_areas
        while(getline(inputStream, id, DELIMITER) && getline(inputStream, area, DELIMITER) && getline(inputStream, desc, DELIMITER)
        && getline(inputStream, north, DELIMITER) && getline(inputStream, east, DELIMITER) && getline(inputStream, south, DELIMITER)
        && getline(inputStream, west, DELIMITER)){
            m_areas.push_back(new Area(stoi(id), string(area), string(desc),
            stoi(north), stoi(east), stoi(south), stoi(west)));
        }
    // The file gets closed after the load
    inputStream.close();
    }else{
        //Otherwise the text file does not exist
        cout << "File does not exist." << endl;
        return;
    }
}

// Name: LoadCraft()
// Description: Reads crafting definitions from the craft file and
//              creates Item objects. Parses each line into an
//              item name and its requirement list.
// Preconditions: m_craftFile is set to a valid filename;
//              the file exists and uses DELIMITER.
// Postconditions: m_items contains new Item pointers for
//              every recipe; file stream is closed.
void Game::LoadCraft(){
    ifstream inputStream; // The input stream variable that will load the 
                          // text file into the items inventory
    string first; //The First(result)
    string second; // The Second(first requirment)
    string third; // The Third(second requirment)
    string fourth; // The Fourth(third requirment)
    string fifth; // The Fifth(fourth requirement)
    string sixth; // The Sixth
    vector<string> require; // Vector of required materials 
    inputStream.open(m_craftFile);
    if(inputStream.is_open()){
        // If the file is open, then 
        // the text file and all of various items and it's requirements
        // gets loaded into creating a pointer vector of all known items
        // No spaces are allowed
        while(getline(inputStream, first, DELIMITER) && getline(inputStream, second, DELIMITER) && getline(inputStream, third, DELIMITER)
        && getline(inputStream, fourth, DELIMITER) && getline(inputStream, fifth, DELIMITER) && getline(inputStream, sixth)){
            // All valid requirement elements gets added to the require vector 
                if(second != "None"){
                    require.push_back(second);
                }
                if(third != "None"){
                    require.push_back(third);
                }
                if(fourth != "None"){
                    require.push_back(fourth);
                }
                if(fifth != "None"){
                    require.push_back(fifth);
                }
                m_items.push_back(new Item(first, require));
                //Clears the current vector to blank to ensure proper requirements 
                //each result item
                require.clear();
            }   
        // The file gets closed after the load
    inputStream.close(); 
    }else{
         // Print this if the file does not get opened
         cout << "File does not exist." << endl;
         return;
    }
}

// Name: HeroCreation()
// Description: Prompts the player to enter a hero name and
//              constructs a new Hero.
// Preconditions: Standard input (cin) is available.
// Postconditions: m_myHero points to a newly allocated Hero
//              with the entered name.
void Game::HeroCreation(){
    string hero_name = ""; // The Hero name
    cout << "Hero Name: " << endl;
    cin >> hero_name;
    while(true){
        // If the input is invaild, the user is prompt to try again.
        if(cin.fail()){
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid input. Try again" << endl;
            cout << "Hero Name: " << endl;
            cin >> hero_name;
        }else{
            break;
        }
    }
    //Creates a new Hero object with the hero_name
    m_myHero = new Hero(hero_name);
}

// Name: Look()
// Description: Displays the current Area’s name, description,
//              and possible exits.
// Preconditions: m_curArea is a valid index into m_myMap.
// Postconditions: Current area details are printed to stdout.
void Game::Look(){
    //Prints the current area and all of it's data
    cout << endl;
    m_areas.at(m_curArea) -> PrintArea();
}

// Name: StartGame()
// Description: Initializes game flow by loading map and crafting
//              data, creating the hero, then showing the
//              starting area and entering the main loop.
// Preconditions: m_mapFile and m_craftFile are set; files exist.
// Postconditions: Game state is initialized and Action() is called.
void Game::StartGame(){
    //Loads the map and items
    //Then creates hero name and starts the game
    LoadMap();
    LoadCraft();
    cout << "Welcome to Runescape Craft!" << endl;
    HeroCreation();
    cout << endl;
    Action();
}

// Name: Action()
// Description: Presents the player with the main menu
//              (Look, Move, Use Area, Craft, Inventory, Quit)
//              and drives game interactions until the player quits.
// Preconditions: Hero and map are initialized.
// Postconditions: Continues looping until user selects Quit.
void Game::Action(){
    int option = 0; // The option from 1-6 that the user chooses

    // The main menu of Runescape Crafting
    // The user can choose to participate or quit
    m_areas.at(m_curArea) -> PrintArea();
    while(option != 6){
        // The game will contiune to play until
        // the user wants to exit, which is 6.
        cout << "What would you like to do?" << endl;
        cout << "1. Look" << endl;
        cout << "2. Move" << endl;
        cout << "3. Use Area" << endl;
        cout << "4. Craft Item" << endl;
        cout << "5. Display Inventory" << endl;
        cout << "6. Quit" << endl;
        cin >> option; 
        while(true){
            // If the input is invaild, the user is prompt to try again.
            if(cin.fail() || option < 1 || option > 6){
                cin.clear();
                cin.ignore(256, '\n');
                cout << "What would you like to do?" << endl;
                cout << "1. Look" << endl;
                cout << "2. Move" << endl;
                cout << "3. Use Area" << endl;
                cout << "4. Craft Item" << endl;
                cout << "5. Display Inventory" << endl;
                cout << "6. Quit" << endl;
                cin >> option; 
            }else{
                break;
            }
        }
        //
        switch(option){
            case 1:
                if(cin.peek() == '\n'){
                    cin.ignore();
                }
                //Sees the current area
                Look();
                break;
            case 2:
                if(cin.peek() == '\n'){
                    cin.ignore();
                }
                //Moves to new Area
                Move();
                m_areas.at(m_curArea) -> PrintArea();
                break;
            case 3:
                if(cin.peek() == '\n'){
                    cin.ignore();
                }
                //Use the area to gather materials
                UseArea();
                break;
            case 4:
                if(cin.peek() == '\n'){
                    cin.ignore();
                }
                //Crafts a new item
                CraftItem();
                break;
            case 5:
                //Displays Hero's inventory if any items are present
                cout << "******* INVENTORY *******" << endl;
                m_myHero -> DisplayInventory();
                break;
            case 6:
                //Final message
                cout << "Good bye!" << endl;
                break;
        }
    }
}

// Name: Move()
// Description: Prompts the player for a direction (N/E/S/W),
//              validates the move, updates m_curArea, and
//              calls Look() to show the new area.
// Preconditions: m_curArea is valid; m_myMap contains
//              adjacent Area pointers.
// Postconditions: m_curArea is updated to the new area index.
void Game::Move(){
    char direct; // The Direction that the user chooses
    int num = 0; // The new Current Area
    cout << "Which direction? (N E S W)" << endl;
    cin >> direct;
    num = m_areas.at(m_curArea) -> CheckDirection(direct);
    while(true){
        // If the input is invaild like -1, the user is prompt to try again.
        if(cin.fail() || num == -1){
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Which direction? (N E S W)" << endl;
            cin >> direct;
            num = m_areas.at(m_curArea) -> CheckDirection(direct);
        }else{
            break;
        }
    }
    //Current area is set to the new area
    m_curArea = num;
}

// Name: CraftItem()
// Description: Displays all craftable items, prompts for a selection,
//              and attempts crafting via Hero’s CanCraft/Craft methods.
// Preconditions: m_items is populated with Item pointers.
// Postconditions: If crafting succeeds, inventory is
//              updated; otherwise prints error.
void Game::CraftItem(){
    int item = 0; //The Item that the user wants to craft
    cout << "Which item would you like to craft?" << endl;
    //Displays all possible items that can be crafted
    for(int i = 0; i < int(m_items.size()); i++){
        cout << i+1 << ". " << m_items.at(i)->GetName() << endl;
    }
    cin >> item;
    while(true){
        // If the input is invaild, the user is prompt to try again.
        if(cin.fail() || item < 1 || item > int(m_items.size())){
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Which item would you like to craft?" << endl;
        for(unsigned int i = 0; i < m_items.size(); i++){
            cout << i << ". " << m_items.at(i) << endl;
        }
        cin >> item; 
        }else{
            break;
        }
    }
    //The item that the user wants to craft gets crafted if possible
    m_myHero -> Craft(m_items.at(item-1)->GetName(), m_items.at(item-1)->GetReq());
}

// Name: UseArea()
// Description: Prompts the player to choose a search action
//              (Raw, Natural, Food, Hunt)
//              and forwards that request to the Hero.
// Preconditions: Hero exists and has methods Raw/Natural/Food/Hunt.
// Postconditions: One gather action is performed and the result printed.
void Game::UseArea(){
    int choice = 0; // The choice that the hero wants to look for
    cout << "What would you like to look for?" << endl;
    cout << "1. Raw Materials (Mining)" << endl;
    cout << "2. Natural Resources (Woodcutting/Foraging)" << endl;
    cout << "3. Food (Fishing/Farming)" << endl;
    cout << "4. Hunt" << endl;
    cin >> choice;
    while(true){
        // If the input is invaild, the user is prompt to try again.
        if(cin.fail() || choice < 1 || choice > 4){
        cin.clear();
        cin.ignore(256, '\n');
        cout << "What would you like to look for?" << endl;
        cout << "1. Raw Materials (Mining)" << endl;
        cout << "2. Natural Resources (Woodcutting/Foraging)" << endl;
        cout << "3. Food (Fishing/Farming)" << endl;
        cout << "4. Hunt" << endl;
        cin >> choice;
        }else{
            break;
        }
    }
    //The user gathers various materials depending on their choice
    switch(choice){
        case 1:
            //Gathers raw material if found
            m_myHero -> Raw();
            break;
        case 2:
            //Gathers natural material if found
            m_myHero -> Natural();
            break;
        case 3:
            //Gathers food material if found
            m_myHero -> Food();
            break;
        case 4:
            //Gathers hunt material if found 
            m_myHero -> Hunt();
            break;
    }
}