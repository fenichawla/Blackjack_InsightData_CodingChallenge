#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include <string> // Using C version of string
#include "Logger.h"
#include "Cards.h"

#define INITIAL_NUM_CHIPS 100
#define BLACKJACK_MAX_VALUE 21
#define DEALER "Dealer"

using namespace std;

// Implement a generic player
class CBasePlayer
{
 private:
  // Variables specific to single blackjack game
  int NumAces;
  int TotalWithoutAces;

  // Total at the end of the game when player decides to stand
  int FinalTotal;

  // set follwoing to true if player decides to split after the first two cards are dealt

 protected:
  
  // Variable that stores the player name
  std::string PlayerName;
  // Vector of Cards seen so far in this hand
  vector <Cards::Card> Hand;

 public:
  // Constructor
  CBasePlayer();
	
  string GetName();
  void SetPlayerName(string);

  // Return true if blackjack hand is achieved
  bool IsBlackjack();

  // Return max score below 21 at any given moment
  int GetCurrentScore();

  void PrintScore();

  // Return true if player hand is busted
  bool IsBusted();

  // Function that is called at the end of each game to reset variables
  void EndHand();

  // Functions for the options that a player has during blackjack game
  void Hit(const Cards::Card);	
  void Stand();	

  // Function to return private members
  int GetNumAces();
  int GetTotalWithoutAces();

  void SetNumAces(int);
  void SetTotalWithoutAces(int);
  void SetFinalTotal(int);
  const vector<Cards::Card> GetHand();
};

// Implement player
class CPlayer: public CBasePlayer
{
 private:
  // Variables associated with a single player
  int ChipsWagered;
  int RemainingChips;
	
 public:
  // Constructor
  CPlayer(const std::string& name)
    {
      ChipsWagered = 0;
      RemainingChips = INITIAL_NUM_CHIPS;
      PlayerName = name;
    };

  // Function that is called to reset the player state
  void Reset();
	
  // Function which is called when the player begins the game
  void BeginGame(int);

  // Function which is called when the game ends
  void EndHand(unsigned int);

  // Function which is called when player doubles wager
  bool Double();

  // Functions to return private members
  int GetChipsWagered();
  int GetChips();

  // Functions to set private members
  void SetChipsWagered(int);
  void SetChips(int);
};

// Implement dealer 
class CDealer: public CBasePlayer
{
 private:

 public:
  // constructor
  CDealer()
    {
      PlayerName = DEALER;
    };
	
  // following returns true when total is hard 17 or greater, or when total is greater than soft 17 
  bool IsReadyToStand();
};

#endif //__PLAYER_H__
