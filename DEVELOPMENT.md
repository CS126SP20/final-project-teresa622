# Development

---
- **5/2/20** Implemented utils class to avoid duplicate code in files and implemented a simple test for it
- **5/1/20** Tested for restarting game and score updating based on cleared lines
    * Add live update of score on the screen
    * Consider adding beginning screen?
    * Should Location be tested?
- **4/30/20** Modified some functions to make them more testable for rotation conflicts and then tested for this 
conflict
    * Check that all comments are followed by spaces
    * Create a utils file to avoid repetitive code for generating a random number? Or would this be unnecessary
    for just one function?
    * Rename row and column in our location class to better suit the interpretation of row and column for Tetris
    * Test that the score correctly increases if line(s) are cleared
- **4/27/20** Added more tests (movemnt conflicts) for engine
    * Finish up testing engine (rotation conflict testing)
- **4/26/20** Implemented sound effects
    * Need to add clarifying comments to tetromino types and perhaps some more event keys 
    (pause, mute sounds, maybe an opening screen)
    * Improve the end screen as well
    * Remember to modify the sound effects to make some louder
- **4/22/20** Added colors to the tetrominoes!
    * Continue testing functionalities
    * I want to add a projection of the falling tetromino onto the surface. Makes it easier to play.
- **4/21/20**  Added the scoring and end game features of Tetris
    - Work on more stretch goals for the upcoming week.
    - Continue to test more of the testable functionalities.
- **4/20/20** Implemented line clearing functionality
    - [ ] Figure out how to not have more than 3 of the same tetromino in a row. Or should it be completely random..?
    - [X] Add color to the tetrominoes. Maybe this functionality will be implemented in the farther future.
    - [X] Figure out how to end the game if the player reaches the top of the screen
    - [X] Implement more scoring functionalities with the database
    * Continue to keep testing more
- **4/19/20** Implemented rotation functionality
    * Consider modifying the rotation of L tetromino
    * Test more of tetromino
    * Next development: Implement user modified game settings(tile size, screen size, etc.) via command line
- **4/18/20** Figured out how to make tetrominoes fall and stack on top of each other.
    * Need to test all the currently functioning code
    * Next development: Translating and rotating tetrominoes with key controls
- **4/17/20** Began implementing Tetris
    * Figured out how to get randomly generated tetromino piece
    * Note: C++ uses time as a seed to generate random numbers
    * Next task: Make pieces fall down the screen