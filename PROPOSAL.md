# Project Proposal
# Tetrominoes

Author: Teresa Dong

---

**Project Idea**

I want to make a basic Tetris game. It will include graphics of tetromino blocks and all the game mechanics needed for a fully functioning simple Tetris game.
> **Simple Tetris game explanation**: Essentailly, tetromino blocks would fall from the top of the screen, and the player would use different key commands to manipulate the tetromino before it falls on other stacked tetronimoes or the bottom of the screen. The goal is to stack the tetrominoes and create as many lines as possible, which would be cleared once they're made. If the tetrominoes are stacked to above the top of the screen, the game is over. 

**Background Knowledge and Motivation for making Tetris**

I understand how a Tetris game works. I also have the coding experience with CLion from CS 126. I think I will mostly be struggling with figuring out how to work with graphics, since I don't have much experience with it.
I want to make Tetris because I enjoy playing the game, and I think it would be cool to play a version of Tetris that I made myself.

**Needed External Libraries**

I am planning on using:
 * [SQLite](https://www.sqlite.org/index.html) database to store player scores.
  
**Rough Timeline**

Week Number | Things to work on
------------ | -------------
Week 1 | 1. I will work on basic graphics, such as generating a screen and having tetromino pieces falling. I am expecting this to be difficult becasue I have little graphics experience. I will also need time to play around with various libraries and figuring out what will work best for my game. <br> 2. I will integrate SQLite, the external library that I am using, into my program (with Cinder) to show that it works with my program. This is because the first checkpoint is graded based on progress of setting up my external library. <br> 3. If I have additional time, I will figure out how to get the tetromino pieces to stack on top of one another.
Week 2| 1. I will implement logic that allows the tetromino pieces to stack on top of one another. <br> 2. I will implement logic that ends the game if the tetrominoes are stacked above the top of the screen. <br> 3. I will implement key controls that will allow the player to rotate and translate the tetromino. <br> 4. I will implement logic that will clear lines that are fully filled by tetrominoes. <br> Note: Depending on my week's workload and how much I am struggling with the graphics, I may have to push #3 and/or #4 to Week 3.
Week 3| 1. I will finish everything from Week 2 if I haven't finished yet. <br> 2. I will implement an ending screen with game leaderboards. This is where I will implement the game scoring.

**Stretch Goals**

If I finish the project with additional time (this seems like a miracle), here are some ideas I have of additional things I can implement:
  * A beginning screen with something like: "Press enter to play" and "Press 'h' for key controls and instructions"
  * Add music to the game and maybe some sound that will play once a line is cleared
  * Add "levels" to the game - making the game faster with more lines that are cleared.
