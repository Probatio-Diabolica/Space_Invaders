# Space Invaders in C++ with Raylib

A modern take on the classic **Space Invaders** arcade game, built using **C++** and **Raylib**. The player controls a spaceship to shoot waves of alien invaders, with increasing difficulty over time.

## Table of Contents

- [Features](#features)
- [Technologies](#technologies)
- [Setup](#setup)
- [How to Play](#how-to-play)
- [Gameplay](#gameplay)
- [Project Structure](#project-structure)
- [Future Improvements](#future-improvements)
- [License](#license)

## Features

- Player-controlled spaceship with keyboard inputs for movement and shooting.
- Waves of alien invaders that increase in speed and difficulty.
- Collision detection for bullets and invaders, and between enemy bullets and the player.
- Scoring system to track player progress.
- Game over conditions when invaders reach the player's position or the player is hit.

## Technologies

- **C++**: Core language for the game logic and structure.
- **Raylib**: Graphics library used for rendering, input handling, and audio effects.

## Setup

To run this project using **Visual Studio**:

1. Clone the repository:

    ```bash
    git clone https://github.com/your-username/space-invaders-cpp.git
    ```

2. Open the project in **Visual Studio**:
   - Open Visual Studio and create a new empty project.
   - Add the existing source files (`.cpp` files) to your project.
   - Set up Raylib by configuring the **Include** directories and **Library** directories in the project properties.

3. Build and run the project:
   - Build the solution (Ctrl + Shift + B).
   - Run the game (F5) to play.


## How to Play

- **Move**: Use the `left` and `right` arrow keys to move your spaceship.
- **Shoot**: Press the `spacebar` to fire bullets at alien invaders.
- **Objective**: Destroy all alien invaders before they reach the bottom of the screen. Avoid being hit by enemy bullets!

## Gameplay

![Game Screenshot](screenshot.png)

The game starts with a grid of alien invaders moving horizontally across the screen. Every time they hit the screen's edge, they descend closer to the player. The player must destroy all the invaders by shooting them while avoiding being hit by their projectiles. The game gets progressively harder as invaders increase in speed.

## Project Structure

```bash
├── src
│   ├── main.cpp          # Entry point of the game
│   ├── player.cpp        # Player class implementation
│   ├── invader.cpp       # Invader class implementation
│   ├── bullet.cpp        # Bullet class implementation
│   └── game_controller.cpp  # Game controller logic
├── assets                # Sprites, sounds, and other game assets
└── README.md             # Project documentation
