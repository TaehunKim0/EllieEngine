#include "PixelShader.hpp"
#include <D3DX11.h>

PixelShader::PixelShader()
    : Shader()
{
}

PixelShader::PixelShader(std::wstring filename)
    : Shader(filename)
{
    profile = "ps_5_0";
}

PixelShader::PixelShader(std::wstring filename, std::string entry, std::string profile)
    : Shader(filename, entry, profile), _PixelShader(0)
{
}

PixelShader::~PixelShader()
{
}

bool PixelShader::Compile(ID3D11Device* device)
{
    ID3DBlob* pBlobPs = nullptr; //�����ϵ� HLSL ����Ʈ �ڵ带 �����صδ� ����(PixelShader)

    // PS ������
    HRESULT result = D3DX11CompileFromFile(
        filename.c_str(),
        NULL,
        NULL,
        entry.c_str(),
        profile.c_str(),
        D3D10_SHADER_ENABLE_STRICTNESS,
        0,
        nullptr,
        &pBlobPs,
        NULL,
        nullptr
    );

    if (FAILED(result))
    {
        MessageBox(nullptr, L"�ȼ� ���̴� ������ ����", L"����", 0);
        return false;
    }

    return true;
}

bool PixelShader::Create(ID3D11Device* device)
{
    // PS ����.
    HRESULT result = device->CreatePixelShader(
        shaderBuffer->GetBufferPointer(), // ���� ���� �ּ�.
        shaderBuffer->GetBufferSize(), // �󸶸�ŭ ���� ��.
        nullptr,
        &_PixelShader
    );
    if (FAILED(result))
    {
        MessageBox(nullptr, L"�ȼ� ���̴� ���� ����", L"����", 0);
        return false;
    }

    return true;
}

void PixelShader::Bind(ID3D11DeviceContext* deviceContext)
{
    deviceContext->PSSetShader(_PixelShader.Get(), NULL, NULL);
}