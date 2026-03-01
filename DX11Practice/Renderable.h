#pragma once
class IRenderable
{
public:
	virtual void Render(ID3D11DeviceContext& DeviceContext) = 0;
};

