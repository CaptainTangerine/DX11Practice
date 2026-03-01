#pragma once
class ULevel;

class URenderer
{
public:
	URenderer(ID3D11Device* _Device, ID3D11DeviceContext* _DeviceContext, IDXGISwapChain* _SwapChain);
	~URenderer() = default;
public:
	void Initialize();

	void BeginScene();
	void Render(ULevel& Level);
	void EndScene();

	void Release();

private:
	void CreateRasterizerState();
	void ReleaseRasterizerState();

	void CreateRenderTargetView();
	void ReleaseRenderTargetView();

	void CreateDepthStensilView();
	void ReleaseDepthStensilView();

private:
	ID3D11Device* Device = { nullptr };
	ID3D11DeviceContext* DeviceContext = { nullptr };
	IDXGISwapChain* SwapChain = { nullptr };

	ID3D11Texture2D* BackBuffer = { nullptr };
	ID3D11RenderTargetView* BackBufferRTV = { nullptr };

	ID3D11Texture2D* DepthBuffer = { nullptr };
	ID3D11DepthStencilView* DepthStensilView = { nullptr };

	ID3D11RasterizerState* RasterizerState = { nullptr };


	ID3D11Buffer* ConstantBuffer = { nullptr };
	D3D11_VIEWPORT ViewportInfo = {};

};

