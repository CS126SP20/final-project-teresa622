# Project Proposal
# Tetris

Author: Teresa Dong

---

**Project Idea**

I want to make a basic Tetris game. It will include graphics of tetromino blocks and all the game mechanics needed for a
 fully functioning simple Tetris game.
> **Simple Tetris game explanation**: Essentially, tetromino blocks would fall from the top of the screen, and the 
>player would use different key commands(arrow keys and space bar) to rotate and translate the tetromino before it falls on other stacked 
>tetronimoes or the bottom of the screen. The goal is to stack the tetrominoes and create as many lines as possible, 
>which would be cleared once they're made. This increases the player's score. The objective is to get the highest score
>possible. If the tetrominoes are stacked to above the top of the screen, the game is over.

**Background Knowledge and Motivation for making Tetris**

I understand how a Tetris game works. I also have the coding experience with CLion from CS 126. I think I will mostly be struggling with figuring out how to work with graphics, since I don't have much experience with it.
I want to make Tetris because I enjoy playing the game, and I think it would be cool to play a version of Tetris that I made myself.

**Needed External Libraries**

I am planning on using:
 * [SQLite](https://www.sqlite.org/index.html) database to store player scores.
  
**Rough Timeline**

Week Number | Things to work on
------------ | -------------
Week 1 | 1. I will work on basic graphics, such as generating a screen and having tetromino pieces falling. <br> 2. I will integrate SQLite, the external library that I am using, into my program (with Cinder) to show that it works with my program. <br> 3. I will figure out how to get the tetromino pieces to stack on top of one another. <br> 4. I will implement key controls(arrows and space bar) that will allow the player to rotate and translate the tetromino. <br> 5. I will test some basic functionalities of tetromino initialization and movement. <br> 6. I will add the score keeping feature that scores all the scores and create the leaderboards when the game ends that shows the top scores.
Week 2| 1. I will implement logic that allows the tetromino pieces to stack on top of one another. <br> 2. I will implement logic that ends the game if the tetrominoes are stacked above the top of the screen. <br> 3. I will implement logic that will clear lines that are fully filled by tetrominoes. <br> 4. I will implement music and sound effects into the game. <br> 5. I will add different color themes for the tetrominoes (a color theme will be randomly generated every new game). <br> 6. I will implement the shadow/projection of the tetrominoes onto the surface for easier gameplay. <br> 7. I will add 'levels' to the game, making it quicker every time a level is passed. <br> 8. I will add more event keys such as pause and restart. <br> 9. I will finish testing tetromino and the game engine.
Week 3| 1. I will create the README.md <br> 2. I will add a feature that shows the player's current score as they are playing. <br> 3. I will add any final clarifying comments and get rid of any redundant code in my program. <br> 4. I will fix any bugs.

**Stretch Goals**

If I finish the project with additional time, here are some ideas I have of additional things I can implement:
  * A beginning screen with something like: "Press enter to play" and "Press 'h' for key controls and instructions"
  * Add music to the game and maybe some sound that will play once a line is cleared
  * Add "levels" to the game - making the game faster with more lines that are cleared.
  * Add different color themes to the tetrominoes.
  * Add other key commands like 'r' to reset and 'p' to pause the game.
