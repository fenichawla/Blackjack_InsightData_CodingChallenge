An Implementation of BlackJack
==============================
Version 1.0

Written by Feni Chawla

##ABOUT THIS PROGRAM

This program implements the popular casino game of BlackJack, using C++.

##ABOUT BLACKJACK
BlackJack is one of the most widely played casino games. It is a comparing game between the dealer and the player, where the player plays against the dealer, but not against the other players. The player can beat the dealer in the following ways:
* Get 21 points on the first 2 cards - called Blackjack
* Reach final score higher than the dealer without exceeding 21
* Let the dealer draw cards until his hand exceeds 21

To read more about BlackJack, please refer to this wikipedia article: 
en.wikipedia.org/wiki/Blackjack

##BLACKJACK TERMS USED IN THE PROGRAM
* Blackjack Hand - Any hand of ACE plus 10 or face card (Jack, Queen, or King) irrespective of the suite
* Hit - Hit is the act of taking the next card from the dealer 
* Stand - Stand is an option for the player, where he/she can choose to take no more cards and "Stand" or stay with their current score
* Double - Double is an option for the player, where the player can choose to double his/her wager. Following this, the player is "Hit" once before he stands.
* Bust - A player or dealer could go "Bust" if his/her hand exceeds a total of 21
* Push - Push occurs when the player and dealer have the same score at the end of a hand. In the case of a push, the player does not lose his wager.

##BLACKJACK RULES IMPLEMENTED IN THE PROGRAM
The game starts with the dealer dealing 2 cards to the player and 2 cards to himself. At this point, the player has the option to decide whether he would like to hit, stand or double. The player's hand ends when his/her hands goes bust or he/she decides to stand. Once the player's hand ends, the dealer is hit until he reaches a score of 17 or greater. Finally, the scores are compared  between the player and dealer, and payouts are made.

The Blackjack implementation in this program uses 8 card decks by default, which can be modified during runtime through a command line parameter.

## SCORING AND PAYOUTS
The score is calculated by totaling the face value of all the cards that a player is holding in his/her hand. The face value of aces can be counted as 1 or 11 depending on the value that gives a better score without going over 21. Face value of face cards (Jack, Queen or King) is counted as 10.

The payouts are calculated as the following:
* Winning blackjack hand is paid at 3:2 (Rounded up for odd wager)
* Winning non-blackjack hand is paid at 1:1
* In case of loss, the player loses his wager
* In case of Push, the player does not lose his wager, but does not win anything either

##PROGRAM STRUCTURE
The program is divided into the following classes:
* CCardDeck - This class manages the card decks used in this game. It implements functions for managing card draws and calculating the probabilities of obtaining high scores on the next card draw.

* CBasePlayer - This is a base class which implements functions that are common between dealer and player functionality, such as Hit() and Stand(). It also keeps track of the cards held by each player, which is used in the calculation of the probability of obtaining a high score.

* CPlayer - This class is derived from the CBasePlayer class, and implements all functionality that is unique for the Player, such as Double(). It also keeps track of the chips help by the player, and the winnings/losses between hands.

* CDealer - This class is also derived from CBasePlayer. It implements the function for determining whether the dealer should stand or continue drawing cards for himself/herself.

* CHighScores - This class implements high scores functionality. It keeps track of the highest scores and stores them in a file. By default, the location of the high scores file is "/tmp/HighScores.txt" and the number of high scores maintained is 5. The number of high scores can be modified through a command line parameter.

* CBlackJack - This class implements core blackjack functionality. It has objects of all other classes, and implements the sequence and logic for the game play, keeps track of player and dealer score, finds the winner and calculates payout and provides game rules and high scores.

* namespace Logger - This namespace implements log messages used throughout the program for implementing logging functionality. This is used for writing debug logs to a file. Currently the log level has been set to a default of 2, which enables logging of all DEBUG_LOG messages with log level equal to and less than 2. The log level can be modified through a command line parameter.

* Messages.h file - This file implements functions for parsing and printing out messages to stdout and the log files. This is used throughout the program.

*Makefile - A make file has been provided to compile and link the program. The name of the output executable file is "Play"

##BUILDING THE PROGRAM
The program folder contains a Makefile, which can be used to build the executable. To build the executalbe, simply run the following from the command line:
make clean 

Followed by:
make
OR
make release
OR
make debug

The name of the executable created is "Play".

##HOW TO RUN
To run the "Play" executable from the command line, use the following:
./Play

The following optional command line parameters are provided for variables that can be configured by the user:
* --logfile <logfile path> --> Use this to specify path and name of logfile
* --loglevel <integer log level> --> use this to specify log level of the messages that will be logged to the file
* --numdecks <integet number of decks> --> Use this to specify number of decks used during the blackjack game
* --highscores <integer number of high scores to print> --> Use this to specify the number of high scores that will be displayed
