# Final Project
#Tetris

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

Read [this document](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html) to understand the project
layout.

**Author**: Teresa Dong - [`teresad2@illinois.edu`](mailto:teresad2@illinois.edu)

###Overview
This application is a basic Tetris game. Tetromino blocks will fall down from the top of the screen, and the player can 
rotate or translate on the screen before it lands on a surface. The surface can be the bottom of the screen or on top 
of other tetrominoes that have already landed. The goal of the game is to make as many full lines as 
possible. These lines will be cleared once they are made, and the player's score will increase. The player wants to get
as high of a score as they can by clearing as many lines as they can.
---
###How to build
This application utilizes Cinder, so please download it [here](https://libcinder.org/download). The latest version is 
recommended.

This application also utilizes SQLite database, but nothing needs to be done here for the program to build. It should 
automatically work.

Lastly, this was compiled using CLion, and has only been tested on MacOS. This application may still run on other 
operating systems, but please use the above for best performance.

___
###Usage
There are 2 different flags for the program (which you can modify via Edit Configurations -> Program Arguments):
    
    * tilesize, default: 50 -- "the size of each tile" in square pixels
    * name, default: Guest -- "the name of the player", for database purposes
    
####Game Controls
* Pause: P
* Restart: R
* Left: Left arrow
* Right: Right arrow
* Down: Down arrow
* Drop: Space bar

####Default Settings
* Font: Arial
___
###Libraries
* Cinder v0.9.2
* SQLiteModernCpp + SQLite3 - for score keeping database
* gflags
* catch2 - for unit testing



