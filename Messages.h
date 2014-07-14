#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include <string> // Using C version of string
#include <iostream>
#include <climits>

using namespace std;

enum RESULT_TYPE
  {
    PUSH,
    PLAYER_WIN,
    PLAYER_21,
    PLAYER_BLACKJACK,
    PLAYER_BLACKJACK_WIN,
    PLAYER_BUST,
    DEALER_WIN,
    DEALER_BUST,
    DEALER_BLACKJACK
  };

#define SAFECIN(input) std::cin >> input;\
                       std::cin.clear(); \
		       std::cin.ignore(INT_MAX, '\n');



#define PLAYER_DOUBLE_ERROR_MESSAGE "Bummer! Not enough chips to double."

#define HIGH_SCORE_TABLE_HEADER "\tName\t" << "\tFinal Chips\n";

#define PLAYER_LOSE_MESSAGE_STREAM(loss, remainder) "You lost " << loss << "chips, and now have " << remainder << " chips remaining" <<endl

void PrintAsteriskLine();
void PrintPlayerScore(std::string, int);
void PrintWelcomeMessage();
void PrintExitMessage(std::string);
void PrintHandQuitMessage();
void PrintFinalScoreMessage();
void PrintHandBeginsMessage(std::string, int);
void PrintWagerStatement(int, int, bool);
void PrintOutOfChipsMessage();
void PrintIncorrectSelectionMessage();
void PrintDoubleHandMessage(bool);
void PrintHitHandMessage();
void PrintStandHandMessage();
void PrintCardDraw(std::string, std::string);
void PrintHighScoreAbsentMessage();
void PrintScoreRow(int, std::string, int);
void PrintPlayerStandMessage(std::string);
void PrintResult(RESULT_TYPE, std::string, unsigned int);
void PrintHighScoreHeader();
void PrintHighResultProbability(float*, int);

// Print message and receive input methods
int AskWager(void);
bool AskChoiceToPlayAgain(int);
int AskMainMenuChoice(std::string);
char AskPlayerHandOptions();
std::string AskPlayerName();

#endif // __MESSAGES_H__

