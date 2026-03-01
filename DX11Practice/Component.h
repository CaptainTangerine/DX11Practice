#pragma once
#include "Updatable.h"
#include "Renderable.h"

class UObject;

class UComponent
{
public:
	void Initialize(UObject* onwer);
	virtual void Release() = 0;

public:
	const UObject* GetOwner() const { return Onwer; };

private:
	UObject* Onwer;

};

