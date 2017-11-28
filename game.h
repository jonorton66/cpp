#ifndef GAME_H
#define GAME_H

#include <string>


// A non-alphabetic character
extern const char FILL_CHARACTER; 


// What is known of the word being guessed. This string is of the
// correct length, with all known characters filled in and the unknown
// positions containing FILL_CHARACTER.
extern std::string wordSoFar;


// How many characters have been guessed that are not in the word?
extern int numMissedGuesses;


// Maximum number of mistaken guesses permitted before the guesser has
// lost the game.
extern const int MAX_MISTAKE_LIMIT;

// Set up a new game, using a word of the indicated length
void setUpGame (int wordLength);

// Indicates whether the game is finished and, if so,
// if the guesser has won
bool guesserHasWon();

// Indicates whether the game is finished and, if so,
// if the guesser has lost
bool guesserHasLost();

// Update game state to reflect a new guess
void guessHasBeenMade (char guess);


#endif
