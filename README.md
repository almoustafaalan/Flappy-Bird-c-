# Flappy-Bird-c-
First c++ game. Using sfml.

# Flappy Bird Clone (C++ & SFML)

A simple Flappy Bird clone built with C++ and [SFML](https://www.sfml-dev.org/).  
This project is for learning purposes and demonstrates basic game loops, physics, collision detection, and graphics.

---

##  Controls
- SPACE → Jump
- R → Restart after game over
- ESC → Quit


##  Features
- Flappy Bird mechanics (jump with SPACE)
- Randomly generated pipes
- Score counter
- Game Over + Restart option
- Built using C++ and SFML

---

## Requirements
- C++ compiler (GCC, Clang, MSVC)
- [SFML 2.5+](https://www.sfml-dev.org/download.php)
- A font file (I used 'arial.ttf', put it in the project folder)

---

## How to Run
1. Install SFML:
   - Download from [SFML official site](https://www.sfml-dev.org/download.php)
   - Extract it somewhere on your computer
   - Note the path to 'include' and 'lib' folders

2. how to compile.
g++ FlappyBird.cpp -o FlappyBird -I <path-to-sfml-include> -L <path-to-sfml-lib> -lsfml-graphics -lsfml-window -lsfml-system


