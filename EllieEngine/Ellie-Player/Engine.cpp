#include "Engine.hpp"

bool Engine::InitializeScene(ID3D11Device* InDevice, ID3D11DeviceContext* InContext)
{
    _VertexShader = VertexShader(L"..//BasicVS.hlsl", "main", "vs_5_0");
    _PixelShader = PixelShader(L"..//BasicPS.hlsl", "main", "vs_5_0");

    //1. 셰이더 컴파일
    if (false == _VertexShader.Compile(InDevice)) return false;
    if (false == _PixelShader.Compile(InDevice)) return false;

    //2. 셰이더 오브젝트 생성
    if (false == _VertexShader.Create(InDevice)) return false;
    if (false == _PixelShader.Create(InDevice)) return false;

    //3. Mesh 정점 버퍼, 인덱스 버퍼 생성



    return true;
}

void Engine::Update(ID3D11Device* InDevice, ID3D11DeviceContext*InContext)
{

}

void Engine::DrawScene(ID3D11Device* InDevice, ID3D11DeviceContext *InContext)
{

}
