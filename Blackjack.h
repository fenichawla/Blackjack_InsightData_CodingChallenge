#ifndef __BLACKJACK_H__
#define __BLACKJACK_H__

#include <iostream>
#include <vector>
#include <string> // Using C version of string
#include <stdlib.h>
#include <math.h>
#include "Player.h"
#include "Cards.h"
#include "Logger.h"
#include "HighScores.h"

#define HINT_NUM 3

using namespace std;
using namespace Logger;
using namespace Cards;

class CBlackJack
{
 private:

  CPlayer Player; // can be made into an array for multiple players or in the case of split
  CDealer Dealer; 
  CCardDeck CardDeck;
  CHighScores HighScoreHandler;

  // functions

  // Function that asks player for number of chips that he/she wants to wager and set the wager 
  bool GetSetPlayerWager();

  // Function that displays player options until the player decides to stand
  void PlayerOptionsAndPlay();

  // Function that displays dealer's hand until the dealer hand reaches a value of 17
  void DealerOptionsAndPlay();

  // Function that checks who won and calculates the payout
  void CheckWinnerCalculatePayout();

  // Function that gives the player option of playing again
  bool EndOption();

  // Function that gets called at the beginning when player is hit
  void Hit(CBasePlayer&);

  void EndHand(unsigned int);
 public:
  CBlackJack(const std::string&, int, int);
	
  // Function that is called from main()
  void StartGameWithNewPlayer();

  // Function that is called from main()
  void DisplayHighScores();

  void ExitGame();

  void ProvideRules();
};

#endif // __BLACKJACK_H__
