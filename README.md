#Runescape Crafting Game
Overview

This project is a text-based simulation of the Runescape Crafting Game. It allows a Hero character to explore, gather resources, craft items, and manage inventory. The game demonstrates object-oriented programming concepts, command handling, and game logic.

Problem it solves: Provides a simple, interactive way to practice programming fundamentals (classes, I/O, game loops).

Who it helps: Students learning C++ and object-oriented design, or anyone interested in text-based game mechanics.

Tech Stack

Language: C++ (tested with g++)

Environment: Linux platform

Tools: Standard Template Library (STL), GNU Make, Valgrind (optional memory debugging)

Key Features

Hero actions: Look, move, gather, craft, display inventory

Resource system: Collect and combine raw materials into crafted items

Inventory management: Track resources and crafted goods dynamically

Command interface: Interactive gameplay via text commands

How to Run
Requirements

Linux environment with g++ and make installed

Steps
# Clone the repository
git clone https://github.com/Vidalb1/runescape-craft.git
cd runescape-craft

# Build using the provided Makefile
make

# Run the game with sample map and crafting data
make run1

# (Optional) Run with Valgrind for memory checks
make val1

# Clean build files
make clean


proj_map1.txt → Defines the game world map

proj_craft.txt → Defines crafting recipes

You can modify these text files to create new maps and recipes.

Results

Functional crafting system inspired by Runescape

Modular codebase built with object-oriented design principles

Successfully compiles and runs on Linux platforms
(Screenshots or terminal GIFs of gameplay would go here for extra polish)

Next Steps

Add more crafting recipes and complex item trees

Implement combat, NPCs, or trading mechanics

Expand world with multiple maps

Add save/load functionality for persistent progress

Commit Style

Commits: Small, descriptive messages (e.g., “Implement Area class with connections”)

Branches: Use feature branches for new components (e.g., feature/crafting)

Issues: Track bugs and TODOs with GitHub Issue
