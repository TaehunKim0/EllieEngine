#pragma once

#include "Singleton.hpp"
#include "Matrix.hpp"
#define DX11 Dx11::GetInstance()

class Dx11 : public Singleton<Dx11>
{
public:
	Dx11();
	~Dx11();

	//Init
	bool Init(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen,
		float screenDepth, float screenNear);
	bool Resize();
	bool Initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen, float screenDepth, float screenNear);


	//Render
	void BeginScene(float red, float green, float blue, float alpha);
	void EndScene();

	//Release
	void Release();

	ID3D11Device* GetDevice() {
		return _Device;
	}
	ID3D11DeviceContext* GetDeviceContext() {
		return _ImmediateContext;
	}
	const HWND GetHWND() {
		return _Hwnd;
	}

	void GetWorldMatrix(Mat4x4 outWorldMatrix) {
		outWorldMatrix = _WorldMatrix;
	}
	void GetProjectionMatrix(Mat4x4 outProjectionMatrix) {
		outProjectionMatrix = _ProjectionMatrix;
	}

private:
	bool _Vsync_Enabled;
	int _VideoCardMemory;
	char _VideoCardDescription[128];
	UINT _4xMsaaQuality;
	bool _EnableMsaa;
	int _ScreenWidth;
	int _ScreenHeight;

private:
	HWND _Hwnd;

	IDXGISwapChain* _SwapChain;
	ID3D11Device* _Device;
	ID3D11DeviceContext* _ImmediateContext;

	ID3D11RenderTargetView* _RenderTargetView;
	ID3D11Texture2D* _DepthStencilBuffer;

	ID3D11DepthStencilState* _DepthStencilState;
	ID3D11DepthStencilView* _DepthStencilView;
	ID3D11DepthStencilState* _DepthDisabledStencilState;

	ID3D11RasterizerState* _RasterState;
	ID3D11RasterizerState* _RasterStateNoCulling;

	Mat4x4 _ProjectionMatrix;
	Mat4x4 _WorldMatrix;
	Mat4x4 _OrthoMatrix;

	D3D11_VIEWPORT _Viewport;
};