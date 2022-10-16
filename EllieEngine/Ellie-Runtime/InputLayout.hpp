#pragma once
#include "Dx11.hpp"

class InputLayout
{
public:
	bool Initialize(ID3D11Device* device, D3D11_INPUT_ELEMENT_DESC* layout, int count, ID3DBlob* vertexShaderBuffer);
	void Bind(ID3D11DeviceContext* deviceContext);

	ID3D11InputLayout* Get() { return _InputLayout.Get(); }
	ID3D11InputLayout** GetAddressOf() { return _InputLayout.GetAddressOf(); }

private:
	ComPtr<ID3D11InputLayout> _InputLayout;
};