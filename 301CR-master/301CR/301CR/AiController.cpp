#include "AiController.h"

AiController::AiController()
{
	
}

//controlls all the ai movement
void AiController::AiMovement()
{
	if (aiOn == true)
	{
		for (int i = 0; i < enemies->size(); i++)
		{
			for (int j = 0; j < eBehav.size(); j++)
			{
				if ((*enemies)[i].aiId == eBehav[j].enemyId)
				{
					if (eBehav[j].detectRange > vladVector.Distance((*enemies)[i].objPosition, player->objPosition) && 30<vladVector.Distance((*enemies)[i].objPosition, player->objPosition))
					{
						Vector3 moveVec;

						vladVector.direction(player->objPosition, (*enemies)[i].objPosition, moveVec);

						moveVec = Vector3(moveVec.x * 1, moveVec.y * 1, moveVec.z * 1);

						Event* phys = new PhysicsEvent((*enemies)[i].objId, "Phx", pEnemyMove, moveVec);
						EQueue.push_back(phys);
					}
				}
			}
		}
	}
}

//checks for ai events
void AiController::CheckEvent(AiEvent* ev)
{
	if (ev->eSpec == aAttack)
	{
		resolveDammageEvent(ev);
	}

	if (ev->eSpec == aDie)
	{
		attackEvent();
	}
	if (ev->eSpec == aOff)
	{
			aiOn = false;
	}
	if (ev->eSpec == aOn)
	{
		aiOn = true;
	}
}

//resolve dammage event from ai to player
void AiController::resolveDammageEvent(AiEvent* ev)
{
	for (int i = 0; i < enemies->size(); i++)
	{
		if ((*enemies)[i].objId == ev->iD)
		{
			for (int j = 0; j < eBehav.size(); j++)
			{
				if ((*enemies)[i].aiId == eBehav[j].enemyId)
				{
					Event* dat = new DataEvent("Dat", eBehav[j].dammage, dHealth);
					EQueue.push_back(dat);
				}
			}
		}
	}
}

//player attacks ai event, it is based on distance as physx is a bit weird
void AiController::attackEvent()
{
	for (int i = 0; i < enemies->size(); i++)
	{
		Vector3 moveVec;

		vladVector.direction((*enemies)[i].objPosition, player->objPosition, moveVec);

		moveVec = Vector3(moveVec.x * 1000, 0, moveVec.z * 1000);

		if (vladVector.Distance((*enemies)[i].objPosition, player->objPosition)<50.0f)
		{
			resolveDeathEvent((*enemies)[i].objId,moveVec);

			Event* dat = new DataEvent("Dat", 0, dScore);
			EQueue.push_back(dat);
		}
	}
}

//resolve ai death (pushes ai with fus ro dah)
void AiController::resolveDeathEvent(int id,Vector3 moveVec)
{
	//delete the physx instance of enemy
	Event* phys = new PhysicsEvent(id,"Phx", pEnemyMove,moveVec);
	EQueue.push_back(phys);
}

//updates ai...mostly movement
void AiController::Update()
{
	AiMovement();
}
