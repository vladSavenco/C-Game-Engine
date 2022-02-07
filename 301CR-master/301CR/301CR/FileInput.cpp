#include "FileInput.h"

void FileInput::WriteData()
{
	char chrData;

	ifstream dataFile;
	dataFile.open("Data/data.txt");

	while (dataFile >> chrData)
	{
		fileVec.push_back(chrData);
	}

	dataFile.close();
}

void FileInput::ReadData()
{
	for (int i = 0; i < fileVec.size(); i++)
	{
		cout << fileVec[i] << endl;
	}
}
