#pragma once
#include "Object.h"

class ULevel
{
public:
	ULevel() = default;
	~ULevel() = default;

public:
	const std::vector<std::unique_ptr<UObject>>& GetObjectList() const { return ObjectList; };

	void Initialize(ID3D11Device& Device);
	void Release();

private:
	std::vector<std::unique_ptr<UObject>> ObjectList;

};

