#include "guesser.h"
#include "game.h"

#include <iostream>
#include <fstream>


using namespace std;

const std::string Guesser::alphabet = "abcdefghijklmnopqrstuvwxyz";



// Initialize the guesser for a game wit hthe indicated wordlength,
// using words from an indicated file.
Guesser::Guesser (int wordLength, const char* wordListFilename)
{
  for (int i = 0; i < 26; ++i)
    charactersTried[i] = false;

  string word;
  ifstream in (wordListFilename);
  while (in >> word)
    {
      if (word.size() == wordLength)
	{
	  // word is of desired length
	  if (word.find_first_not_of(alphabet) == string::npos) {
	    // word contains only lowercse alphabetics
	    possibleSolutions.push_back (word);
	  }
	}
    }
  in.close();

}


/**
 * Scan the words that are possible solutions so far, counting, for 
 * each letter not already tried, the number of words with that letter.
 * Guess the letter that occurs in the most words.
 */
char Guesser::guessACharacter()
{
  int counts[26];
  for (int i = 0; i < 26; ++i)
    counts[i] = 0;
  
  // Count the number of words in which each letter can be found
  for (int i = 0; i < possibleSolutions.size(); ++i)
    {
      string word = possibleSolutions[i];
      for (char c = 'a'; c <= 'z'; ++c)
	{
	  if (!charactersTried[c- 'a'])
	    {
	      // Character c has not been tried yet
	      if (word.find(c) != string::npos)
		// c is in this word
		++counts[c - 'a'];  
	    }
	}
    }

  // Find the character that occurs in the most words
  char guess = ' ';
  int maxSoFar = -1;
  for (char c = 'a'; c <= 'z'; ++c)
    {
      if (counts[c - 'a'] > maxSoFar)
	{
	  guess = c;
	  maxSoFar = counts[c - 'a'];
	}
    }


  if (maxSoFar <= 0)
    {
      guess = 'a';
      while (charactersTried[guess-'a'])
	++guess;
    }

  charactersTried[guess-'a'] = true;
  return guess;
}


/**
 * Following a successful guess of a letter in the word, make a pass through
 * the possibleSolutions, removing all words that do not contain the
 * guess character in the positions indicated in wordSoFar.
 */
void Guesser::characterIsInWord (char guess, const string& wordSoFar)
{
  vector<string> remainingSolutions;
  for (int i = 0; i < possibleSolutions.size(); ++i)
    {
      string wd = possibleSolutions[i];
      bool OK = true;
      for (int k = 0; OK && k < wordSoFar.size(); ++k)
	{
	  if (wordSoFar[k] == guess)
	    {
	      if (wd[k] != guess)
		{
		  OK = false;
		}
	    }
	}
      if (OK)
	{
	  //cerr << "Keeping " << wd << endl;
	  remainingSolutions.push_back (wd);
	}
    }
  possibleSolutions = remainingSolutions;

}


/**
 * Following a mistaken guess of a letter in the word, make a pass through
 * the possibleSolutions, removing all words that contain the
 * guess character.
 */
void Guesser::characterIsNotInWord (char guess)
{
  vector<string> remainingSolutions;
  for (int i = 0; i < possibleSolutions.size(); ++i)
    {
      string wd = possibleSolutions[i];
      if (wd.find(guess) == string::npos)
	{
	  remainingSolutions.push_back (wd);
	}
    }
  possibleSolutions = remainingSolutions;
}


/**
 * Guesser has lost the game. Look at the provider's actual word
 * and gripe a bit about losing.
 */
void Guesser::admitToLoss (std::string actualWord, const string& wordSoFar)
{
  bool match = actualWord.size() == wordSoFar.size();
  for (int i = 0; match && i < actualWord.size(); ++i)
    {
      match = wordSoFar[i] == Game::FILL_CHARACTER || 
	wordSoFar[i] == actualWord[i];
    }
  if (!match)
    {
      cout << "Ummm...your word '" << actualWord
	   << "' does not match the patterh '"
	   << wordSoFar <<"'.\nDid you make a mistake somewhere?"
	   << endl;
    }
  else
    {
      for (int i = 0; match && i < actualWord.size(); ++i)
	{
	  if (wordSoFar[i] == Game::FILL_CHARACTER
	      && charactersTried[actualWord[i]-'a'])
	    {
	      cout << "Did you forget to mention the '"
		   << actualWord[i]
		   << "' in position " << i+1 << "?"
		   << endl;
	      return;
	    }
	}
      
      for (int i = 0; (!match) && i < possibleSolutions.size(); ++i)
	match = (actualWord == possibleSolutions[i]);
      match = match && (possibleSolutions.size() > 0);
      if (match)
	{
	  cout << "OK, I might have guessed that eventually." << endl;
	}
      else
	{
	  cout << "Interesting, I don't know that word. Are you sure you\n"
	       << "spelled it correctly?." << endl;
	}

    }
}
 


