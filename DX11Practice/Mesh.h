#pragma once
#include "Component.h"

class UMesh : public UComponent , public IRenderable
{
public:
	UMesh() = default;
	~UMesh() = default;

public:
	template<typename T>
	void Load(ID3D11Device& Device, const T* vertices, UINT vertexCount)
	{
		NumVertices = vertexCount;
		Stride = sizeof(T);
		ByteWidth = sizeof(T) * vertexCount;

		D3D11_BUFFER_DESC vertexBufferDesc = {};
		vertexBufferDesc.ByteWidth = ByteWidth;
		vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vertexBufferSRD = { vertices };

		HRESULT hr = Device.CreateBuffer(&vertexBufferDesc, &vertexBufferSRD, &VertexBuffer);
		assert(SUCCEEDED(hr));
	}
	virtual void Release() override;

	virtual void Render(ID3D11DeviceContext& DeviceContext) override;

private:
	ID3D11Buffer* VertexBuffer = { nullptr };
	ID3D11Buffer* IndexBuffer = { nullptr };

	UINT Stride;
	UINT ByteWidth;
	UINT NumVertices;
};

