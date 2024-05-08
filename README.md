# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Game Intructions ##

1. Firtsly, the game gives up some options to choose, these are described as bellow:

    - Press "S" or "s" : Start a new game.

    - Press "H" or "h" : Show top of 10 best scores.

    - Press "Q" or "q" : Quit the game.

2. When your choice is start the new game, you have to fill out your name and your age. And then, your information will be stored in the snake.txt file.

      **Note**:

      - The name accesses all keywords on your keyboard, but your age is only acccepted with the number characters and this value is between 10 and 99.

3. When your turn ends, the game menu will be shown again, and you could to the guide above to start the next turn.

## Game New Features ##

1. After 10 senconds, a poisonour apple (obstacle) displays on your screen with red color. If your snake eats that apple, your turn is ended.

2. Your can check the player histories in the snake.txt file. Your could see who is the best player.

## Rubic items matched ##

### Object Oriented Programming - Use OOP techniques ###

To meet this requirement, I created three new classes, including `Player`, `GameData` and `GameManager` (inside data.h and gamemanager.h). Player class holds the player information, such as name, age and score. `GameData` class holds the vector of players and orginizes methods to store player information to the text file. `GameManager` to control the game and interact with users.

### Object Oriented Programming - Use appropiate access specifiers ###

To fulfill this requirement, I used private class member, mostly. For instance, in the Player class, the memeber data are name, age, score, all of them is private (line 9 - 11), or class GameData, vector of players is also private (line 27).

### Object Oriented Programming - Class constructor utilize member initialization list ###

You can see, all the new classes have constructor using member initialization list. Inside data.h file, line 10 - 17 and the gamemanager.h file, line 7.

### Loops, Funtions, I/O - C++ functions and control structures ###

In this project, I used variety of control structures, including if/else, if/else if/ else, while, do/while, switch/case, (inside gamemanager.cpp, line 10 - 97, data.cpp line 40).

### Loops, Funtions, I/O - Interact with file ###

In the `GameData` class, I have some methods to interact with the text file, like `GameData::ReadPlayerData` line 40, `GameData::StorePlayerData` line 25.

### Loops, Funtions, I/O - Accept user input and process input ###

When user enter your age, only number characters are accepted and it is between 10 and 99. With the game menu, you have to press correct keyword to control the game, if not correct, you need to re-enter again. You can see it in the `GameManager::GameManagerInit()` line 10 in the gamemanager.cpp file.

### Memory Management - Use references in function declarations ###

With this requirement, I often use passing by reference in my funtions. You can see some methods in `GameData` class, such as `GameData::StorePlayerData` line 25, `GameData::AddNewPlayer` line 80 or `Player::operator<` line 21 in the data.cpp file.

### Memory Management - Use smart pointer ###

I used `std::unique_ptr` with `GameData` member in the `GameManager` class, to make exclusive ownership with the `GameData`.

### Memory Management - RAII techinuque ###

I usued `gameManger` in the main file as a local variable and combine with smart pointer, the resource will be freed automatically when it out of scope. And I usually use local variable for automatically free the occupied memory.

### Concurrency - Use multithreding ###

I cread another thread using member function to make the obstacle. Every 10 seconds, a new obstacle is created. Use can see line 24 in the game.cpp file.

### Concurrency - Use mutex or lock ###

In the game class, I created a thread and a mutex lock. Mutex is used to synchronize data (vector of obstacle) and avoid data racing (running and snake.alive). Please check the game.cpp for more detailed.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
