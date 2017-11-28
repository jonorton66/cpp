#ifndef PROVIDER_H
#define PROVIDER_H

#include <string>


class Provider {
public:

  /**
   * Announce the game, invite the player to think of a word.
   * Return the length of the word.
   */
  int initialPrompt ();
  
  
  /**
   * Find out from provider if the latest guess is in the word or not and,
   * if it is, update the word by inserting the guessed character at the
   * appropriate positions.
   */
  void getResponseToGuess (char guess, bool& isInWord,
			   std::string& wordSoFar,
			   int numMissedGuesses);
  
  
  
  /**
   * Announce that the provider has won the game, and get the
   * provider's actual word.
   */
  std::string providerHasWon ();
  
  
  /**
   * Announce that the guesser has won the game.
   */
  void providerHasLost (std::string wordSoFar);
  
private:


};



#endif
