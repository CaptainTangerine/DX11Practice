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
	static UShaderManager* GInstance;
	static UShaderManager& GetInstance() { return *GInstance; }
	static void CreateInstance() { GInstance = new UShaderManager(); }
	static void DestroyInstance() { delete GInstance; GInstance = nullptr; }
	
public:
	bool  CompileShaderFile(ID3D11Device& Device, const std::wstring& Filename, EShaderType ShaderType, const D3D11_INPUT_ELEMENT_DESC Layout[], int ElemnetNum);
	const FShader* GetShader(EShaderType eType) const;
	void CleanUp();


public:
	std::unordered_map<EShaderType, FShader> Shaders;
};

