#include "Precompiled.h"
#include "IndexBuffer.h"

bool IndexBuffer::Initialize(ID3D11Device* device, void* data, int count)
{
    this->count = count;

    D3D11_BUFFER_DESC indexBufferDesc;
    ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
    indexBufferDesc.ByteWidth = sizeof(unsigned int) * this->count;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

    // 데이터 담기.
    D3D11_SUBRESOURCE_DATA indexBufferData;
    ZeroMemory(&indexBufferData, sizeof(indexBufferData));
    indexBufferData.pSysMem = data;

    // 인덱스 버퍼 생성.
    HRESULT result = device->CreateBuffer(
        &indexBufferDesc,
        &indexBufferData,
        _Buffer.GetAddressOf()
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"인덱스 버퍼 생성 실패", L"오류", 0);
        return false;
    }

    return true;
}

void IndexBuffer::Bind(ID3D11DeviceContext* deviceContext)
{
    deviceContext->IASetIndexBuffer(_Buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}