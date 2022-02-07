#pragma once
#include "Subsystem.h"

class AiController :
    public Subsystem
{
public:
    GameObject* player;

    std::vector<GameObject>* enemies;

    std::vector<EnemyBehaviour> eBehav;

    bool aiOn = true;

    AiController();

    //make the ai move towards the player
    void AiMovement();

    void CheckEvent(AiEvent* ev);

    void resolveDammageEvent(AiEvent* ev);

    void attackEvent();

    void resolveDeathEvent(int id, Vector3 moveVec);

    void Update();
};

