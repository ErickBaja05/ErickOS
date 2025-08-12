# ErickOS

**Welcome to ErickOS!**  
ErickOS is a modular console-based operating system simulation project where I practice and showcase fundamental data structures and algorithms using C++  
Each mini-project within ErickOS demonstrates practical applications of data structures like linked lists, stacks, queues and more, combined with file handling and modular programming concepts.  

---

## Table of Contents

- [About the Project](#about-the-project)  
- [Mini Projects](#mini-projects)  
  - [To-Do List](#to-do-list)  
- [Steps to build and run](#steps-to-build-and-run)
  -[To-Do List](#to-do-list)    
- [How to Use](#how-to-use)  
- [Future Plans](#future-plans)  
- [Contact](#contact)  

---

## About the Project

ErickOS aims to create a lightweight, text-based operating system simulation where users can access various utilities like a To-Do List manager, Music Player, and more. The focus is on clean code architecture, modular design, and solid understanding of data structures in real-world applications.  
This project is a personal learning journey and part of my software engineering portfolio, showcasing proficiency in C++ and Java.

---

## Mini Projects

### To-Do List

The To-Do List is the first mini-project implemented in ErickOS. It allows users to manage daily tasks using a singly linked list data structure. Features include:

- Add tasks with descriptions and creation timestamps.  
- Delete tasks by their unique IDs.  
- Search tasks by keyword (case-insensitive).  
- Save and load tasks from a text file to persist data between sessions.  
- Tasks are automatically assigned unique incremental IDs.  
- Only pending tasks are saved, completed tasks are excluded from the file.  

This mini-project demonstrates practical usage of pointers, dynamic memory management, string manipulation, file I/O, and modular programming techniques in C++.

---

## Getting Started

This project uses CMake as its build system. To compile and run ErickOS, make sure you have CMake and a C++ compiler (like g++) installed.

### Steps to build and run:

```bash
# Clone the repository
git clone https://github.com/ErickBaja05/ErickOS
cd ErickOS

# Create a build directory and enter it
mkdir build
cd build

# Generate build files with CMake
cmake ..

# Build the project
cmake --build .

# Run the executable
./ErickOS
```
### Notes
-  The project source files are organized modularly inside the src/ folder.
- Header files are in the include/ folder.
- Data files are stored inside the data/ folder.
- Make sure to run commands from the build/ directory after initial setup.


---

## How to Use

When running ErickOS, the main menu presents available mini-projects. Selecting the To-Do List opens its menu where you can add, delete, search, view, save, and load tasks. 
All input/output is managed through the console for simplicity and focus on core concepts.

---


## Future Plans
- Implement additional mini-projects: Music Player, Bank Simulator, Card Game, etc.  
- Extend data structures to trees and AVL trees.
- Add graphical interface using JavaFX for Java version.

---


## Contact
- Personal mail: [erickalexis2566@gmail.com](mailto:erickalexis2566@gmail.com)  
- Corporate mail: [erick.bajana@epn.edu.ec](mailto:erick.bajana@epn.edu.ec)  
- GitHub: [https://github.com/ErickBaja05](https://github.com/ErickBaja05)  
- LinkedIn: [https://linkedin.com/in/erick-baja05](https://linkedin.com/in/erick-baja05)  


---
