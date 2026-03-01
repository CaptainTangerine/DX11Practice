#include "pch.h"
#include "Object.h"

#include "Component.h"
#include "Updatable.h"
#include "Renderable.h"

void UObject::Update(float DeltatTime)
{
	for (auto Component : Updatables)
	{
		Component->Update(DeltatTime);
	}
}

void UObject::LateUpdate(float DeltatTime)
{
	for (auto Component : Updatables)
	{
		Component->LateUpdate(DeltatTime);
	}
}

void UObject::Render(ID3D11DeviceContext& DeviceContext)
{
	for (auto Component : Renderables)
	{
		Component->Render(DeviceContext);
	}
}

void UObject::Release()
{
	for (auto Component : Components)
	{
		Component->Release();
		delete Component;
	}

	Components.clear();
	Updatables.clear();
	Renderables.clear();

}
