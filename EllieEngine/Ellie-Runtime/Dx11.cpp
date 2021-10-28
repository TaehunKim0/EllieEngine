#include "Precompiled.h"

Dx11::Dx11() : m_Device(0), m_ImmediateContext(0), m_DepthStencilView(0), m_DepthDisabledStencilState(0), m_DepthStencilBuffer(0), m_DepthStencilState(0)
, m_RasterState(0), m_RasterStateNoCulling(0), m_RenderTargetView(0),m_SwapChain(0),m_VideoCardMemory(0)
, m_Vsync_Enabled(0) , m_EnableMsaa(0), m_4xMsaaQuality(0),m_ScreenHeight(0), m_ScreenWidth(0)
{
}

bool Dx11::Init(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen, float screenDepth, float screenNear)
{
    m_ScreenWidth = screenWidth;
    m_ScreenHeight = screenHeight;

	//*1. D3D 디바이스 설정*//
	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr = D3D11CreateDevice(
		0,                 // default adapter
		D3D_DRIVER_TYPE_HARDWARE,
		0,                 // no software device
		0,
		0, 0,              // default feature level array
		D3D11_SDK_VERSION,
		&this->m_Device,
		&featureLevel,
		&this->m_ImmediateContext);	

	if (FAILED(hr))
	{
		MessageBox(0, _T("D3D11 Create Device Failed."), 0, 0);
		return false;
	}

	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, _T("Direct3D Feature Level 11 unsupported."), 0, 0);
		return false;
	}

	//*2. 4X MSAA 품질 수준 지원 점검(안티엘리어싱)*//
	m_Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &this->m_4xMsaaQuality);
	assert(m_4xMsaaQuality > 0);

	//*3. 후면 버퍼 설정*//
	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = screenWidth;
	sd.BufferDesc.Height = screenHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	if (m_EnableMsaa == true)
	{
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}
	else
	{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hwnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	//*4. 후면 버퍼 생성*//
	IDXGIDevice* dxgiDevice = 0;
	m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
	IDXGIAdapter* dxgiAdapter = 0;
	dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);
	IDXGIFactory* dxgiFactory = 0;
	dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

	HRESULT hrr = dxgiFactory->CreateSwapChain(m_Device, &sd, &m_SwapChain);
	if (FAILED(hrr))
	{
		MessageBox(0, _T("D3D11 Create SwapChain Failed."), 0, 0);
		return false;
	}

	SAFE_RELEASE(dxgiDevice);
	SAFE_RELEASE(dxgiAdapter);
	SAFE_RELEASE(dxgiFactory);

	if (this->Resize() == false)
		return false;

	return true;
}

bool Dx11::Resize()
{
    assert(m_ImmediateContext);
    assert(m_Device);
    assert(m_SwapChain);

	//*5. 렌더 대상 뷰 설정*//
    m_SwapChain->ResizeBuffers(1, m_ScreenWidth, m_ScreenHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
    ID3D11Texture2D* backBuffer;

    m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));

    m_Device->CreateRenderTargetView(backBuffer, 0, &m_RenderTargetView);

    SAFE_RELEASE(backBuffer);

	//*6. 깊이 - 스텐실 버퍼와 뷰 생성*//
    D3D11_TEXTURE2D_DESC depthStencilDesc;

    depthStencilDesc.Width = m_ScreenWidth;
    depthStencilDesc.Height = m_ScreenHeight;
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.ArraySize = 1;
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

    // Use 4X MSAA? --must match swap chain MSAA values.
    // 4X MSAA를 사용하는가? --반드시 교환 사슬의 MSAA 설정과 일치해야 함.
    if (m_EnableMsaa)
    {
        depthStencilDesc.SampleDesc.Count = 4;
        depthStencilDesc.SampleDesc.Quality = m_4xMsaaQuality - 1;
    }
    else
    {
        depthStencilDesc.SampleDesc.Count = 1;
        depthStencilDesc.SampleDesc.Quality = 0;
    }

    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilDesc.CPUAccessFlags = 0;
    depthStencilDesc.MiscFlags = 0;

    m_Device->CreateTexture2D(&depthStencilDesc, 0, &m_DepthStencilBuffer);       

    m_Device->CreateDepthStencilView(m_DepthStencilBuffer, 0, &m_DepthStencilView);

	//*7. 뷰들을 출력 병합기 단계에 묶기*//
    m_ImmediateContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

	//*8. 뷰포트 설정*//
    m_Viewport.TopLeftX = 0;
	m_Viewport.TopLeftY = 0;
	m_Viewport.Width = static_cast<float>(m_ScreenWidth);
	m_Viewport.Height = static_cast<float>(m_ScreenHeight);
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;

    m_ImmediateContext->RSSetViewports(1, &m_Viewport);

	return true;
}

int Dx11::Rendering()
{
	BeginScene(0.f,0.f,1.f,1.f);

	//Render

	EndScene();
	return 0;
}

void Dx11::BeginScene(float red, float green, float blue, float alpha)
{
	float color[4];

	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;

	m_ImmediateContext->ClearRenderTargetView(m_RenderTargetView, color);
	m_ImmediateContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Dx11::EndScene()
{
	m_SwapChain->Present(1, 0);
}
