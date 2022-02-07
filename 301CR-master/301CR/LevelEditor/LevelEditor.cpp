#include "LevelEditor.h"

//runs when the engine awakes
void LevelEditor::Awake()
{
	cout << "Level editor awake" << endl;
}

//function builder
LevelEditor::LevelEditor()
{
	Awake();
}

//the start function where we call and start all the other engines
void LevelEditor::Start()
{
	
}

//the update function of the game engine
void LevelEditor::Update()
{
	graphics.Update();
}

void LevelEditor::CreateMap()
{
	for (int i = 0; i < assetLoader.levelObj.size(); i++)
	{
		
	}
}
