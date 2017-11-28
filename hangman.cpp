#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

#include "game.h"
#include "provider.h"
#include "guesser.h"


using namespace std;



int main (int argc, char** argv)
{
  Provider provider;

  int wordSize = provider.initialPrompt();

  Game game (wordSize, "words", provider);

  bool gameFinished = false;

  while (!gameFinished) {
    
    char guess = game.getGuesser().guessACharacter();
    
    game.guessHasBeenMade (guess);
    
    gameFinished = game.guesserHasWon() || game.guesserHasLost();
  }


  if (game.guesserHasWon())
    game.getProvider().providerHasLost(game.getWordSoFar());
  else
    {
      string actualWord = game.getProvider().providerHasWon();
      game.getGuesser().admitToLoss (actualWord, game.getWordSoFar());
    }


  return 0;
}

  
