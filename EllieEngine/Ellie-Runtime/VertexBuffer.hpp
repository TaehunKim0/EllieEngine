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
    int _Count;                              // ���� ����.
    unsigned int _ElementByteWidth;          // ���� �迭 ���� ����Ʈ ��.
    ComPtr<ID3D11Buffer> _Buffer;            // DX11 ����.
};