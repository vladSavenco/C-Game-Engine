#include "Sounds.h"

void Sounds::Start()
{
	engine = irrklang::createIrrKlangDevice();

	if (engine == NULL)
	{
		cout << "Error in creating sound engine" << endl;
	}
}

void Sounds::CheckEvent(SoundEvent* ev)
{
	if (ev->eSpec == sPlay)
	{
		playSound(ev->sName, ev->isLoop);
	}
}

void Sounds::playSound(std::string name,bool loop)
{
	engine->play2D(name.c_str(), loop);
}
