#include "Rulebook.h"
#include "Messages.h"

using namespace std;

void DisplayRuleBook()
{
  PrintAsteriskLine();
  cout << "BLACKJACK RULEBOOK:\n";
  cout << "You are given 100 chips to start with. Your objective is to beat the dealer by doing one of the following:\n";
  cout << "  1. Get 21 points on the first two cards (called blackjack)\n";
  cout << "  2. Reach final score higher than the dealer but lesser than 21\n";
  cout << "  3. Let dealer draw additional cards until his/her hand exceeds 21\n";
  cout << endl;
  cout << "Game flow: \n";
  cout << "You will be dealt 2 cards, and the dealer will be dealt 2 cards. ";
  cout << "Based on these, you will be asked to select from the following:\n";
  cout << "1. Hit - Take the next card from the dealer\n";
  cout << "2. Stand - Stay with current score\n";
  cout << "3. Double - Double your wager, then draw a card and stand\n";
  cout << "4. Hint - Get some help in making your decision\n";
  cout << endl;

  cout << "Once the player's hand is done, the dealer is hit until he hits a score of 17 or higher. ";

  cout << "When both hands are done, the result will be calculated as follows:\n";
  cout << "1. Blackjack hand - Any hand of ACE plus 10 or face card pays 3:2 (rounded up for odd wager)\n";
  cout << "2. Player scores higher than dealer - Player wins and is paid at 1:1\n";
  cout << "3. Player scores lower than dealer - Player loses his wager\n";
  cout << "4. Player busts - If player exceeds a total of 21, he loses his wager\n";
  cout << "5. Dealer busts - If dealer exceeds a total of 21, the player is paid at 1:1\n";
  cout << "6. Push - Dealer and player have the same score, the player is returned his wager\n";
  cout << endl;

  cout << "The score is calculated by totaling the face value of all the cards that a player is holding in his/her hand. The face value of aces can be counted as 1 or 11 depending on the value that gives a better score without going over 21. Face value of face cards (Jack, Queen or King) is counted as 10.\n";

  cout << endl;
  cout << "Good luck and may the odds ever be in your favor!\n";
  PrintAsteriskLine();
}
