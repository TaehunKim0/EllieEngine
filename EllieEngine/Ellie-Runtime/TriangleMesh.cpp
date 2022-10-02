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
    // ���� ������ �����.
    // ����(Vertex) �迭.
    // �޼� ��ǥ��.

    // ���� ���� ����.
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

    // �ε��� ���� ����.
    unsigned int indices[] =
    {
        0, 1, 2
    };
    if (_IndexBuffer.Initialize(InDevice, indices, ARRAYSIZE(indices)) == false)
    {
        return false;
    }

    // ������ ���� �� ����� (�Է� ���̾ƿ�).
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    if (_InputLayout.Initialize(InDevice, layout, ARRAYSIZE(layout), InVertexShaderBuffer) == false)
    {
        return false;
    }

    // ��� ����.
    if (_TransformBuffer.Create(InDevice, XMMATRIX(0)) == false)
    {
        return false;
    }

    return true;
}