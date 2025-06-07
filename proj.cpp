/*****************************************
** File: proj.cpp
** Project: Runescape Crafting
** Author: Vidal Bickersteth
** Date: 5/3/25
**
** This program is the proj.cpp file of Runescape Crafting Project.
** This program plays the Runscape Crafting Game.
** This allows the Hero to look, move, gather, craft, or display their inventory
** This file is the combination of all other files of this program 
** in order to play this simulation.
**
***********************************************/
#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

int main(int argc, char *argv[]) {
  if( argc != 3) {
    cout << "This requires a map file and a craft file to be loaded." << endl;
    cout << "Usage: ./proj proj_map1.txt proj_craft.txt" << endl;
  }

  cout << "Loading file: " << argv[1] << endl << endl;

  string mapName = argv[1];
  string craftName = argv[2];
  srand (time(NULL));
  Game g(mapName, craftName);
  g.StartGame();
  return 0;
}
