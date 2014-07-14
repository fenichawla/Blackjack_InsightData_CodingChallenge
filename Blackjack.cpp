#include "Messages.h"
#include "Blackjack.h"
#include "Rulebook.h"
#include <stdlib.h>

CBlackJack::CBlackJack(const std::string& playerName, int numDecks, 
		       const std::string& highScoreFile, int numHighScores)
  :Player(playerName),
   CardDeck(numDecks)
{
  HighScoreHandler.SetFile(highScoreFile);
  HighScoreHandler.SetHighScore(numHighScores);
  return;
}

void CBlackJack::ProvideRules()
{
  DisplayRuleBook();
  return;
}

void CBlackJack::ExitGame()
{
  PrintExitMessage(Player.GetName());
  return;
}

void CBlackJack::DisplayHighScores()
{
  HighScoreHandler.DisplayHighScores();
  return;
}

// Function that asks player for number of chips that he/she wants to wager and set the wager
bool CBlackJack::GetSetPlayerWager()
{
  int playerWager = AskWager();
  bool tooHigh = playerWager > Player.GetChips(); 
  PrintWagerStatement(playerWager, Player.GetChips(),tooHigh);
  if(tooHigh)
    {
      DEBUG_LOG(1, "Wager of "<<playerWager
		<<" against remaining chips of "<<Player.GetChips());
      return false;
    }
  Player.BeginGame(playerWager);
  return true;
}

// Function that displays player options until the player decides to stand
void CBlackJack::PlayerOptionsAndPlay()
{
  while (!Player.IsBusted() && (Player.GetCurrentScore() != BLACKJACK_MAX_VALUE))
    {
      char playerChoice = AskPlayerHandOptions();
      if ('H' == playerChoice)
	{
	  PrintHitHandMessage();
	  Hit(Player);
	  Player.PrintScore();
	}
      else if ('S' == playerChoice)
	{
	  PrintStandHandMessage();
	  Player.Stand();
	  Player.PrintScore();
	  break; // exit the while() loop
	}
      else if ('D' == playerChoice)
	{
	  bool isDoubleAllowed = Player.Double();
	  PrintDoubleHandMessage(isDoubleAllowed);
	  if(isDoubleAllowed)
	    { 
	      // Player is allowed to double
	      // The player will now be hit once and then forced to stand
	      PrintWagerStatement(Player.GetChipsWagered(), 
				  (Player.GetChips()+Player.GetChipsWagered()),
				  false); //this isn't too high by definition
	      Hit(Player);
	      Player.Stand(); //Make the Player Stand now
	      Player.PrintScore();
	      break; // exit the while() loop
	    }
	}
      else if ('X' == playerChoice)
	{
	  const vector<Card> playerHand = Player.GetHand();
	  int* sum = BlackJackValueList(&playerHand[0], playerHand.size());
	  float* prob = CardDeck.HighResultProbability(&(sum[1]), sum[0], HINT_NUM);
	  PrintHighResultProbability(prob, HINT_NUM);
	  free(sum);
	  free(prob);
	}
      else 
	{
	  PrintIncorrectSelectionMessage();
	}
    }// end while() loop

  // Check why player stopped playing and print appropriate messages
  if (Player.IsBusted())
    {
      PrintResult(PLAYER_BUST, Player.GetName(), 0); 
    }
  else if (Player.GetCurrentScore() == BLACKJACK_MAX_VALUE)
    {
      PrintResult(PLAYER_21, Player.GetName(), 0);
    }
  else
    {
      DEBUG_LOG(1, "Player stopped for unexpected reason");
    }
}

// Function that displays dealer's hand until the dealer hand reaches a value of 17
void CBlackJack::DealerOptionsAndPlay()
{
  while (!Dealer.IsBusted() && !Dealer.IsReadyToStand())
    {
      Hit(Dealer);
      Dealer.PrintScore();	
    } // end while loop

  if(Dealer.IsBusted())
    PrintResult(DEALER_BUST, Dealer.GetName(), 0);
  else 
    PrintPlayerStandMessage(Dealer.GetName());
  return;
}

// Function that checks who won and calculates the payout
void CBlackJack::CheckWinnerCalculatePayout()
{
  // Return the wagered chips to the player
  unsigned int wager = Player.GetChipsWagered();
  unsigned int payback = 0;
  PrintFinalScoreMessage();
  PrintPlayerScore(Player.GetName(), Player.GetCurrentScore());
  PrintPlayerScore(Dealer.GetName(), Dealer.GetCurrentScore());

  // Case1: Player gets blackjack hand
  if(Player.IsBlackjack())
    {
      if(Dealer.IsBlackjack())  // Blackjack vs. Blackjack is a PUSH
	{
	  //Player does not lose any chips.
	  payback = wager;
	  PrintResult(PUSH, Player.GetName(), 0);
	}
      else //Player wins the BlackJack hand
	{
	  // BlackJack pays 3:2 the wager
	  payback = (int)((float)wager + (1.5 * (float)wager));
	  PrintResult(PLAYER_BLACKJACK_WIN, Player.GetName(),
		      (int)(ceil(1.5 * (float)(wager))));
	}
    }
  else if (Player.IsBusted())
    {
      if(Dealer.IsBusted()) //Push case
	{
	  // Player gets wager back
	  payback = wager;
	  PrintResult(PUSH, Player.GetName(), 0);
	}
      else // Dealer clearly wins, Player Bust
	{
	  // Player loses wager
	  payback = 0;
	  PrintResult(DEALER_WIN, Player.GetName(), wager);
	}
    }
  else if (Dealer.IsBusted()) //Player clearly wins
    {
      // Player gets back twice the wager
      payback = wager * 2;
      PrintResult(PLAYER_WIN, Player.GetName(), wager);
    }
  else if (Player.GetCurrentScore() > Dealer.GetCurrentScore()) // Player clearly wins
    {
      // Player gets back twice the wager
      payback = wager * 2;
      PrintResult(PLAYER_WIN, Player.GetName(), wager);
    }
  else if (Player.GetCurrentScore() == Dealer.GetCurrentScore()) // Push case
    {
      // Player gets the wager back
      payback = wager;
      PrintResult(PUSH, Player.GetName(), 0);
    } 
  else //Dealer clearly wins
    {
      // Player loses the wager
      payback = 0;
      PrintResult(DEALER_WIN, Player.GetName(), wager);
    }

  EndHand(payback);
  return;
}

void CBlackJack::EndHand(unsigned int payback)
{
  Player.EndHand(payback);
  Dealer.EndHand();
  PrintAsteriskLine();
  return;
}

// Function that gives the player option of playing again
bool CBlackJack::EndOption()
{
  if(Player.GetChips() > 0)
    {
      return AskChoiceToPlayAgain(Player.GetChips());
    }
  else
    {
      PrintOutOfChipsMessage();
      return false;
    }
}

void CBlackJack::Hit(CBasePlayer &p)
{
  Card c = CardDeck.DrawCard();
  p.Hit(c);
  PrintCardDraw(p.GetName(), CardToString(c));
  return;
}

// Main function that executes the blackjack game with a new player
void CBlackJack::StartGameWithNewPlayer()
{
  bool playAgain = true;
  PrintHandBeginsMessage(Player.GetName(), Player.GetChips());

  while(playAgain)
    {
      // Ask player for a wager. It returns true if valid wager is returned
      if(GetSetPlayerWager())
	{
	  // Hit the player twice 
	  Hit(Player);
	  Hit(Player);
	  DEBUG_LOG (4, "Hit Player twice");
	  if(Player.IsBlackjack())
	    PrintResult(PLAYER_BLACKJACK, Player.GetName(), 0);

	  // Hit dealer twice
	  Hit(Dealer);
	  Hit(Dealer);
	  DEBUG_LOG (4, "Hit Dealer twice");
	  if(Dealer.IsBlackjack())
	    PrintResult(DEALER_BLACKJACK, Dealer.GetName(), 0);

	  // If dealer or player got blackjack or busted, then game can end here. 
	  // Else, continue playing
	
	  if(!Player.IsBlackjack() && !Player.IsBusted()
	     && !Dealer.IsBlackjack() && !Dealer.IsBusted())
	    {
	      // Display scores
	      Player.PrintScore();
	      Dealer.PrintScore();

	      // Give playing options to player and play
	      PlayerOptionsAndPlay();
	      // Unless player is busted, continue hitting the dealer
	      if(!Player.IsBusted())
		DealerOptionsAndPlay();				
	    }
			
	  // At the end, check for winner, and calculate payout
	  CheckWinnerCalculatePayout();
	}

      // Ask player for another game
      playAgain = EndOption();

    } // end while playAgain

  // Add player's score to high scores
  DEBUG_LOG(1, "Remaining chips " << Player.GetChips());
  HighScoreHandler.AddNewScore(Player.GetName(), Player.GetChips());

  // Reset remaining chips with player
  Player.Reset();

  PrintHandQuitMessage();
}


