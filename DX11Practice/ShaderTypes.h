#pragma once

enum class EShaderType { Simple };

struct FShader
{
	ID3D11VertexShader* VS;
	ID3D11PixelShader* PS;
	ID3D11InputLayout* InputLayout;
};


