#include "Engine.hpp"

bool Engine::InitializeScene(ID3D11Device* InDevice, ID3D11DeviceContext* InContext)
{
    _VertexShader = VertexShader(L"..//BasicVS.hlsl", "main", "vs_5_0");
    _PixelShader = PixelShader(L"..//BasicPS.hlsl", "main", "vs_5_0");

    //1. ���̴� ������
    if (false == _VertexShader.Compile(InDevice)) return false;
    if (false == _PixelShader.Compile(InDevice)) return false;

    //2. ���̴� ������Ʈ ����
    if (false == _VertexShader.Create(InDevice)) return false;
    if (false == _PixelShader.Create(InDevice)) return false;

    //3. Mesh ���� ����, �ε��� ���� ����



    return true;
}

void Engine::Update(ID3D11Device* InDevice, ID3D11DeviceContext*InContext)
{

}

void Engine::DrawScene(ID3D11Device* InDevice, ID3D11DeviceContext *InContext)
{

}
