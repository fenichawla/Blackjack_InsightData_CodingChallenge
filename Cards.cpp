#include <iostream>
#include <iomanip>
#include <string.h> //using C string header
#include <stdlib.h>
#include <time.h>
#include <random>
#include "Cards.h"
#include "Logger.h"

using namespace std;
using namespace Cards;

int GetRandomValue(const int OuterMax)
{
  //using the Knuth algorithm to generate random numbers
  random_device rd;
  knuth_b rg(rd());
  uniform_real_distribution<double> dist(0,OuterMax);

  int r = (int)dist(rg);
  return r;
}


int BlackJackValue_helper (int v)
{
  if (v <= 10)
    return v;
  return 10;
}

int* BlackJackValueCalculator(const Card c[], int num)
{
  int *result;
  if (c[num-1].face_value == 1) // Ace, can have two values
    {
      if (1 == num)
	{
	  result = new int[3];
	  result[0] = 2;
	  result[1] = 1;
	  result[2] = 11;
	}
      else
	{
	  int *sub_result = BlackJackValueCalculator(c, num-1);
	  result = new int[sub_result[0]*2 + 1]; //*2 for extra Ace value, +1 for length
	  result[0] = sub_result[0]*2; 
	  for (int i=0; i<sub_result[0]; i++)
	    {
	      result[i+1] = sub_result[i+1] + 1;
	      result[i+1+sub_result[0]] = sub_result[i+1] + 11;
	    }
	  free(sub_result);
	}
    }
  else  // Regular, single-value card 
    {
      if (1 == num)
	{
	  result = new int[2];
	  result[0] = 1;
	  result[1] = BlackJackValue_helper(c[0].face_value);
	}
      else
	{
	  result = BlackJackValueCalculator(c, num -1);
	  for (int i=0; i<result[0]; i++)
	    {
	      result[i+1] += BlackJackValue_helper(c[num-1].face_value);
	    }
	}
    }
  return result;
}

int* Cards::BlackJackValueList(const Card c[], int num)
{
  int* results = BlackJackValueCalculator(c, num);
  // the results may contain duplicates, that we will now need to remove
  int num_uniques = results[0];
  for (int i =0; i<results[0]; i++)
    {
      for (int j=i+1; j<results[0]; j++)
	{
	  if ((results[i] != 0) && (results[i] == results[j]))
	    {
	      results[j] = 0;
	      num_uniques--;
	    }
	}
    }
  int* unique_results = new int[num_uniques+1];
  unique_results[0] = num_uniques;
  for (int i=0, j=0; i<results[0]; i++)
    {
      if (0 != results[i+1])
	{
	  unique_results[j+1] = results[i+1];
	  j++;
	}
    }
  free(results);
  return unique_results;
}


string Cards::CardToString(Card c)
{
	string str;
	if (1 == c.face_value)
		str = "Ace";
	else if (11 == c.face_value)
		str = "Jack";
	else if (12 == c.face_value)
		str = "Queen";
	else if (13 == c.face_value)
		str = "King";
	else
		str = to_string(c.face_value);
	str = str + " of ";
	
	switch (c.suite)
	{
	case HEARTS:
		str = str + "Hearts";
		return str;
	case CLUBS:
		str = str + "Clubs";
		return str;
	case SPADES:
		str = str + "Spades";
		return str;
	case DIAMONDS:
		str = str + "Diamonds";
		return str;
	}
	return "";
}

CCardDeck::CCardDeck(int nD)
{
  if (nD <=0)
    nD = DEFAULT_NUM_DECKS;
  NumDecks = nD;
  for(int i=0; i<13; i++)
    {
      for(int j=0; j<4; j++)
	{
	  Deck[i][j] = NumDecks;
	}
    }
  NumCards = 13 * 4 * NumDecks;
  srand(time(NULL));
  return;
}

Card CCardDeck::DrawCard()
{
  int value = GetRandomValue(13) + 1;
  CARD_SUITE suite = (CARD_SUITE)GetRandomValue(4);
	
  if(0 == NumCards)
    {
      Card c = {0, HEARTS};
      return c;		
    }

  int num_flips = 0;
  while(0 == Deck[value][suite])
    {
      num_flips++ ;
      if(52 <= num_flips)
	{
	  // too many flips have happened, just begin a linear scan
	  for (int i=0; i< 13; i++) 
	    {
	      bool broken = false;
	      for (int j =0; j< 4; j++) 
		{
		  if (0 < Deck[i][j]) 
		    {
		      value = i;
		      suite = (CARD_SUITE)j;
		      broken = true;
		      break;
		    }
		}
	      if (broken) break;
	    }
	}
      else
	{
	  value = ((13 == value) ? 1 : value + 1);
	  suite = (CARD_SUITE)(rand() % 4);
	}
    }
  Deck[value][suite]--;
  Card c = {value, suite};
  NumCards--;
  return c;
}

int CCardDeck::GetNumCards()
{
  return NumCards;
}

int CCardDeck::NumCardsForTarget(int target)
{
  int sum = 0;
  if (target > 11 || target <= 0)
    sum = 0;
  else if (11 == target)
    {
      for (int i=0; i<4; i++) 
	{
	  sum += Deck[0][i]; // count all Aces
	}
    }
  else if (10 == target)
    {
      for (int i=0; i<4; i++)
	{
	  sum += Deck[9][i]; // count all Tens
	  sum += Deck[10][i]; // count all Jacks
	  sum += Deck[11][i]; // count all Queens
	  sum += Deck[12][i]; // count all Kings
	}
    }
  else
    {
      for (int i=0; i<4; i++) 
	{
	  sum += Deck[target-1][i];
	}
    }
  return sum;
}

float* CCardDeck::HighResultProbability(int* sum, int num_sum, int num_high)
{
  float* result = new float[num_high];
  float totalOutcomes = NumCards;
  for (int i=0; i<num_high; i++)
    {
      int max = 21 - i;
      int numPositiveOutcomes = 0;
      for (int j=0; j<num_sum; j++)
	{
	  DEBUG_LOG(2, "Checking for sum value "<<sum[j]);
	  numPositiveOutcomes += NumCardsForTarget(max - sum[j]);
	}
      result[i] = ((float)numPositiveOutcomes / totalOutcomes) * 100.0;
      DEBUG_LOG(2, "Hint for target " << max
		<< " numPositiveOutcomes "<< numPositiveOutcomes 
		<< " totalOutcomes "<<totalOutcomes);
    }
  return result;
}

