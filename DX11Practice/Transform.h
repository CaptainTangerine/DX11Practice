#pragma once
#include "Component.h"

class UTransform : public UComponent
{
public:
	UTransform() = default;
	~UTransform() = default;
public:
	void Update(float fTimeDalta) {};
	virtual void Release() override {};
private:
	//FVector<float> Position;
};

