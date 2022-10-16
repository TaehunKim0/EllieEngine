#pragma once
#include "VertexShader.hpp"
#include "PixelShader.hpp"

class Engine
{
public:
	bool InitializeScene(ID3D11Device* InDevice, ID3D11DeviceContext* InContext);
	void Update(ID3D11Device* InDevice, ID3D11DeviceContext* InContext);
	void DrawScene(ID3D11Device* InDevice, ID3D11DeviceContext* InContext);

private:
	VertexShader _VertexShader;
	PixelShader _PixelShader;


};