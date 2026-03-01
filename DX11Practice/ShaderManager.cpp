#include "pch.h"
#include "ShaderManager.h"


bool UShaderManager::CompileShaderFile(ID3D11Device& Device, const std::wstring& Filename, EShaderType ShaderType, const D3D11_INPUT_ELEMENT_DESC Layout[], int ElementNum)
{
	FShader ShaderInfo = {};

	ID3DBlob* VertexShaderCSO = nullptr;
	ID3DBlob* PixelShaderCSO = nullptr;
	ID3DBlob* ErrorBlob = nullptr;

	// Vertex Shader 컴파일
	HRESULT hr = D3DCompileFromFile(Filename.c_str(), nullptr, nullptr, "VS_MAIN", "vs_5_0", 0, 0, &VertexShaderCSO, &ErrorBlob);
	if (ErrorBlob) { ErrorBlob->Release(); ErrorBlob = nullptr; }
	if (FAILED(hr)) return false;

	hr = Device.CreateVertexShader(VertexShaderCSO->GetBufferPointer(), VertexShaderCSO->GetBufferSize(), nullptr, &ShaderInfo.VS);
	if (FAILED(hr)) { VertexShaderCSO->Release(); return false; }

	// 레이아웃 생성
	hr = Device.CreateInputLayout(Layout, ElementNum, VertexShaderCSO->GetBufferPointer(), VertexShaderCSO->GetBufferSize(), &ShaderInfo.InputLayout);
	VertexShaderCSO->Release();
	if (FAILED(hr)) { ShaderInfo.VS->Release(); return false; }

	// Pixel Shader 컴파일
	hr = D3DCompileFromFile(Filename.c_str(), nullptr, nullptr, "PS_MAIN", "ps_5_0", 0, 0, &PixelShaderCSO, &ErrorBlob);
	if (ErrorBlob) { ErrorBlob->Release(); ErrorBlob = nullptr; }
	if (FAILED(hr)) { ShaderInfo.VS->Release(); ShaderInfo.InputLayout->Release(); return false; }

	hr = Device.CreatePixelShader(PixelShaderCSO->GetBufferPointer(), PixelShaderCSO->GetBufferSize(), nullptr, &ShaderInfo.PS);
	PixelShaderCSO->Release();
	if (FAILED(hr)) { ShaderInfo.VS->Release(); ShaderInfo.InputLayout->Release(); return false; }

	Shaders[ShaderType] = ShaderInfo;
	return true;
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

void UShaderManager::CleanUp()
{
	for (auto& pair : Shaders) {
		if (pair.second.VS)          pair.second.VS->Release();
		if (pair.second.PS)          pair.second.PS->Release();
		if (pair.second.InputLayout) pair.second.InputLayout->Release();
	}
	Shaders.clear();
}
