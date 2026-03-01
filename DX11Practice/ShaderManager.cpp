#include "pch.h"
#include "ShaderManager.h"


bool UShaderManager::CompileShaderFile(ID3D11Device& Device, std::wstring& Filename, EShaderType ShaderType, const D3D11_INPUT_ELEMENT_DESC Layout[], int ElemnetNum)
{
	FShader ShaderInfo;

	ID3DBlob* VertexShaderCSO;
	ID3DBlob* PixelShaderCSO;

	bool bCompileSuccess = true;

	D3DCompileFromFile(Filename.c_str(), nullptr, nullptr, "VS_MAIN", "vs_5_0", 0, 0, &VertexShaderCSO, nullptr);
	if (!Device.CreateVertexShader(VertexShaderCSO->GetBufferPointer(), VertexShaderCSO->GetBufferSize(), nullptr, &ShaderInfo.VS))
	{
		bCompileSuccess = false;
	}

	//레이아웃 생성
	if (!Device.CreateInputLayout(Layout, ElemnetNum, VertexShaderCSO->GetBufferPointer(), VertexShaderCSO->GetBufferSize(), &ShaderInfo.InputLayout))
	{
		bCompileSuccess = false;
	}

	D3DCompileFromFile(Filename.c_str(), nullptr, nullptr, "PS_MAIN", "ps_5_0", 0, 0, &PixelShaderCSO, nullptr);
	if (!Device.CreatePixelShader(PixelShaderCSO->GetBufferPointer(), PixelShaderCSO->GetBufferSize(), nullptr, &ShaderInfo.PS))
	{
		bCompileSuccess = false;
	}

	VertexShaderCSO->Release();
	VertexShaderCSO->Release();

	if (bCompileSuccess)
	{
		Shaders[ShaderType] = ShaderInfo;
	}

	return bCompileSuccess;
}

const FShader* UShaderManager::GetShader(EShaderType eType) const
{
	auto iter = Shaders.find(eType);
	if (iter == Shaders.end())
	{
		return nullptr;
	}

	return &iter->second;
}
