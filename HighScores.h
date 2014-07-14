#ifndef __HIGHSCORES_H__
#define __HIGHSCORES_H__

#include <iostream>
#include <string>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Logger.h"

#define DEFAULT_HS_FILE "/tmp/BlackJackHighScores.txt"
#define TOP_NUM 5

struct ScoreTableElement
{
  std::string name;
  int score;
};

class CHighScores
{
 private:
  std::vector <ScoreTableElement> HSTable;

  void InitializeHSTable();
  void WriteHSTableToFile();
  int TopNum;

 public:
  void DisplayHighScores();
  void AddNewScore(const std::string&, int);
  void SetHighScore(int);
};


#endif
