#ifndef __HIGHSCORES_H__
#define __HIGHSCORES_H__

#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Logger.h"

#define DEFAULT_HS_FILE_PATH "/tmp/BlackJackHighScores.txt"
#define TOP_NUM 5

using namespace std;

struct ScoreTableElement
{
  string name;
  int score;
};

class CHighScores
{
 private:
  string Filepath;
  vector <ScoreTableElement> HSTable;

  void InitializeHSTable();
  void WriteHSTableToFile();
  int TopNum;

 public:
  CHighScores(int);

  void DisplayHighScores();
  void AddNewScore(string, int);
};


#endif
