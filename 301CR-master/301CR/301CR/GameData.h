#pragma once
#include "Subsystem.h"

#include <fstream>

#include <windows.h>

class GameData :
    public Subsystem
{
public:
    playerData* pD;

    HighScore score[5];

    GameData();

    void Update();

    //function to cout data such as health,score and potions
    void coutData();

    //function that couts the current highscores
    void coutScore();

    void Start();

    void checkNewScore();

    //this is a function that saves the higscores to a "data base"
    void saveDataToFile();

    //it does what it says, I have attempted the google drive api, but that just made me really sad as the c++ 
    //implementations was not working properly and the other way to do it was java.
    void coutAnEntireHtmlWebsiteToFile();

    void gameEnd();

    void CheckEvent(DataEvent* ev);
};

