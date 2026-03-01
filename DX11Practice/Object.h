#pragma once
class UComponent;
class IUpdatable;
class IRenderable;

class UObject abstract
{
public:
	UObject() = default;
	~UObject() = default;

public:
	template<typename T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		T* component = new T(std::forward<Args>(args)...);
		Components.push_back(component);

		if (auto* updatable = dynamic_cast<IUpdatable*>(component))
		{
			Updatables.push_back(updatable);
		}
		if (auto* renderable = dynamic_cast<IRenderable*>(component))
		{
			Renderables.push_back(renderable);
		}

		component->Initialize(this);

		return component;
	}
public:
	virtual void Initialize(ID3D11Device& Device) = 0;
	virtual void Update(float DeltatTime);
	virtual void LateUpdate(float DeltatTime);
	virtual void Render(ID3D11DeviceContext& DeviceContext);
	virtual void Release();

private:
	std::vector<UComponent*>  Components;
	std::vector<IUpdatable*>  Updatables;
	std::vector<IRenderable*> Renderables;
};

