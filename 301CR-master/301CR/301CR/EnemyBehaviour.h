#pragma once
#include <irrlicht.h>

struct EnemyBehaviour
{
public:
	int enemyId;

	float detectRange;
	float attackRange;

	int dammage;

	EnemyBehaviour() 
	{

	}

	EnemyBehaviour(int eId,float dRange,int dmg)
	{
		enemyId = eId;
		detectRange = dRange;
		dammage = dmg;
	}
};