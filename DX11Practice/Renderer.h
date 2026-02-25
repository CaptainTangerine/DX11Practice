#pragma once
class URenderer
{
public:
	URenderer() = default;
	~URenderer() = default;

public:

private:
	ID3D11DepthStencilView* DepthStensilView = { nullptr };

};

