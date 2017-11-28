#include "provider.h"
#include "game.h"

#include <iostream>


using namespace std;


/**
 * Announce the game, invite the player to think of a word.
 * Return the length of the word.
 */
int Provider::initialPrompt ()
{
  cout << "Let's play Hangman!\n\n"
       << "Please think of a word from 4-9 characters long. The word\n"
       << "should not be a proper name (something that you would normally\n"
       << "capitalize, nor should it contain any punctuation characters.\n"
       << "\n\nOK, got a word?\n" << endl;
  int len = 1;
  while (len < 4 || len > 9)
    {
      cout << "How long is your word? " << flush;
      cin >> len;
      if (len < 4 || len > 9)
	{
	  cout << "Please choose a word between 4 and 9 characters long."
	       << endl;
	}
    }
  return len;
}



bool getYesNoResponse()
{
  string response;
  getline (cin, response);
  while (response.size() == 0 || 
	 (response[0] != 'y' && response[0] != 'Y'
	  && response[0] != 'n' && response[0] != 'N'))
    {
      if (response.size() > 0)
	cout << "Please respond 'yes' or 'no'. " << flush;
      getline (cin, response);
    }
  return response[0] == 'y' || response[0] == 'Y';  
}



/**
 * Find out from provider if the latest guess is in the word or not and,
 * if it is, update the word by inserting the guessed character at the
 * appropriate positions.
 */
void Provider::getResponseToGuess (char guess, bool& isInWord,
				   std::string& wordSoFar,
				   int numMissedGuesses)
{
  cout << "I have missed " << numMissedGuesses << " guesses ("
       << Game::MAX_MISTAKE_LIMIT - numMissedGuesses << " misses left)"
       << endl; 
  cout << "\n" << wordSoFar << "\n";
  for (int i = 1; i <= wordSoFar.size(); ++i)
    cout << i;
  cout << "\n\nDoes your word contain the letter '" 
       << guess << "'? (y/n) " << flush;
  isInWord = getYesNoResponse();
  if (isInWord) {
      string response;
      bool done = false;
      string newWord;
      while (!done)
	{
	  cout << "Enter all of the character positions (1-"
	       << wordSoFar.size() << ") in which the letter '"
	       << guess <<  "' appears: " << flush;
	  getline (cin, response);
	  bool digitsFound = false;
	  newWord = wordSoFar;
	  for (int i = 0; i < response.size(); ++i)
	    {
	      char d = response[i];
	      if (d >= '1' && d <= '0' + wordSoFar.size())
		{
		  int k = d - '1';
		  if (wordSoFar[k] == Game::FILL_CHARACTER)
		    {
		      newWord[k] = guess;
		      digitsFound = true;
		    }
		}
	    }
	  if (digitsFound)
	    {
	      cout << "Like this: " << newWord << "? (y/n) " << flush;
	      bool yn = getYesNoResponse();
	      if (yn)
		{
		  wordSoFar = newWord;
		  done = true;
		}
	    }
	}
  }
}



/**
 * Announce that the provider has won the game, and get the
 * provider's actual word.
 */
std::string Provider::providerHasWon ()
{
  cout << "Congratulations, you have won." << endl;
  cout << "\nOut of curiosity, what was your word? " << flush;

  string answer;
  getline (cin, answer);
  return answer;
}


/**
 * Announce that the guesser has won the game, and get the
 * provider's actual word.
 */
void Provider::providerHasLost (string wordSoFar)
{
  cout << wordSoFar
       << "\n\nI have won!\nThanks for playing" << endl;
}


