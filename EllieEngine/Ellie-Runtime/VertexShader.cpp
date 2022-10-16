#include "VertexShader.hpp"
#include <d3dcompiler.h>
#include <d3dx11.h>

VertexShader::VertexShader()
    : Shader()
{
}

VertexShader::VertexShader(std::wstring filename)
    : Shader(filename)
{
    profile = "vs_5_0";
}

VertexShader::VertexShader(std::wstring filename, std::string entry, std::string profile)
    : Shader(filename, entry, profile), _VertexShader(0)
{
}

VertexShader::~VertexShader()
{
}

bool VertexShader::Compile(ID3D11Device* device)
{
    ID3DBlob* pBlobVs = nullptr; //컴파일된 HLSL 바이트 코드를 저장해두는 변수(VertexShader)

    // VS 컴파일
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
        MessageBox(nullptr, L"정점 쉐이더 컴파일 실패", L"오류", 0);
        return false;
    }

    return true;
}

bool VertexShader::Create(ID3D11Device* device)
{
    // VS 생성.
    HRESULT result = device->CreateVertexShader(
        shaderBuffer->GetBufferPointer(), // 시작 지점 주소.
        shaderBuffer->GetBufferSize(), // 얼마만큼 읽을 지.
        nullptr,
        &_VertexShader
    );
    if (FAILED(result)) { MessageBox(nullptr, L"정점 쉐이더 생성 실패", L"오류", 0); }

    return true;
}

void VertexShader::Bind(ID3D11DeviceContext* deviceContext)
{
    deviceContext->VSSetShader(_VertexShader.Get(), NULL, NULL);
}