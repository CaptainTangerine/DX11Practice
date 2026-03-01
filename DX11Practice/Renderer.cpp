#include "pch.h"
#include "Renderer.h"
#include "Level.h"
#include "Object.h"
#include "ShaderManager.h"

URenderer::URenderer(ID3D11Device* _Device, ID3D11DeviceContext* _DeviceContext, IDXGISwapChain* _SwapChain)
	: Device(_Device), DeviceContext(_DeviceContext), SwapChain(_SwapChain)
{
}

void URenderer::Initialize()
{
	DXGI_SWAP_CHAIN_DESC SwapChainDesc = {};
	SwapChain->GetDesc(&SwapChainDesc);
	ViewportInfo = { 0.0f, 0.0f, (float)SwapChainDesc.BufferDesc.Width, (float)SwapChainDesc.BufferDesc.Height, 0.0f, 1.0f };
	
	CreateRenderTargetView();
	CreateDepthStensilView();
	CreateRasterizerState();
}

void URenderer::BeginScene()
{
	FLOAT ClearColor[4] = {0.025f, 0.025f, 0.025f, 1.0f};
	DeviceContext->ClearRenderTargetView(BackBufferRTV, ClearColor);
	DeviceContext->ClearDepthStencilView(DepthStensilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);

	DeviceContext->RSSetViewports(1, &ViewportInfo);
	DeviceContext->RSSetState(RasterizerState);
	DeviceContext->OMSetRenderTargets(1, &BackBufferRTV, DepthStensilView);

	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DeviceContext->OMSetBlendState(nullptr, nullptr, 0xffffffff);
}

void URenderer::Render(ULevel& Level)
{
	const auto& ObjectList = Level.GetObjectList();

	const auto SimplePass = UShaderManager::GetInstance().GetShader(EShaderType::Simple);
	if (SimplePass)
	{
		DeviceContext->VSSetShader(SimplePass->VS, nullptr, 0);
		DeviceContext->PSSetShader(SimplePass->PS, nullptr, 0);
		DeviceContext->IASetInputLayout(SimplePass->InputLayout);

		for (const auto& Object : ObjectList)
		{
			Object->Render(*DeviceContext);
		}
	}
}

void URenderer::EndScene()
{
	SwapChain->Present(1, 0);
}

void URenderer::Release()
{
	DeviceContext->OMSetRenderTargets(0, nullptr, nullptr);

	ReleaseRasterizerState();
	ReleaseDepthStensilView();
	ReleaseRenderTargetView();
}

void URenderer::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC RasterizerDesc = {};
	RasterizerDesc.FillMode = D3D11_FILL_SOLID;
	RasterizerDesc.CullMode = D3D11_CULL_BACK;

	Device->CreateRasterizerState(&RasterizerDesc, &RasterizerState);

}

void URenderer::ReleaseRasterizerState()
{
	if (RasterizerState)
	{
		RasterizerState->Release();
		RasterizerState = nullptr;
	}
}


void URenderer::CreateRenderTargetView()
{
	SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);

	// 렌더 타겟 뷰 생성
	D3D11_RENDER_TARGET_VIEW_DESC BackBufferRTVdesc = {};
	BackBufferRTVdesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
	BackBufferRTVdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	Device->CreateRenderTargetView(BackBuffer, &BackBufferRTVdesc, &BackBufferRTV);
}

void URenderer::ReleaseRenderTargetView() 
{
	if (BackBufferRTV)
	{
		BackBufferRTV->Release();
		BackBufferRTV = nullptr;
	}

	if (BackBuffer)
	{
		BackBuffer->Release();
		BackBuffer = nullptr;
	}

}

void URenderer::CreateDepthStensilView()
{
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width = static_cast<UINT>(ViewportInfo.Width);
	desc.Height = static_cast<UINT>(ViewportInfo.Height);
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;   // 깊이: 24bit, 스텐실: 8bit
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	
	Device->CreateTexture2D(&desc, nullptr, &DepthBuffer);

	D3D11_DEPTH_STENCIL_VIEW_DESC viewDesc = {};
	viewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	viewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	viewDesc.Texture2D.MipSlice = 0;

	Device->CreateDepthStencilView(DepthBuffer, &viewDesc, &DepthStensilView);
}

void URenderer::ReleaseDepthStensilView()
{
	if (DepthStensilView)
	{
		DepthStensilView->Release();
		DepthStensilView = nullptr;
	}

	if (DepthBuffer)
	{
		DepthBuffer->Release();
		DepthBuffer = nullptr;
	}
}
