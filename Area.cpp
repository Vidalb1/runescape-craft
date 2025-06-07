/*****************************************
** File: Area.cpp
** Project: Runescape Crafting
** Author: Vidal Bickersteth
** Date: 5/3/25
**
** This program is the Area.cpp file of Runescape Crafting Project
** This file consists of the name, description, and ID of each area
** This file creates an Area object.
** This file is neccessary for the Hero to move and change directions
** All possible exits for the Hero to make are displayed
** -1 means no path
**
***********************************************/

#include <iostream>
#include <string>
#include <vector>
#include "Area.h"
using namespace std;

//Name: Area (Overloaded Constructor)
//Precondition: Must have valid input for each part of a area
// First int is the unique identifier for this particular area.
// The first string is the name of the area
// The second string is the description of the area
// The last four ints are the unique identifier for adjacent areas
//     (-1 = no path)
// North, East, South, and West
//Postcondition: Creates a new area
Area::Area(int first_int, string first_string, string second_string
    , int second_int, int third_int, int fourth_int, int fifth_int){
    m_ID = first_int; //The ID for the area
    m_name = first_string; // The name of the area
    m_desc = second_string; // The description of the area
    m_direction[0] = second_int; //The ID for North
    m_direction[1] = third_int; //The ID for East
    m_direction[2] = fourth_int; //The ID for South
    m_direction[3] = fifth_int; //The ID for West
}

//Name: GetName
//Precondition: Must have valid area
//Postcondition: Returns area name as string
string Area::GetName(){
    //Returns area name
    return m_name;
}

//Name: GetID
//Precondition: Must have valid area
//Postcondition: Returns area id as int
int Area::GetID(){
    //Returns area's ID
    return m_ID;
}

//Name: GetDesc
//Precondition: Must have valid area
//Postcondition: Returns area desc as string
string Area::GetDesc(){
    //Retuns Area's description
    return m_desc;
}

//Name: CheckDirection
//Precondition: Must have valid area
//You pass it a char (N/n, E/e, S/s, or W/w) and if that is a valid exit it
//returns the ID of the area in that direction
//Postcondition: Returns id of area in that direction if the exit exists
//If there is no exit in that direction, returns -1
int Area::CheckDirection(char myDirection){
    //If there's a direction in the following areas
    // N E S W, then the ID of that area get's returned
    // Otherwise, there is no direction of that area
    switch(myDirection){
        case 'N':
            if(m_direction[0] != -1){
                return m_direction[N];
            }
            break;
        case 'n':
            if(m_direction[0] != -1){
                return m_direction[n];
            }
            break;
        case 'E':
            if(m_direction[1] != -1){
                return m_direction[E];
            }
            break;
        case 'e':
            if(m_direction[1] != -1){
                return m_direction[e];
            }
            break;
        case 'S':
            if(m_direction[2] != -1){
                return m_direction[S];
            }
            break;
        case 's':
        if(m_direction[2] != -1){
                return m_direction[s];
            }
            break;
        case 'W':
            if(m_direction[3] != -1){
                return m_direction[W];
            }
            break;
        case 'w':
            if(m_direction[3] != -1){
                return m_direction[w];
            }
            break;
    }
    return -1;
}

//Name: PrintArea
//Precondition: Area must be complete
//Postcondition: Outputs the area name, area desc, then possible exits
void Area::PrintArea(){
    cout << m_name << endl; //Prints the area name
    cout << m_desc << endl; //Prints the area description
    vector<string> lists; //List of possible exits
    int count = 0; //The counter 
    for(int i = 0; i < 4; i++){
        //All valid exits are added to a list of possible exits
        if(m_direction[i] != -1){
            count++;
            if(i == 0){
                lists.push_back("N");
            }else if(i == 1){
                lists.push_back("E");
            }else if(i == 2){
                lists.push_back("S");
            }else if(i == 3){
                lists.push_back("W");
            }
        }
    }
    //If there no exits in the four directions, then there are
    //no possible exits 
    if(count == 0){
        cout << "There are no possible exits" << endl;
    }else{
        //The possible exits gets displayed
        cout << "Possible Exits: ";
        for(unsigned int j = 0; j < lists.size(); j++){
            cout << lists.at(j) << " ";
        }
        cout << endl;
    }
}