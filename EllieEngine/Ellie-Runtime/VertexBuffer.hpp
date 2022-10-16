#pragma once
#include "Dx11.hpp"

class VertexBuffer
{
public:
    bool Initialize(ID3D11Device* device, void* data, int count, int elementByteWidth);
    void Bind(ID3D11DeviceContext* deviceContext);

    int Count() { return _Count; }
    unsigned int ElementByteWidth() { return _ElementByteWidth; }

    ID3D11Buffer* Get() { return _Buffer.Get(); }
    ID3D11Buffer** GetAddressOf() { return _Buffer.GetAddressOf(); }

private:
    int _Count;                              // 정점 개수.
    unsigned int _ElementByteWidth;          // 정점 배열 원소 바이트 수.
    ComPtr<ID3D11Buffer> _Buffer;            // DX11 버퍼.
};