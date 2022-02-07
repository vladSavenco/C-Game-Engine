#include "GameData.h"

GameData::GameData()
{

}

//update function
void GameData::Update()
{
	if (pD->playerHealth < 0)
	{
		gameEnd();
	}
}

//function to write data to console
void GameData::coutData()
{
	cout << "Player Health : " << pD->playerHealth << endl;
	cout << "Potions Left : " << pD->healthPotions << endl;
	cout << "Score : " << pD->playerScore << endl;
}

//function to write out the score
void GameData::coutScore()
{
	for (int i = 0; i < 5; i++)
	{
		cout << score[i].name << endl;
		cout << score[i].score << endl;
	}
}

//start
void GameData::Start()
{
	cout << "please input name:" << endl;
	cin >> pD->name;
}

//function that checks if the new score is top 5 and will replace it in the top5
void GameData::checkNewScore()
{
	for (int i = 4; i >=0; i--)
	{
		if (score[i].score <= pD->playerScore)
		{
			score[i].score = pD->playerScore;
			score[i].name = pD->name;

			break;
		}
	}
}

//function that saves data to the "data base"
void GameData::saveDataToFile()
{
	ofstream scoreFile;

	scoreFile.open("Data/score.lua", std::ofstream::out | std::ofstream::trunc);

	scoreFile << "score={" << endl;

	for (int i = 0; i < 5; i++)
	{
		scoreFile << "sc" << i << "={" << endl;
		scoreFile << "name=" << "\"" << score[i].name << "\"," << endl;
		scoreFile << "sc=" << score[i].score << endl;
		if (i == 4)
		{
			scoreFile << "}" << endl;
		}
		else
		{
			scoreFile << "}," << endl;
		}
	}

	scoreFile << "}" << endl;

	scoreFile.close();
}

//couts an entire website to html
void GameData::coutAnEntireHtmlWebsiteToFile()
{
	ofstream htmlFile;

	htmlFile.open("Data/HighScore.html", std::ofstream::out | std::ofstream::trunc);

	htmlFile << "<html>" << endl;
	htmlFile << "<head>" << endl;
	htmlFile << "<h1>HIGH SCORE</h1>" << endl;
	htmlFile << "</head>" << endl;

	htmlFile << "<body>" << endl;

	for (int i = 4; i >= 0; i--)
	{
		htmlFile << "<p>" << score[i].name << "  " << score[i].score << "</p>" << endl;
	}

	htmlFile << "</body>" << endl;
	htmlFile << "</html>" << endl;

	htmlFile.close();
}

//function that triggers the end of the game
void GameData::gameEnd()
{
	checkNewScore();
	saveDataToFile();
	coutAnEntireHtmlWebsiteToFile();

	system("start Data/HighScore.html");

	Event* stp = new Event("Stp");
	EQueue.push_back(stp);
}

//checking for data events
void GameData::CheckEvent(DataEvent* ev)
{
	if (ev->eSpec == dHealth)
	{
		pD->playerHealth = pD->playerHealth - ev->ammount;

		//system("CLS");
		coutData();
	}

	if (ev->eSpec == dPotion)
	{
		if (pD->healthPotions > 0)
		{
			pD->playerHealth = pD->playerHealth + pD->potionEffect;

			pD->healthPotions = pD->healthPotions - 1;
		}
		else
		{
			//tell player he doesnt have enough potions
		}

		//system("CLS");
		coutData();
	}

	if (ev->eSpec == dScore)
	{
		pD->playerScore = pD->playerScore + 1;

		//system("CLS");
		coutData();
	}
}
