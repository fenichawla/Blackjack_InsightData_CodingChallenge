#include <iostream>
#include <iomanip>
#include <ctype.h>
#include "Messages.h"
#include "Logger.h"

using namespace std;

void PrintAsteriskLine()
{
  cout << setfill('*') << setw(80) <<"" <<endl;
  return;
}

void PrintHandBeginsMessage(string name, int remainder)
{
  PrintAsteriskLine();
  cout << name << ", you have " << remainder << " chips to play with" ;
  cout << endl << " " << setfill('-') << setw(strlen(HAND_BEGINS_MESSAGE)+2) <<"";
  cout << endl << "| " << HAND_BEGINS_MESSAGE << " |";
  cout << endl << " " << setfill('-') << setw(strlen(HAND_BEGINS_MESSAGE)+2) <<"";
  cout << endl;
  PrintAsteriskLine();
  return;
}

void PrintHandQuitMessage()
{
  cout << endl << " " << setfill('-') << setw(strlen(HAND_QUIT_MESSAGE)+2) <<"";
  cout <<endl << "| " << HAND_QUIT_MESSAGE << " |";
  cout << endl << " " << setfill('-') << setw(strlen(HAND_QUIT_MESSAGE)+2) <<"";
  cout <<endl;
  return;
}


void PrintPlayerScore(string name, int score)
{
  cout << " -- " << name << "\t\t<< " << score << " >>" <<endl;
  return;
}

void PrintWelcomeMessage()
{
  PrintAsteriskLine();
  cout << "\t   Welcome to Casino Blackjack!\n";
  cout << "\t\tI am your Dealer!\n";
}

string AskPlayerName()
{
  string name;
  cout << "What's your name, warrior? ";
  do
    {
      SAFECIN(name);
      if (name.length() != 0)
	break; // exit while(1) loop
      cout << "Hunh, I can't hear you!" <<endl;
    } while(1);
  return name;
}

int AskMainMenuChoice(string name)
{
  int choice;
  cout << "\nPlease select from the following menu:\n";
  cout << "1. Study Rulebook \t\t (recommended for newbies)\n";
  cout << "2. Play BlackJack \t\t (you start with 100 chips)\n";
  cout << "3. Display high scores \t\t (see what you are up against)\n";
  cout << "4. Exit the game \t\t (why would you?)\n";
  do 
    {
      cout << "\nEnter your numerical choice here: ";
      SAFECIN(choice);
      if ((choice <= 4) && (choice >= 1))
	break; // exit while(1) loop
      cout <<"Oops, invalid choice! Please try again" <<endl;
    } while (1);
  return choice;
}

void PrintExitMessage(string name)
{
  cout << "Thanks for playing with us " << name
       <<", hope to see you again soon!\n\n";
  return;
}

void PrintWagerStatement(int wager, int total, bool tooHigh)
{
  if (tooHigh)
      cout << "Your wager is too high. \n";
  else
    cout <<"You wagered " << wager << " chips out of "
	 << total << " chips" << endl;
  return;
}

int AskWager()
{
  int wager = 0;
  while (wager <= 0)
    {
      cout << "So, how many chips would you like to wager? ";
      SAFECIN(wager);
      if (wager <= 0)
	cout << "C'mon, wager something for real!" <<endl;
    }
  return wager;
}

bool AskChoiceToPlayAgain(int total)
{
  char inp;
  cout << "You have " << total << " chips remaining. "
       << "Would you like to play again (Y/N)? ";
  do
    {
      SAFECIN(inp);
      if (toupper(inp) == 'Y') return true;
      if (toupper(inp) == 'N') return false;
      cout << "Incorrect selection. What's it going to be? (Y/N)";
    } while (1);
  return false;
}

char AskPlayerHandOptions()
{
  char op;
  cout << "What next - [H] Hit <or> [S] Stand <or> [D] Double <or> [X] Hint ?";
  SAFECIN(op);
  return toupper(op);
}

void PrintIncorrectSelectionMessage()
{
  cout << "Incorrect selection. Please try again." << endl;
  return;
}
void PrintFinalScoreMessage()
{
  cout << "\t\t----------------" <<endl;
  cout << "\t\t**Final Scores**" <<endl;
  cout << "\t\t----------------" <<endl;
  return;
}

void PrintOutOfChipsMessage()
{
  cout << "Unfortunately you have run out of chips. Your game ends here. \n";
  return;
}

void PrintDoubleHandMessage(bool isOK)
{
  if (!isOK)
    {
      cout << "Player not allowed a double hand, too few chips" <<endl;
      return;
    }
  cout << "Doubling down..";
  return;
}

void PrintHitHandMessage()
{
  cout << "Hit..."<<endl;
  return;
}

void PrintStandHandMessage()
{
  cout << "Stand..."<<endl;
  return;
}

void PrintPlayerStandMessage(string name)
{
  cout << "\t[[" << name << "]] \tstands" << endl;
  return;
}

void PrintResult(RESULT_TYPE op, string player, unsigned int outcome)
{
  switch(op)
    {
    case PUSH:
      cout << "~~Game drawn!~~" <<endl;
      break;
    case PLAYER_WIN:
      cout << "~~Congratulations " << player<<"!!!"
	   << " You won " << outcome << " chips.~~"<<endl;
      break;
    case DEALER_WIN:
      cout << "~~Sorry :-( You lost " << outcome << " chips.~~" << endl;
      break;
    case PLAYER_BUST:
      cout << "~~Crap! You went bust "<< player <<"~~" <<endl;
      break;
    case PLAYER_BLACKJACK:
      cout << "~~Woohoo! BlackJack!!" <<endl;
      break;
    case PLAYER_21:
      cout << "~~Whoot! 21!~~" << endl;
      break;
    case PLAYER_BLACKJACK_WIN:
      cout << "~~WOW! BlackJack! You rock, and won " << outcome
	   << " chips!~~" << endl;
      break;
    case DEALER_BUST:
      cout << "~~Yay! " << player << " went bust. You win this hand!~~" <<endl;
      break;
    case DEALER_BLACKJACK:
      cout << "Uh oh! " << player << " has a BlackJack here.." <<endl;
      break;
    default:
      DEBUG_LOG(1, "Unexpected result "<< op);
    }
  return;
}

void PrintCardDraw(string player, string cardstr)
{
  cout << "\t[[" << player << "]]"<< "\t draws\t\t[["<< cardstr <<"]]"<<endl;
  return;
}

void PrintScoreRow(int ctr, std::string name, int score)
{
  cout << left << setfill(' ') << "#" <<setw(5) << ctr 
       << setw(12) << name 
       << setw(10) << "scored"
       << score << endl;
  return;
}

void PrintHighScoreHeader()
{
  cout << endl;
  cout << setfill(' ');
  cout << right << setw(30) << "All Time High Scores" << endl;
  cout << right << setw(30) << "--------------------" << endl;
  return;
}

void PrintHighResultProbability(float *probs, int num)
{
  cout << setfill(' ');
  cout << right << setw(45) << "Some possible scenarios" << endl;
  cout << right << setw(45) << "-----------------------" << endl;
  for (int i=0; i<num; i++)
    {
      cout << "\tProbability of hitting "<<(21-i)<< " with next card:"<<probs[i]<<"%" << endl;
    }  
  return;
}
