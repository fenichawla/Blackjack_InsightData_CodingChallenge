#include "Player.h"
#include "Messages.h"

using namespace Cards;

CBasePlayer::CBasePlayer()
{
  NumAces = 0;
  TotalWithoutAces = 0;
  FinalTotal = 0;
}

// Return TRUE if player holds a blackjack hand (ACE + ten or Face card(J/Q/K))
bool CBasePlayer::IsBlackjack()
{
  if (Hand.size()==2 && NumAces == 1 && TotalWithoutAces == 10)
    return true;
  else
    return false;
}

// Return TRUE if total exceeds BLACKJACK_MAX_VALUE (21)
bool CBasePlayer::IsBusted()
{
  if(NumAces == 0)
    {
      if(TotalWithoutAces > BLACKJACK_MAX_VALUE)
	return true;
      else
	return false;
    }	
  else
    {
      // We only need to check hard total here (where ACES are considered to have value of 1
      if(TotalWithoutAces + NumAces > BLACKJACK_MAX_VALUE)
	return true;
      else
	return false;
    }

  return false;	
}

// Implement function that is called when player selects Hit
// Return false in case of error, true otherwise
void CBasePlayer::Hit(Card c)
{
  Hand.push_back(c);
  int CardFaceValue = c.face_value;
  DEBUG_LOG(1, "Hitting "<<PlayerName<<" with value "<<CardFaceValue);
  // Check error conditions
  if(CardFaceValue < 1 || CardFaceValue > 13)
    DEBUG_LOG(0, "Error: received CardFaceValue: "<<CardFaceValue);	

  // Update the number of aces or the total value
  if (CardFaceValue == 1)
      NumAces++;
  else if (CardFaceValue <= 10) 
      TotalWithoutAces += CardFaceValue;
  else // Face card
      TotalWithoutAces += 10;
  return;
}

void CBasePlayer::PrintScore()
{
  PrintPlayerScore(PlayerName, GetCurrentScore());
  return;
}

// Function that calculates the max score for a player taking hard and soft hands into consideration
int CBasePlayer::GetCurrentScore()
{
  DEBUG_LOG(1, "Getting current score for "<<PlayerName);
  int currentScore = 0;
  int hardTotal = 0, softTotal = 0;
  int aceCount = 0;

  DEBUG_LOG(2, "Total without Aces:"<<TotalWithoutAces);
  DEBUG_LOG(2, "Num of Aces:"<<NumAces);
  // First check hard total, considering aces to be valued at 1
  hardTotal = TotalWithoutAces + NumAces; 
  // if hard total is <21, then keep adding each
  // ACE to find the max soft total
  currentScore = hardTotal;
	
  while(currentScore <= BLACKJACK_MAX_VALUE && aceCount < NumAces)
    {
      softTotal = currentScore + 10;
      if (softTotal <= BLACKJACK_MAX_VALUE)
	currentScore = softTotal;
      else
	break;
    }

  //finish:
  return currentScore;
}

// Implement function which is called when player decides to stand
void CBasePlayer::Stand()
{
  // Update final total for the player using following algorithm
	
  FinalTotal = GetCurrentScore();
  return;
}

void CBasePlayer::EndHand()
{
  // Reset everything else in preparation of the next game
  NumAces = 0;
  TotalWithoutAces = 0;
  FinalTotal = 0;
  Hand.clear();
}

string CBasePlayer::GetName() 
{
  return PlayerName;
}

void CBasePlayer::SetPlayerName(string name) 
{
  PlayerName = name;
}

int CBasePlayer::GetNumAces() 
{
  return NumAces;
}

int CBasePlayer::GetTotalWithoutAces() 
{
  return TotalWithoutAces;
}

void CBasePlayer::SetTotalWithoutAces(int total) 
{
  TotalWithoutAces = total;
}

void CBasePlayer::SetNumAces(int aces) 
{
  NumAces = aces;
}

void CBasePlayer::SetFinalTotal(int final) 
{
  FinalTotal = final;
}

const vector<Cards::Card> CBasePlayer::GetHand() 
{
  return Hand;
}

// Function that is called when the player starts the game
void CPlayer::BeginGame(int numChipsWagered)
{
  ChipsWagered = numChipsWagered;
  RemainingChips -= ChipsWagered;
}
// Function that is called when the game ends
void CPlayer::EndHand(unsigned int payout)
{
  // Update remaining number of chips
  RemainingChips += payout;
  // Reset everything else in preparation of the next game
  SetChipsWagered(0);
  SetFinalTotal(0);
  SetNumAces(0);
  SetTotalWithoutAces(0);
  Hand.clear();
  //isSplit = FALSE;
}

// Funciton to reset the player objects at the end of each game
void CPlayer::Reset()
{
  SetChipsWagered(0);
  SetFinalTotal(0);
  SetNumAces(0);
  SetTotalWithoutAces(0);
  Hand.clear();

  ChipsWagered = 0;
  RemainingChips = INITIAL_NUM_CHIPS;
}

// Implement function that gets called when player decides to double his/her bet
bool CPlayer::Double()
{
  int numRemainingChips = GetChips();
  int numChipsWagered = GetChipsWagered();

  // Change the wager and the remaining balance with the player
  if(numRemainingChips >= numChipsWagered)
    {
      numRemainingChips -= numChipsWagered;
      numChipsWagered *= 2;
    }
  else
      return false;

  SetChips(numRemainingChips);
  SetChipsWagered(numChipsWagered);

  return true;
}

int CPlayer::GetChipsWagered() 
{
  return ChipsWagered;
}

int CPlayer::GetChips() 
{
  return RemainingChips;
}

void CPlayer::SetChipsWagered(int chips) 
{
  ChipsWagered = chips;
}

void CPlayer::SetChips(int remainder) 
{
  RemainingChips = remainder;
}

// following returns true when total is 17 or greater 
bool CDealer::IsReadyToStand()
{
  if(GetCurrentScore() < 17)
    return false;
  else
    return true;
}

