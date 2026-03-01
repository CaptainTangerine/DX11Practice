#include "pch.h"
#include "Mesh.h"

void UMesh::Release()
{
	if (VertexBuffer)
	{
		VertexBuffer->Release();
		VertexBuffer = nullptr;
	}

	if (IndexBuffer)
	{
		IndexBuffer->Release();
		IndexBuffer = nullptr;
	}
}

void UMesh::Render(ID3D11DeviceContext& DeviceContext)
{
	UINT offset = 0;
	DeviceContext.IASetVertexBuffers(0, 1, &VertexBuffer, &Stride, &offset);
	DeviceContext.Draw(NumVertices, 0);
}
