#include "Precompiled.h"
#include "PixelShader.h"

PixelShader::PixelShader()
    : EShader()
{
}

PixelShader::PixelShader(std::wstring filename)
    : EShader(filename)
{
    profile = "ps_5_0";
}

PixelShader::PixelShader(std::wstring filename, std::string entry, std::string profile)
    : EShader(filename, entry, profile), _PixelShader(0)
{
}

PixelShader::~PixelShader()
{
}

bool PixelShader::Compile(ID3D11Device* device)
{
    ID3DBlob* pBlobVs = nullptr; //�����ϵ� HLSL ����Ʈ �ڵ带 �����صδ� ����(VertexShader)
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

    HRESULT hr2 = DX11.GetDevice()->CreatePixelShader(pBlobPs->GetBufferPointer(), pBlobPs->GetBufferSize(),
        nullptr, &_PixelShader);

    if (FAILED(hr2)) 
    {
        MessageBox(nullptr, L"�ȼ� ���̴� ������Ʈ ���� ����", L"����", 0);
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
        _PixelShader.GetAddressOf()
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

bool PixelShader::CreateSamplerState(ID3D11Device* device)
{
    D3D11_SAMPLER_DESC samplerDesc;
    ZeroMemory(&samplerDesc, sizeof(samplerDesc));
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    // ���÷� ������Ʈ ����.
    HRESULT result = device->CreateSamplerState(&samplerDesc, _SamplerState.GetAddressOf());
    if (FAILED(result))
    {
        MessageBox(nullptr, L"���÷� ������Ʈ ���� ����", L"����", 0);
        return false;
    }

    return true;
}

void PixelShader::BindSamplerState(ID3D11DeviceContext* deviceContext)
{
    deviceContext->PSSetSamplers(0, 1, _SamplerState.GetAddressOf());
}

bool PixelShader::LoadTexture(ID3D11Device* device, std::wstring filename)
{
 /*   ETexture texture;
    texture.filename = filename;
    if (texture.LoadTextureFromFile(device) == false)
    {
        return false;
    }
    _Textures.push_back(texture);

    return true;*/
}

void PixelShader::BindTextures(ID3D11DeviceContext* deviceContext)
{
 /*   for (int ix = 0; ix < textures.size(); ++ix)
    {
        deviceContext->PSSetShaderResources(
            ix,
            1,
            textures[ix].textureResource.GetAddressOf()
        );
    }*/
}
