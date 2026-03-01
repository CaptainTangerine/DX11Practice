#include "pch.h"
#include "Level.h"
#include "Object.h"
#include "Ball.h"

void ULevel::Initialize(ID3D11Device& Device)
{
	//오브젝트 생성
	std::unique_ptr<UObject> SimpleObject = std::make_unique<UBall>();
	SimpleObject->Initialize(Device);

	ObjectList.push_back(std::move(SimpleObject));

}

void ULevel::Release()
{
	for (const auto& Object : ObjectList)
	{
		Object->Release();
	}
}
