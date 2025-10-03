🎮 Runescape Crafting Game

A text-based crafting game inspired by Runescape, built in C++.

📝 Overview

This project simulates the Runescape Crafting Game. The player controls a Hero who can explore, gather resources, craft items, and manage their inventory.

Problem it solves: Provides a fun, interactive way to practice programming fundamentals (classes, OOP, file I/O, game loops).

Who it helps: Students learning C++ and object-oriented design, or anyone interested in text-based game mechanics.

🛠 Tech Stack

Language: C++ (tested with g++)

Environment: Linux platform

Libraries/Tools: Standard Template Library (STL), GNU Make, Valgrind (optional for memory debugging)

✨ Key Features

Hero actions: look, move, gather, craft, display inventory

Resource system: Collect and combine raw materials into crafted items

Inventory management: Track resources and crafted goods dynamically

Command interface: Interactive text-based gameplay

🚀 How to Run
Requirements

Linux environment with g++ and make installed

Build & Run
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


Files:

proj_map1.txt → Defines the game world map

proj_craft.txt → Defines crafting recipes

You can modify these files to create custom maps and crafting recipes.

📊 Results

Fully functional crafting system inspired by Runescape

Modular codebase using object-oriented design principles

Successfully compiles and runs on Linux platforms

Screenshots or terminal GIFs of gameplay can be added here for visual impact.

🛣 Next Steps

Add more crafting recipes and complex item trees

Implement combat, NPCs, or trading mechanics

Expand the game world with multiple maps

Add save/load functionality for persistent progress

💾 Commit Style

Commits: Small, descriptive messages (e.g., Implement Area class with connections)

Branches: Feature branches for new components (e.g., feature/crafting)

Issues: Track bugs and TODOs using GitHub Issues
