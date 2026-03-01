#pragma once
class IUpdatable abstract
{
public:
	virtual void Update(float fDeltaTime) = 0;
	virtual void LateUpdate(float fDeltaTime) = 0;
};


