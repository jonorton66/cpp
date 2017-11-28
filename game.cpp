#include "game.h"
#include "guesser.h"
#include "provider.h"

using namespace std;

// A non-alphabetic character
const char FILL_CHARACTER = '.';


// What is known of the word being guessed. This string is of the
// correct length, with all known characters filled in and the unknown
// positions containing FILL_CHARACTER.
string wordSoFar;


// How many characters have been guessed that are not in the word?
int numMissedGuesses;


// Maximum number of mistaken guesses permitted before the guesser has
// lost the game.
const int MAX_MISTAKE_LIMIT = 10;

// Set up a new game, using a word of the indicated length
void setUpGame (int wordLength)
{
  wordSoFar = string(wordLength, FILL_CHARACTER);
  numMissedGuesses = 0;
}

// Indicates whether the game is finished and, if so,
// if the guesser has won
bool guesserHasWon()
{
  return wordSoFar.find(FILL_CHARACTER) == string::npos;
}

// Indicates whether the game is finished and, if so,
// if the guesser has lost
bool guesserHasLost()
{
  return numMissedGuesses >= MAX_MISTAKE_LIMIT;
}

// Update game state to reflect a new guess
void guessHasBeenMade (char guess)
{
  bool isInWord;
  getResponseToGuess (guess, isInWord, wordSoFar);
  if (isInWord)
    {
      characterIsInWord (guess, wordSoFar);
    }
  else
    {
      ++numMissedGuesses;
      characterIsNotInWord (guess);
    }
}

