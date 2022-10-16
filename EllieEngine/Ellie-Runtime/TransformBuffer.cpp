#include "Precompiled.hpp"
#include "TransformBuffer.hpp"

bool TransformBuffer::Create(ID3D11Device* device, Mat4x4 InMatrix)
{
    _TransformMatrix = InMatrix;

    // ��� ����.
    D3D11_BUFFER_DESC transformBufferDesc;
    ZeroMemory(&transformBufferDesc, sizeof(transformBufferDesc));
    transformBufferDesc.ByteWidth = sizeof(_TransformMatrix);
    transformBufferDesc.CPUAccessFlags = 0;
    transformBufferDesc.MiscFlags = 0;
    transformBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    transformBufferDesc.Usage = D3D11_USAGE_DEFAULT;

    // ������ ���.
    D3D11_SUBRESOURCE_DATA transformBufferData;
    ZeroMemory(&transformBufferData, sizeof(transformBufferData));
    transformBufferData.pSysMem = &_TransformMatrix;

    // ���� ����.
    HRESULT result = device->CreateBuffer(
        &transformBufferDesc,
        &transformBufferData,
        _ConstantBuffer.GetAddressOf()
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"��� ���� ���� ����", L"����", 0);
        return false;
    }

    return true;
}

void TransformBuffer::Bind(ID3D11DeviceContext* deviceContext)
{
    // ��� ������ ������Ʈ.
    deviceContext->UpdateSubresource(_ConstantBuffer.Get(), 0, NULL, &_TransformMatrix, 0, 0);

    // ��� �����Ͱ� ��� ���� ���ε�. (����.)
    deviceContext->VSSetConstantBuffers(0, 1, _ConstantBuffer.GetAddressOf());
}