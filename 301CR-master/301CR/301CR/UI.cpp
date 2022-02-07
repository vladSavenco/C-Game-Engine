#include "UI.h"

void UI::Update()
{
	//--------
	//Controls
	//--------

	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	 {
		 moveVec = Vector3(moveVec.x, moveVec.y, moveVec.z + 40.0);
	 }

	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	 {
		 moveVec = Vector3(moveVec.x, moveVec.y, moveVec.z - 40.0);
	 }

	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	 {
		 moveVec = Vector3(moveVec.x - 40, moveVec.y, moveVec.z);
	 }

	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	 {
		 moveVec = Vector3(moveVec.x + 40, moveVec.y, moveVec.z);
	 }

	 //---------------------
	 //POTIONS AND ABILITIES
	 //---------------------

	 //potion
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	 {
		 Event* dat = new DataEvent("Dat", 0, dPotion);
		 EQueue.push_back(dat);
	 }

	 //attack
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
	 {
		 Event* aie=new AiEvent("Aie", 0,aDie);
		 EQueue.push_back(aie);
	 }

	 //checks if there was any player input and adds it to the player
	 if (moveVec.x!=0.0|| moveVec.y != 0.0|| moveVec.z != 0.0)
	 {
		 //move player
		 Event* phys = new PhysicsEvent("Phx", pPlayerMove, moveVec);
		 EQueue.push_back(phys);

		 //play step sound
		 Event* snd = new SoundEvent("Snd", *stepSound, false, sPlay);
		 EQueue.push_back(snd);

		 moveVec = Vector3(0.0, 0.0, 0.0);
	 }

	 //------------
	 //Miscelaneous
	 //------------

	 //turn off ai
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	 {
		 Event* aie = new AiEvent("Aie", 0, aOff);
		 EQueue.push_back(aie);
	 }

	 //turn on ai
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	 {
		 Event* aie = new AiEvent("Aie", 0, aOn);
		 EQueue.push_back(aie);
	 }
}
