#pragma once
#include "Dx11.h"

class IndexBuffer
{
public:
	bool Initialize(ID3D11Device* device, void* data, int count);
	void Bind(ID3D11DeviceContext* deviceContext);

	int Count() { return count; }

	ID3D11Buffer* Get() { return _Buffer.Get(); }
	ID3D11Buffer** GetAddressOf() { return _Buffer.GetAddressOf(); }

private:
	int count;
	ComPtr<ID3D11Buffer> _Buffer;
};

