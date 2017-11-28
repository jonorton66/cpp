#ifndef GUESSER_H
#define GUESSER_H

#include <string>
#include <vector>

class Game;

class Guesser {
public:
  // Initialize the guesser for a game with the indicated wordlength,
  // using words from an indicated file.
  Guesser (int wordLength, const char* wordListFilename);


  /**
   * Scan the words that are possible solutions so far, counting, for 
   * each letter not already tried, the number of words with that letter.
   * Guess the letter that occurs in the most words.
   */
  char guessACharacter();


  /**
   * Following a successful guess of a letter in the word, make a pass through
   * the possibleSolutions, removing all words that do not contain the
   * guess character in the positions indicated in wordSoFar.
   */
  void characterIsInWord (char guess, const std::string& wordSoFar);


  /**
   * Following a mistaken guess of a letter in the word, make a pass through
   * the possibleSolutions, removing all words that contain the
   * guess character.
   */
  void characterIsNotInWord (char guess);

  
  /**
   * Guesser has lost the game. Look at the provider's actual word
   * and gripe a bit about losing.
   */
  void admitToLoss (std::string actualWord, const std::string& wordSoFar);
private:

  // A collection of words that match all guesses made so far
  std::vector<std::string> possibleSolutions;

  // Tracks characters already guessed.
  //  charactersTried[c-'a'] is true if the character c
  //    has been guessed previously
  bool charactersTried[26];

  static const std::string alphabet;
};


#endif
