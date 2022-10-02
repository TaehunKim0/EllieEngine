#include "Precompiled.h"
#include "InputLayout.h"

bool InputLayout::Initialize(ID3D11Device* device, D3D11_INPUT_ELEMENT_DESC* layout, int count, ID3DBlob* vertexShaderBuffer)
{
    // �Է� ���̾ƿ� ����.
    HRESULT result = device->CreateInputLayout(
        layout,
        count,
        vertexShaderBuffer->GetBufferPointer(),
        vertexShaderBuffer->GetBufferSize(),
        _InputLayout.GetAddressOf()
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"�Է� ���̾ƿ� ���� ����", L"����", 0);
        return false;
    }

    return true;
}

void InputLayout::Bind(ID3D11DeviceContext* deviceContext)
{
    deviceContext->IASetInputLayout(_InputLayout.Get());
}
