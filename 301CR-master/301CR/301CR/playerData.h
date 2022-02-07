#pragma once

struct playerData
{
public:
    int playerHealth;

    int healthPotions;
    int potionEffect;

    int playerScore;

    std::string name;

    playerData(){}

    playerData(int helt,int heltP,int pEff,int playerS)
    {
        playerHealth = helt;
        healthPotions = heltP;
        potionEffect = pEff;
        playerScore = playerS;
    }
};