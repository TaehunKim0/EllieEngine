#include "Precompiled.h"
#include "InputLayout.h"

bool InputLayout::Initialize(ID3D11Device* device, D3D11_INPUT_ELEMENT_DESC* layout, int count, ID3DBlob* vertexShaderBuffer)
{
    // 입력 레이아웃 설정.
    HRESULT result = device->CreateInputLayout(
        layout,
        count,
        vertexShaderBuffer->GetBufferPointer(),
        vertexShaderBuffer->GetBufferSize(),
        _InputLayout.GetAddressOf()
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"입력 레이아웃 생성 실패", L"오류", 0);
        return false;
    }

    return true;
}

void InputLayout::Bind(ID3D11DeviceContext* deviceContext)
{
    deviceContext->IASetInputLayout(_InputLayout.Get());
}
