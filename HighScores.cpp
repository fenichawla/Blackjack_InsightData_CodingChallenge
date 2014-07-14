#include "Messages.h"
#include "HighScores.h"

using namespace std;

bool sortByScore(const ScoreTableElement& lhs, 
		 const ScoreTableElement& rhs)
{
  return (lhs.score > rhs.score); 
}

void CHighScores::SetFile(const std::string& name)
{
  if (name.size() == 0)
    Filepath = DEFAULT_HS_FILE_PATH;
  else
    Filepath = name;
  return;
}

void CHighScores::SetHighScore(int tn) 
{
  TopNum = (0==tn) ? TOP_NUM : tn;
  return;
}

void CHighScores::InitializeHSTable()
{
  HSTable.clear(); // reset Vector to empty
  ifstream in_file(Filepath, ios::in);
  if(!in_file.good())
    {
      DEBUG_LOG(0,"ERROR: Can't write to High Score file: "<< Filepath);
      return; 
    }
  ScoreTableElement tableElement;
  string name;
  int score;
  while(in_file >> score >> name)
    {
      DEBUG_LOG(1, "Reading from the file: score:"<<score <<" name:"<<name);
      tableElement.name = name;
      tableElement.score = score;
      HSTable.push_back(tableElement);
    }
  sort(HSTable.begin(),HSTable.end(),sortByScore);
  in_file.close();
  return;
}

void CHighScores::WriteHSTableToFile()
{
  DEBUG_LOG(1, "Opening file "<<Filepath);
  // Open the file in out mode, truncing the previous incarnation
  ofstream out_file(Filepath, ios::out); 
  if(!out_file.good())
    {
      DEBUG_LOG(0,"ERROR: Can't write to High Score file: "<< Filepath);
      return; 
    }
  vector<ScoreTableElement>::iterator i;
  DEBUG_LOG(2, "Beginning iteration through high scores for output");
  int ctr = 0;
  for(i = HSTable.begin(); i < HSTable.end(); i++, ctr++)
    {
      if (ctr >= TopNum)
	break;
      out_file << (*i).score << " " << (*i).name << endl;
      DEBUG_LOG(4, "Written name = " << (*i).name << "  score = " << (*i).score);
    }
  out_file.close();
  return;
}

void CHighScores::AddNewScore(const string& newName, int newScore)
{
  DEBUG_LOG(1, "Opening file "<<Filepath);
  ofstream out_file(Filepath, ios::app);

  if(!out_file.good())
    {
      DEBUG_LOG(0, "ERROR: Can't open High Score file "<<Filepath);
      return; 
    }
  out_file << newScore << " " << newName << endl;
  out_file.close();
  DEBUG_LOG(0, "New score added");
}

void CHighScores::DisplayHighScores()
{
  InitializeHSTable(); // HSTable is sorted
  // Print top players
  vector<ScoreTableElement>::iterator i;
  int ctr = 0;
  PrintHighScoreHeader();
  for (i = HSTable.begin(); i < HSTable.end(); i++, ctr++)
    {
      if (ctr >= TopNum) 
	break;
      PrintScoreRow(ctr+1, (*i).name, (*i).score);
    }
  WriteHSTableToFile();
  return;
}
