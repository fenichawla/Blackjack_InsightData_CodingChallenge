// Implementation of the main function for Blackjack game

#include <iostream>
#include <string> // Using C version of string
#include "Blackjack.h"
#include "Logger.h"
#include "Messages.h"

using namespace Logger;
using namespace std;

int main(int argc, char** argv)
{
  int choice = 0;
  string playerName;
  int numDecks = 0, highScores = 0;
  string filepath = string(); 

  // Setup logger 
  Logger::initLogger();

  for (int i = 1; i < argc; i++) // parse input arguments 
    {
      if (string(argv[i]) == string("--logfile")) 
	Logger::setLogfile(argv[i+1]);
      if (string(argv[i]) == string("--loglevel")) 
	Logger::setLogLevel(argv[i+1]);
      if (string(argv[i]) == string("--numdecks"))
	numDecks = atoi(argv[i+1]);
      if (string(argv[i]) == string("--highscoresfile"))
	filepath = argv[i+1];
      if (string(argv[i]) == string("--highscores"))
	highScores = atoi(argv[i+1]);
    }
  DEBUG_LOG(1, "Number of cards:" << numDecks);
  PrintWelcomeMessage();
  playerName = AskPlayerName();
  cout << "Hi " << playerName << "!" <<endl;
  
  CBlackJack game(playerName, numDecks, filepath, highScores);
  
  typedef void (CBlackJack::*funcptr)();
  funcptr opts[4] = { &CBlackJack::ProvideRules, 
		      &CBlackJack::StartGameWithNewPlayer,
		      &CBlackJack::DisplayHighScores,
		      &CBlackJack::ExitGame
		      };
  do
    { 
      choice = AskMainMenuChoice(playerName); //choice is between 1 and 4
      (game.*opts[choice-1])();
    } while(choice != 4); // 4 is the Exit choice
  return 1;
}

