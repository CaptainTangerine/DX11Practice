#include "pch.h"
#include "LevelManager.h"
#include "Level.h"

ULevelManager::ULevelManager()
{
}

ULevelManager::~ULevelManager()
{
}

void ULevelManager::ChangeLevel(ID3D11Device& Device)
{
	if (Level)
	{
		Level->Release(); 
		Level.reset();
	}
	Level = std::make_unique<ULevel>();
	Level->Initialize(Device);
}

void ULevelManager::Release()
{
	if (Level)
	{
		Level->Release();
	}
}
