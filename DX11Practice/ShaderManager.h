#pragma once
#include "ShaderTypes.h"

class UShaderManager
{
public:
	UShaderManager() = default;
	UShaderManager() = default;

public:
	bool  CompileShaderFile(ID3D11Device& Device, std::wstring& Filename, EShaderType ShaderType, const D3D11_INPUT_ELEMENT_DESC Layout[], int ElemnetNum);

	const FShader* GetShader(EShaderType eType) const;

public:
	std::unordered_map<EShaderType, FShader> Shaders;
};

