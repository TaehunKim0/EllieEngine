#include "Precompiled.h"
#include "SpriteRendererComponent.h"

ESpriteRendererComponent::ESpriteRendererComponent()
{

}

ESpriteRendererComponent::~ESpriteRendererComponent()
{

}

bool ESpriteRendererComponent::Init()
{
    bool result;

    //����, �ε��� ���� ����
    result = InitializeBuffer(); 
    if (false == result) return false;

    //���̴� ������ �� ���̴� ������Ʈ ����, ��ǲ ���̾ƿ� ����
    result = InitializeShader(TEXT("ColorVS.hlsl"), TEXT("ColorPS.hlsl")); 
    if (false == result) return false;

    return true;
}

void ESpriteRendererComponent::Tick()
{
    Render();
}

void ESpriteRendererComponent::Excute()
{
    SAFE_RELEASE(m_VertexBuffer);
    SAFE_RELEASE(m_IndexBuffer);
    SAFE_RELEASE(m_VertexShader);
    SAFE_RELEASE(m_PixelShader);
    SAFE_RELEASE(m_InputLayout);
    SAFE_RELEASE(m_MatrixBuffer);
}

void ESpriteRendererComponent::Destroy()
{

}

void ESpriteRendererComponent::SetSprite(ESprite* sprite)
{
    m_Sprite = sprite;
}

void ESpriteRendererComponent::Render()
{
    Mat4x4 world, view, projection;
    m_Sprite->GetMatrix(world, view, projection);

    RenderBuffer();
    SetShaderParameters(world, view, projection, m_Sprite->GetTexture());
    RenderShader();
}

void ESpriteRendererComponent::RenderShader()
{
    //����, �ȼ� ���̴��� �����ϰ� �ﰢ���� �׸��ϴ�.
    DX11.GetDeviceContext()->IASetInputLayout(m_InputLayout);
    DX11.GetDeviceContext()->VSSetShader(m_VertexShader, nullptr, 0);
    DX11.GetDeviceContext()->PSSetShader(m_PixelShader, nullptr, 0);
    DX11.GetDeviceContext()->DrawIndexed(m_IndexCount, 0, 0);
}

void ESpriteRendererComponent::RenderBuffer()
{
    //���� ���ۿ� �ε��� ���۸� ���������ο� �־� �׸� �غ� �մϴ�.
    unsigned int stride;
    unsigned int offset;

    stride = sizeof(VertexType);
    offset = 0;

    //������ ���ؽ� ���۸� �Է� ���̾ƿ� ��������(Input Assembler)�� Ȱ��ȭ�Ͽ� �׷��� �� �ְ� �Ѵ�.
    DX11.GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
    //�ε��� ���۵� ���������� �����Ѵ�.
    DX11.GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    //���� ���۷� �׸� �⺻���� �����մϴ�.
    DX11.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool ESpriteRendererComponent::InitializeBuffer()
{
    //���ؽ� ���� ����
    bool result = InitializeVertexBuffer();
    if (false == result) return false;
    
    //�ε��� ���� ����
    result = InitializeIndexBuffer();
    if (false == result) return false;

    return true;
}

bool ESpriteRendererComponent::InitializeVertexBuffer()
{
    //1.������ ���ؽ� ������ ������ ������ �����ϴ� D3D11_BUFFER_DESC ����ü ����
    D3D11_BUFFER_DESC xyzBufferDesc;
    xyzBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    xyzBufferDesc.ByteWidth = sizeof(VertexType) * 4;
    xyzBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    xyzBufferDesc.CPUAccessFlags = 0;
    xyzBufferDesc.MiscFlags = 0;
    xyzBufferDesc.StructureByteStride = 0;

    //2.���� ���ҽ�(���ҽ��� ���� ������)�� �ʱ�ȭ �����ͷ� D3D11_SUBRESOURCE_DATA ����ü�� ����
    //2-1.���� ���ҽ� �ʱ�ȭ

    float fSizeX = 5.0f;
    float fSizeY = 5.0f;
    VertexType vertices[] =
    {
        XMFLOAT3(-fSizeX, fSizeY, 0.0f),
        XMFLOAT3(-fSizeX, -fSizeY, 0.0f),
        XMFLOAT3( fSizeX, -fSizeY, 0.0f),
        XMFLOAT3( fSizeX, fSizeY, 0.0f)
    };

    //2-2.���� ���ҽ� ����
    D3D11_SUBRESOURCE_DATA xyzSubData;
    xyzSubData.pSysMem = vertices;
    xyzSubData.SysMemPitch = 0;
    xyzSubData.SysMemSlicePitch = 0;

    //3.CreateBuffer ȣ��
    ID3D11Buffer* g_pVerBuffer = nullptr;
    HRESULT hr = DX11.GetDevice()->CreateBuffer(&xyzBufferDesc, &xyzSubData, &g_pVerBuffer);
    if (FAILED(hr)) return false;

    m_VertexBuffer = g_pVerBuffer;

    return true;
}

bool ESpriteRendererComponent::InitializeIndexBuffer()
{
    //�ε��� ���۵� ���۸��ҽ��� �� �����̹Ƿ� ���ؽ� ���ۿ� ��������� ����ϴ�.

    //1.�ε��� ���� ����
    D3D11_BUFFER_DESC idBufferDesc;
    idBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    idBufferDesc.ByteWidth = sizeof(VertexType) * 2;
    idBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    idBufferDesc.CPUAccessFlags = 0;
    idBufferDesc.MiscFlags = 0;
    idBufferDesc.StructureByteStride = 0;

    m_IndexCount = 6;

    //2.�ε��� ���� ���긮�ҽ� �ʱ�ȭ
    UINT idxVertexID[] =
    {
        0,1,2 ,2,1,3
    };

    //3.�ε��� ���� ���긮�ҽ� ����
    D3D11_SUBRESOURCE_DATA idxSubData;
    idxSubData.pSysMem = &idBufferDesc;
    idxSubData.SysMemPitch = 0;
    idxSubData.SysMemSlicePitch = 0;

    //4.�ε������� ����
    ID3D11Buffer* g_pIdxBuffer = nullptr;
    HRESULT hr = DX11.GetDevice()->CreateBuffer(&idBufferDesc, &idxSubData, &g_pIdxBuffer);
    if (FAILED(hr)) return false;

    m_IndexBuffer = g_pIdxBuffer;
    
    return true;
}

bool ESpriteRendererComponent::InitializeInputLayout(ID3D10Blob* pBlobVS)
{
    D3D11_INPUT_ELEMENT_DESC polygonLayout[2] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    unsigned int numElements = ARRAYSIZE(polygonLayout);

    //���� �����͸� ������ �Է� ����� ��������(IA)�� ���ؽ������� �����͸� ��� �о���ϱ� �����ϱ� ����
    //�Է� ���̾ƿ� ������Ʈ�� �����ؾ� �Ѵ�.
    HRESULT hr = DX11.GetDevice()->CreateInputLayout(polygonLayout, numElements, pBlobVS->GetBufferPointer(), pBlobVS->GetBufferSize(), &m_InputLayout);
    if (FAILED(hr)) return false;

    //�Է·��̾ƿ� ����
    DX11.GetDeviceContext()->IASetInputLayout(m_InputLayout);
    //������Ƽ�� Ÿ�� ����
    DX11.GetDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    return false;
}

bool ESpriteRendererComponent::InitializeShader(const TCHAR* vsFilename, const TCHAR* psFilename)
{
    ID3D10Blob* errorMessage = 0;

    //Dx9�� �޸� ������ ������������ �����Ǿ� ��� ���̴� �ڵ带 �ۼ��ؾ� �Ѵ�.
    //1. ���̴� �ڵ带 ������ �Ѵ�.
    ID3DBlob* pBlobVs = nullptr; //�����ϵ� HLSL ����Ʈ �ڵ带 �����صδ� ����(VertexShader)
    ID3DBlob* pBlobPs = nullptr; //�����ϵ� HLSL ����Ʈ �ڵ带 �����صδ� ����(PixelShader)

    //���ؽ� ���̴� ������
    HRESULT hr = D3DX11CompileFromFile(
        vsFilename,
        nullptr,
        nullptr,
        "VS",
        "vs_5_0",
        D3D10_SHADER_ENABLE_STRICTNESS,
        0,
        nullptr,
        &pBlobVs,
        &errorMessage,
        nullptr
    );

    //�ȼ� ���̴� ������
    hr = D3DX11CompileFromFile(
        psFilename,
        nullptr,
        nullptr,
        "PS",
        "ps_5_0",
        D3D10_SHADER_ENABLE_STRICTNESS,
        0,
        nullptr,
        &pBlobPs,
        &errorMessage,
        nullptr
    );


    //2.�������ϸ� ID3DBlob �������̽��� �����Ͱ� �Ѿ���µ� �̰ɷ� ���ؽ�,�ȼ� ���̴� ������Ʈ�� �����.
    hr = DX11.GetDevice()->CreateVertexShader(pBlobVs->GetBufferPointer(), pBlobVs->GetBufferSize(),
        nullptr, &m_VertexShader);
    if (FAILED(hr)) return false;

    hr = DX11.GetDevice()->CreatePixelShader(pBlobVs->GetBufferPointer(), pBlobVs->GetBufferSize(),
        nullptr, &m_PixelShader);
    if (FAILED(hr)) return false;

    //3.�Է� ���̾ƿ�
    bool result = InitializeInputLayout(pBlobVs);
    if (false == result) return false;

    SAFE_RELEASE(pBlobVs);
    SAFE_RELEASE(pBlobPs);

    return true;
}

bool ESpriteRendererComponent::SetShaderParameters(D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix ,ID3D11ShaderResourceView* texture)
{
    D3D11_BUFFER_DESC matrixBufferDesc;
    MatrixBufferType* dataPtr;
    unsigned int bufferNumber = 0;

    matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
    matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    matrixBufferDesc.MiscFlags = 0;
    matrixBufferDesc.StructureByteStride = 0; 
    
    HRESULT hr = DX11.GetDevice()->CreateBuffer(&matrixBufferDesc, NULL, &m_MatrixBuffer);
    if(FAILED(hr)) { return false; }

    //����� ��ġ�Ͽ� ���̴������� �غ��մϴ�.
    D3DXMatrixTranspose(&worldMatrix, &worldMatrix);
    D3DXMatrixTranspose(&viewMatrix, &viewMatrix);
    D3DXMatrixTranspose(&projectionMatrix, &projectionMatrix);

    D3D11_MAPPED_SUBRESOURCE mappedResource;
    //��� ���۸� ���� ���� ��޴ϴ�.
    HRESULT result = DX11.GetDeviceContext()->Map(m_MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    if (FAILED(result)) return false;

    //��� ������ �����Ϳ� ���� �����͸� �����ɴϴ�.
    dataPtr = (MatrixBufferType*)mappedResource.pData;

    //����� ��� ���ۿ� �����մϴ�.
    dataPtr->world = worldMatrix;
    dataPtr->view = viewMatrix;
    dataPtr->projection = projectionMatrix;

    //��� ������ ����� Ǳ�ϴ�.
    DX11.GetDeviceContext()->Unmap(m_MatrixBuffer, 0);

    //���� ���̴����� ��� ������ ��ġ�� �����մϴ�.
    bufferNumber = 0;

    //������Ʈ�� ������ ���� ���̴����� ��� ���۸� �����մϴ�.
    DX11.GetDeviceContext()->VSSetConstantBuffers(bufferNumber, 1, &m_MatrixBuffer);
    //�ȼ� ���̴����� ���̴� �ؽ�ó ���ҽ��� �����մϴ�.
    DX11.GetDeviceContext()->PSSetShaderResources(0, 1, &texture);

    return true;
}
