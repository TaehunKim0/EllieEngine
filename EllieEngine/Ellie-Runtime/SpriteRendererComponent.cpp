#include "Precompiled.h"
#include "SpriteRendererComponent.h"
#include "CameraMgr.h"

ESpriteRendererComponent::ESpriteRendererComponent()
{
    _VertexShader = 0;
    _PixelShader = 0;
    _InputLayout = 0;
    _MatrixBuffer = 0;
}

ESpriteRendererComponent::~ESpriteRendererComponent()
{
}

bool ESpriteRendererComponent::Init()
{
    bool result;

    //����, �ε��� ���� ����
    result = initializeBuffer(); 
    if (false == result) return false;

    //���̴� ������ �� ���̴� ������Ʈ ����, ��ǲ ���̾ƿ� ����
    result = initializeShader(TEXT("ColorVS.hlsl"), TEXT("ColorPS.hlsl")); 
    if (false == result) return false;

    return true;
}

void ESpriteRendererComponent::Tick()
{
    Render();
}

void ESpriteRendererComponent::Excute()
{
    SAFE_RELEASE(_VertexBuffer);
    SAFE_RELEASE(_IndexBuffer);
    SAFE_RELEASE(_VertexShader);
    SAFE_RELEASE(_PixelShader);
    SAFE_RELEASE(_InputLayout);
    SAFE_RELEASE(_MatrixBuffer);
}

void ESpriteRendererComponent::Destroy()
{

}

void ESpriteRendererComponent::SetSprite(ESprite* sprite)
{
    _Sprite = sprite;
}

void ESpriteRendererComponent::Render()
{
    Mat4x4 worldMatrix, viewMatrix, projectionMatrix; 
    worldMatrix = XMMatrixIdentity();
    viewMatrix = XMMatrixIdentity();
    projectionMatrix = XMMatrixIdentity();

    /*CORE.GetCameraMgrCore()->GetViewMatrix(viewMatrix);
    DX11.GetWorldMatrix(worldMatrix);
    DX11.GetProjectionMatrix(projectionMatrix);*/

    ETransformComponent& transform = _Sprite->GetTransform();


    renderBuffer();
    renderShader(worldMatrix, viewMatrix, projectionMatrix, _Sprite->GetTexture());
}

void ESpriteRendererComponent::renderShader(Mat4x4 worldMatrix, Mat4x4 viewMatrix, Mat4x4 projectionMatrix, ID3D11ShaderResourceView* texture)
{
    //���̴� ���� �����մϴ�.
    setShaderParameters(worldMatrix, viewMatrix, projectionMatrix, _Sprite->GetTexture());

    // ���� �Է� ���̾ƿ��� �����մϴ�. 
    DX11.GetDeviceContext()->IASetInputLayout(_InputLayout);
    // �ﰢ���� �׸� ���� ���̴��� �ȼ� ���̴��� �����մϴ�.   
    DX11.GetDeviceContext()->VSSetShader(_VertexShader, NULL, 0);
    DX11.GetDeviceContext()->PSSetShader(_PixelShader, NULL, 0);
    // �ﰢ���� �׸��ϴ�.
    DX11.GetDeviceContext()->DrawIndexed(_IndexCount, 0, 0);

    return;
}

void ESpriteRendererComponent::renderBuffer()
{
    //���� ���ۿ� �ε��� ���۸� ���������ο� �־� �׸� �غ� �մϴ�.
    unsigned int stride;
    unsigned int offset;

    stride = sizeof(VertexType);
    offset = 0;

    //������ ���ؽ� ���۸� �Է� ���̾ƿ� ��������(Input Assembler)�� Ȱ��ȭ�Ͽ� �׷��� �� �ְ� �Ѵ�.
    DX11.GetDeviceContext()->IASetVertexBuffers(0, 1, &_VertexBuffer, &stride, &offset);
    //�ε��� ���۵� ���������� �����Ѵ�.
    DX11.GetDeviceContext()->IASetIndexBuffer(_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    //���� ���۷� �׸� �⺻���� �����մϴ�.
    DX11.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool ESpriteRendererComponent::initializeBuffer()
{
    //���ؽ� ���� ����
    bool result = initializeVertexBuffer();
    if (false == result) return false;
    
    //�ε��� ���� ����
    result = initializeIndexBuffer();
    if (false == result) return false;

    return true;
}

bool ESpriteRendererComponent::initializeVertexBuffer()
{
    //1.������ ���ؽ� ������ ������ ������ �����ϴ� D3D11_BUFFER_DESC ����ü ����
    _VertexCount = 3;
    D3D11_BUFFER_DESC xyzBufferDesc;
    xyzBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    xyzBufferDesc.ByteWidth = sizeof(VertexType) * _VertexCount;
    xyzBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    xyzBufferDesc.CPUAccessFlags = 0;
    xyzBufferDesc.MiscFlags = 0;
    xyzBufferDesc.StructureByteStride = 0;

    //2.���� ���ҽ�(���ҽ��� ���� ������)�� �ʱ�ȭ �����ͷ� D3D11_SUBRESOURCE_DATA ����ü�� ����
    //2-1.���� ���ҽ� �ʱ�ȭ
    VertexType* vertices = new VertexType[_VertexCount];
    vertices[0].Position = Vec3(-0.5f, -0.50f, 0.0f);  // Bottom left.
    vertices[0].Color = Vec4(1.0f, 0.0f, 0.0f, 1.0f);

    vertices[1].Position = Vec3(0.0f, 0.50f, 0.0f);  // Top middle.
    vertices[1].Color = Vec4(1.0f, 0.0f, 0.0f, 1.0f);

    vertices[2].Position = Vec3(0.5f, -0.5f, 0.0f);  // Bottom right.
    vertices[2].Color = Vec4(1.0f, 0.0f, 0.0f, 1.0f);

    //2-2.���� ���ҽ� ����
    D3D11_SUBRESOURCE_DATA xyzSubData;
    xyzSubData.pSysMem = vertices;
    xyzSubData.SysMemPitch = 0;
    xyzSubData.SysMemSlicePitch = 0;

    //3.CreateBuffer ȣ��
    HRESULT result = DX11.GetDevice()->CreateBuffer(&xyzBufferDesc, &xyzSubData, &_VertexBuffer);
    if (FAILED(result)) { return false; }

    delete[] vertices;

    return true;
}

bool ESpriteRendererComponent::initializeIndexBuffer()
{
    //�ε��� ���۵� ���۸��ҽ��� �� �����̹Ƿ� ���ؽ� ���ۿ� ��������� ����ϴ�.
    _IndexCount = 3;
    //1.�ε��� ���� ����
    D3D11_BUFFER_DESC idBufferDesc;
    idBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    idBufferDesc.ByteWidth = sizeof(unsigned long) * _IndexCount;
    idBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    idBufferDesc.CPUAccessFlags = 0;
    idBufferDesc.MiscFlags = 0;
    idBufferDesc.StructureByteStride = 0;

    //2.�ε��� ���� ���긮�ҽ� �ʱ�ȭ
    unsigned long* indices = new unsigned long[_IndexCount];
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;

    //3.�ε��� ���� ���긮�ҽ� ����
    D3D11_SUBRESOURCE_DATA idxSubData;
    idxSubData.pSysMem = indices;
    idxSubData.SysMemPitch = 0;
    idxSubData.SysMemSlicePitch = 0;

    //4.�ε������� ����
    HRESULT result = DX11.GetDevice()->CreateBuffer(&idBufferDesc, &idxSubData, &_IndexBuffer);
    if (FAILED(result)) { return false; }

    delete[] indices;
    indices = 0;
    
    return true;
}

bool ESpriteRendererComponent::initializeInputLayout(ID3D10Blob* pBlobVS)
{
    D3D11_INPUT_ELEMENT_DESC polygonLayout[2] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    int numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

    //���� �����͸� ������ �Է� ����� ��������(IA)�� ���ؽ������� �����͸� ��� �о���ϱ� �����ϱ� ����
    //�Է� ���̾ƿ� ������Ʈ�� �����ؾ� �Ѵ�.
    HRESULT hr = DX11.GetDevice()->CreateInputLayout(polygonLayout, numElements, pBlobVS->GetBufferPointer(), pBlobVS->GetBufferSize(), &_InputLayout);
    if (FAILED(hr)) return false;

    return true;
}

bool ESpriteRendererComponent::initializeShader(const TCHAR* vsFilename, const TCHAR* psFilename)
{
    ID3D10Blob* errorMessage = 0;

    //Dx9�� �޸� ������ ������������ �����Ǿ� ��� ���̴� �ڵ带 �ۼ��ؾ� �Ѵ�.
    //1. ���̴� �ڵ带 ������ �Ѵ�.
    ID3DBlob* pBlobVs = nullptr; //�����ϵ� HLSL ����Ʈ �ڵ带 �����صδ� ����(VertexShader)
    ID3DBlob* pBlobPs = nullptr; //�����ϵ� HLSL ����Ʈ �ڵ带 �����صδ� ����(PixelShader)

   // ���ؽ� ���̴� ������
    HRESULT hr1 = D3DX11CompileFromFileW(
        vsFilename,
        nullptr,
        nullptr,
        "main",
        "vs_5_0",
        D3D10_SHADER_ENABLE_STRICTNESS,
        0,
        nullptr,
        &pBlobVs,
        &errorMessage,
        nullptr
    );

    //�ȼ� ���̴� ������
    HRESULT hr2 = D3DX11CompileFromFileW(
        psFilename,
        nullptr,
        nullptr,
        "main",
        "ps_5_0",
        D3D10_SHADER_ENABLE_STRICTNESS,
        0,
        nullptr,
        &pBlobPs,
        &errorMessage,
        nullptr
    );


    //2.�������ϸ� ID3DBlob �������̽��� �����Ͱ� �Ѿ���µ� �̰ɷ� ���ؽ�,�ȼ� ���̴� ������Ʈ�� �����.
    hr1 = DX11.GetDevice()->CreateVertexShader(pBlobVs->GetBufferPointer(), pBlobVs->GetBufferSize(),
        nullptr, &_VertexShader);
    if (FAILED(hr1)) return false;

    hr2 = DX11.GetDevice()->CreatePixelShader(pBlobPs->GetBufferPointer(), pBlobPs->GetBufferSize(),
        nullptr, &_PixelShader);
    if (FAILED(hr2)) return false;

    //3.�Է� ���̾ƿ�
    bool result = initializeInputLayout(pBlobVs);
    if (false == result) return false;

    //��� ������� ����
    D3D11_BUFFER_DESC matrixBufferDesc;
    matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
    matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    matrixBufferDesc.MiscFlags = 0;
    matrixBufferDesc.StructureByteStride = 0;

    HRESULT hr = DX11.GetDevice()->CreateBuffer(&matrixBufferDesc, NULL, &_MatrixBuffer);
    if (FAILED(hr)) { return false; }

    SAFE_RELEASE(pBlobVs);
    SAFE_RELEASE(pBlobPs);

    return true;
}

bool ESpriteRendererComponent::setShaderParameters(Mat4x4 worldMatrix, Mat4x4 viewMatrix, Mat4x4 projectionMatrix ,ID3D11ShaderResourceView* texture)
{
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    //��� ���۸� ���� ���� ��޴ϴ�.
    HRESULT result = DX11.GetDeviceContext()->Map(_MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    if (FAILED(result)) return false;

    //��� ������ �����Ϳ� ���� �����͸� �����ɴϴ�.
    MatrixBufferType* dataPtr;
    dataPtr = (MatrixBufferType*)mappedResource.pData;

    //����� ��� ���ۿ� �����մϴ�.
    dataPtr->world = XMMatrixTranspose(worldMatrix);
    dataPtr->view = XMMatrixTranspose(viewMatrix);
    dataPtr->projection = XMMatrixTranspose(projectionMatrix);

    //��� ������ ����� Ǳ�ϴ�.
    DX11.GetDeviceContext()->Unmap(_MatrixBuffer, 0);

    //���� ���̴����� ��� ������ ��ġ�� �����մϴ�.
    unsigned int bufferNumber = 0;

    //������Ʈ�� ������ ���� ���̴����� ��� ���۸� �����մϴ�.
    DX11.GetDeviceContext()->VSSetConstantBuffers(bufferNumber, 1, &_MatrixBuffer);

    return true;
}