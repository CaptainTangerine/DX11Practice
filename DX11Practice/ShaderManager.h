#pragma once
#include "ShaderTypes.h"
#include "VertexTypes.h"

class UShaderManager
{
public:
	UShaderManager() = default;
	~UShaderManager() = default;

private:
	UShaderManager(const UShaderManager& rhs) = delete;
	UShaderManager& operator=(const UShaderManager& rhs) = delete;

public:
	static UShaderManager& GetInstance()
	{
		static UShaderManager Instance;
		return Instance;
	}
	
public:
	bool  CompileShaderFile(ID3D11Device& Device, const std::wstring& Filename, EShaderType ShaderType, const D3D11_INPUT_ELEMENT_DESC Layout[], int ElemnetNum);
	const FShader* GetShader(EShaderType eType) const;
	void CleanUp();


public:
	std::unordered_map<EShaderType, FShader> Shaders;
};

