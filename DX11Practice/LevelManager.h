#pragma once
class ULevel;

class ULevelManager
{

public:
	ULevelManager();
	~ULevelManager();

public:
	 ULevel* GetCurrentLevel() const { return Level.get();  };
	void ChangeLevel(ID3D11Device& Device);
	void Release();

private:
	std::unique_ptr<ULevel> Level;
};

