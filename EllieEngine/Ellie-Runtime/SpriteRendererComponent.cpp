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

    //정점, 인덱스 버퍼 생성
    result = InitializeBuffer(); 
    if (false == result) return false;

    //셰이더 컴파일 후 셰이더 오브젝트 생성, 인풋 레이아웃 설정
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
    //정점, 픽셀 셰이더를 설정하고 삼각형을 그립니다.
    DX11.GetDeviceContext()->IASetInputLayout(m_InputLayout);
    DX11.GetDeviceContext()->VSSetShader(m_VertexShader, nullptr, 0);
    DX11.GetDeviceContext()->PSSetShader(m_PixelShader, nullptr, 0);
    DX11.GetDeviceContext()->DrawIndexed(m_IndexCount, 0, 0);
}

void ESpriteRendererComponent::RenderBuffer()
{
    //정점 버퍼와 인덱스 버퍼를 파이프라인에 넣어 그릴 준비를 합니다.
    unsigned int stride;
    unsigned int offset;

    stride = sizeof(VertexType);
    offset = 0;

    //생성한 버텍스 버퍼를 입력 레이아웃 스테이지(Input Assembler)에 활성화하여 그려질 수 있게 한다.
    DX11.GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
    //인덱스 버퍼도 마찬가지로 설정한다.
    DX11.GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    //정점 버퍼로 그릴 기본형을 설정합니다.
    DX11.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool ESpriteRendererComponent::InitializeBuffer()
{
    //버텍스 버퍼 생성
    bool result = InitializeVertexBuffer();
    if (false == result) return false;
    
    //인덱스 버퍼 생성
    result = InitializeIndexBuffer();
    if (false == result) return false;

    return true;
}

bool ESpriteRendererComponent::InitializeVertexBuffer()
{
    //1.생성할 버텍스 버퍼의 데이터 형식을 정의하는 D3D11_BUFFER_DESC 구조체 선언
    D3D11_BUFFER_DESC xyzBufferDesc;
    xyzBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    xyzBufferDesc.ByteWidth = sizeof(VertexType) * 4;
    xyzBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    xyzBufferDesc.CPUAccessFlags = 0;
    xyzBufferDesc.MiscFlags = 0;
    xyzBufferDesc.StructureByteStride = 0;

    //2.서브 리소스(리소스의 실제 데이터)의 초기화 데이터로 D3D11_SUBRESOURCE_DATA 구조체를 정의
    //2-1.서브 리소스 초기화

    float fSizeX = 5.0f;
    float fSizeY = 5.0f;
    VertexType vertices[] =
    {
        XMFLOAT3(-fSizeX, fSizeY, 0.0f),
        XMFLOAT3(-fSizeX, -fSizeY, 0.0f),
        XMFLOAT3( fSizeX, -fSizeY, 0.0f),
        XMFLOAT3( fSizeX, fSizeY, 0.0f)
    };

    //2-2.서브 리소스 정의
    D3D11_SUBRESOURCE_DATA xyzSubData;
    xyzSubData.pSysMem = vertices;
    xyzSubData.SysMemPitch = 0;
    xyzSubData.SysMemSlicePitch = 0;

    //3.CreateBuffer 호출
    ID3D11Buffer* g_pVerBuffer = nullptr;
    HRESULT hr = DX11.GetDevice()->CreateBuffer(&xyzBufferDesc, &xyzSubData, &g_pVerBuffer);
    if (FAILED(hr)) return false;

    m_VertexBuffer = g_pVerBuffer;

    return true;
}

bool ESpriteRendererComponent::InitializeIndexBuffer()
{
    //인덱스 버퍼도 버퍼리소스의 한 종류이므로 버텍스 버퍼와 생성방식이 비슷하다.

    //1.인덱스 버퍼 정의
    D3D11_BUFFER_DESC idBufferDesc;
    idBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    idBufferDesc.ByteWidth = sizeof(VertexType) * 2;
    idBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    idBufferDesc.CPUAccessFlags = 0;
    idBufferDesc.MiscFlags = 0;
    idBufferDesc.StructureByteStride = 0;

    m_IndexCount = 6;

    //2.인덱스 버퍼 서브리소스 초기화
    UINT idxVertexID[] =
    {
        0,1,2 ,2,1,3
    };

    //3.인덱스 버퍼 서브리소스 정의
    D3D11_SUBRESOURCE_DATA idxSubData;
    idxSubData.pSysMem = &idBufferDesc;
    idxSubData.SysMemPitch = 0;
    idxSubData.SysMemSlicePitch = 0;

    //4.인덱스버퍼 생성
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

    //위의 데이터를 가지고 입력 어셈블러 스테이지(IA)가 버텍스버퍼의 데이터를 어떻게 읽어들일까 지시하기 위해
    //입력 레이아웃 오브젝트를 생성해야 한다.
    HRESULT hr = DX11.GetDevice()->CreateInputLayout(polygonLayout, numElements, pBlobVS->GetBufferPointer(), pBlobVS->GetBufferSize(), &m_InputLayout);
    if (FAILED(hr)) return false;

    //입력레이아웃 설정
    DX11.GetDeviceContext()->IASetInputLayout(m_InputLayout);
    //프리미티브 타입 정의
    DX11.GetDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    return false;
}

bool ESpriteRendererComponent::InitializeShader(const TCHAR* vsFilename, const TCHAR* psFilename)
{
    ID3D10Blob* errorMessage = 0;

    //Dx9와 달리 고정된 파이프라인이 폐지되어 모든 셰이더 코드를 작성해야 한다.
    //1. 셰이더 코드를 컴파일 한다.
    ID3DBlob* pBlobVs = nullptr; //컴파일된 HLSL 바이트 코드를 저장해두는 변수(VertexShader)
    ID3DBlob* pBlobPs = nullptr; //컴파일된 HLSL 바이트 코드를 저장해두는 변수(PixelShader)

    //버텍스 셰이더 컴파일
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

    //픽셀 셰이더 컴파일
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


    //2.컴파일하면 ID3DBlob 인터페이스로 데이터가 넘어오는데 이걸로 버텍스,픽셀 셰이더 오브젝트를 만든다.
    hr = DX11.GetDevice()->CreateVertexShader(pBlobVs->GetBufferPointer(), pBlobVs->GetBufferSize(),
        nullptr, &m_VertexShader);
    if (FAILED(hr)) return false;

    hr = DX11.GetDevice()->CreatePixelShader(pBlobVs->GetBufferPointer(), pBlobVs->GetBufferSize(),
        nullptr, &m_PixelShader);
    if (FAILED(hr)) return false;

    //3.입력 레이아웃
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

    //행렬을 전치하여 셰이더용으로 준비합니다.
    D3DXMatrixTranspose(&worldMatrix, &worldMatrix);
    D3DXMatrixTranspose(&viewMatrix, &viewMatrix);
    D3DXMatrixTranspose(&projectionMatrix, &projectionMatrix);

    D3D11_MAPPED_SUBRESOURCE mappedResource;
    //상수 버퍼를 쓰기 위해 잠급니다.
    HRESULT result = DX11.GetDeviceContext()->Map(m_MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    if (FAILED(result)) return false;

    //상수 버퍼의 데이터에 대한 포인터를 가져옵니다.
    dataPtr = (MatrixBufferType*)mappedResource.pData;

    //행렬을 상수 버퍼에 복사합니다.
    dataPtr->world = worldMatrix;
    dataPtr->view = viewMatrix;
    dataPtr->projection = projectionMatrix;

    //상수 버퍼의 잠금을 풉니다.
    DX11.GetDeviceContext()->Unmap(m_MatrixBuffer, 0);

    //정점 셰이더에서 상수 버퍼의 위치를 설정합니다.
    bufferNumber = 0;

    //업데이트된 값으로 정점 셰이더에서 상수 버퍼를 설정합니다.
    DX11.GetDeviceContext()->VSSetConstantBuffers(bufferNumber, 1, &m_MatrixBuffer);
    //픽셀 셰이더에서 셰이더 텍스처 리소스를 설정합니다.
    DX11.GetDeviceContext()->PSSetShaderResources(0, 1, &texture);

    return true;
}
