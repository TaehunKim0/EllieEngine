#include "Precompiled.hpp"
#include "VertexShader.hpp"

VertexShader::VertexShader()
    : EShader()
{
}

VertexShader::VertexShader(std::wstring filename)
    : EShader(filename)
{
    profile = "vs_5_0";
}

VertexShader::VertexShader(std::wstring filename, std::string entry, std::string profile)
    : EShader(filename, entry, profile), _VertexShader(0)
{
}

VertexShader::~VertexShader()
{
}

bool VertexShader::Compile(ID3D11Device* device)
{
    ID3DBlob* pBlobVs = nullptr; //�����ϵ� HLSL ����Ʈ �ڵ带 �����صδ� ����(VertexShader)
    ID3DBlob* pBlobPs = nullptr; //�����ϵ� HLSL ����Ʈ �ڵ带 �����صδ� ����(PixelShader)

    // VS ������
    HRESULT result = D3DX11CompileFromFile(
        filename.c_str(),
        NULL,
        NULL,
        entry.c_str(),
        profile.c_str(),
        D3D10_SHADER_ENABLE_STRICTNESS,
        0,
        nullptr,
        &pBlobVs,
        NULL,
        nullptr
    );
    if (FAILED(result)) 
    {
        MessageBox(nullptr, L"���� ���̴� ������ ����", L"����", 0); 
        return false;
    }

    HRESULT hr1 = DX11.GetDevice()->CreateVertexShader(pBlobVs->GetBufferPointer(), pBlobVs->GetBufferSize(),
        nullptr, &_VertexShader);

    if(FAILED(hr1)) 
    {
        MessageBox(nullptr, L"���� ���̴� ������Ʈ ���� ����", L"����", 0); 
        return false;
    }

    return true;
}

bool VertexShader::Create(ID3D11Device* device)
{
    // VS ����.
    HRESULT result = device->CreateVertexShader(
        shaderBuffer->GetBufferPointer(), // ���� ���� �ּ�.
        shaderBuffer->GetBufferSize(), // �󸶸�ŭ ���� ��.
        nullptr,
        _VertexShader.GetAddressOf()
    );
    if (FAILED(result)) { MessageBox(nullptr, L"���� ���̴� ���� ����", L"����", 0); }

    return true;
}

void VertexShader::Bind(ID3D11DeviceContext* deviceContext)
{
    deviceContext->VSSetShader(_VertexShader.Get(), NULL, NULL);
}
