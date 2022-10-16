#include "Precompiled.hpp"
#include "VertexBuffer.hpp"

bool VertexBuffer::Initialize(ID3D11Device* device, void* data, int count, int elementByteWidth)
{
    this->_Count = count;
    this->_ElementByteWidth = elementByteWidth;

    // 정점 버퍼 만들기.
    D3D11_BUFFER_DESC vertexBufferDesc;
    ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
    vertexBufferDesc.ByteWidth = this->_ElementByteWidth *this->_Count; // 얼마만큼 읽을까.
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // 정점 데이터 버퍼로 쓸 것이다.
    vertexBufferDesc.CPUAccessFlags = 0; // 성능을 올리기 위해 CPU가 GPU 접근할 수 있게 할까? 우리가 구분 잘해서 코딩할 수 있으면 접근하게 만들어도 됨. 0은 못 접근하게.
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

    // 데이터 담기.
    D3D11_SUBRESOURCE_DATA vertexBufferData;
    ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
    vertexBufferData.pSysMem = data;

    // 정점 버퍼 생성.
    HRESULT result = device->CreateBuffer(
        &vertexBufferDesc,
        &vertexBufferData,
        _Buffer.GetAddressOf()
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"정점 버퍼 생성 실패", L"오류", 0);
        return false;
    }

    return true;
}

void VertexBuffer::Bind(ID3D11DeviceContext* deviceContext)
{
    // Bind
    unsigned int stride = _ElementByteWidth; // 한번에 몇 개씩 읽을 지.
    unsigned int offset = 0;

    deviceContext->IASetVertexBuffers(0, 1, _Buffer.GetAddressOf(), &stride, &offset);
}