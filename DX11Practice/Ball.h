#pragma once
#include "Object.h"

class UBall : public UObject
{
public:
	UBall()  = default;
	~UBall() = default;

public:
	// UObject을(를) 통해 상속됨
	virtual void Initialize(ID3D11Device& Device) override;

};

