#ifndef __CARDS_H__
#define __CARDS_H__

#include<iostream>

#define DEFAULT_NUM_DECKS 8

namespace Cards {

enum CARD_SUITE
{
  HEARTS = 0,
  SPADES = 1,
  DIAMONDS = 2,
  CLUBS = 3
};

struct Card
{
  int face_value;
  CARD_SUITE suite;
};

int* BlackJackValueList(const Card[], int);

std::string CardToString(Card);

class CCardDeck
{
 private:
  int Deck[13][4];
  int NumCardsForTarget(int);
  int NumCards;
  int NumDecks;
 public:
  CCardDeck(int);
  Card DrawCard();
  int GetNumCards();
  float* HighResultProbability(int*, int, int);
};

}// namespace Cards

#endif // __CARDS_H__
