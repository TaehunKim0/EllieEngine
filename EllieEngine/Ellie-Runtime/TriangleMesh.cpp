#include "Precompiled.h"
#include "TriangleMesh.h"

TriangleMesh::TriangleMesh()
{
}

TriangleMesh::~TriangleMesh()
{
}

bool TriangleMesh::InitializeBuffers(ID3D11Device* InDevice, ID3DBlob* InVertexShaderBuffer)
{
    // 정점 데이터 만들기.
    // 정점(Vertex) 배열.
    // 왼손 좌표계.

    // 정점 버퍼 생성.
    Vertex vertices[] =
    {
        Vertex(0.0f, 0.5f, 0.5f),
        Vertex(0.5f, -0.5f, 0.5f),
        Vertex(-0.5f, -0.5f, 0.5f)
    };
    if (_VertexBuffer.Initialize(InDevice, vertices, ARRAYSIZE(vertices), sizeof(Vertex)) == false)
    {
        return false;
    }

    // 인덱스 버퍼 생성.
    unsigned int indices[] =
    {
        0, 1, 2
    };
    if (_IndexBuffer.Initialize(InDevice, indices, ARRAYSIZE(indices)) == false)
    {
        return false;
    }

    // 정점에 대한 명세 만들기 (입력 레이아웃).
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    if (_InputLayout.Initialize(InDevice, layout, ARRAYSIZE(layout), InVertexShaderBuffer) == false)
    {
        return false;
    }

    // 상수 버퍼.
    if (_TransformBuffer.Create(InDevice, XMMATRIX(0)) == false)
    {
        return false;
    }

    return true;
}