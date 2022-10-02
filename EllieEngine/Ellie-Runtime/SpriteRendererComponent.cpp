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

    //정점, 인덱스 버퍼 생성
    result = initializeBuffer(); 
    if (false == result) return false;

    //셰이더 컴파일 후 셰이더 오브젝트 생성, 인풋 레이아웃 설정
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
    //셰이더 값을 지정합니다.
    setShaderParameters(worldMatrix, viewMatrix, projectionMatrix, _Sprite->GetTexture());

    // 정점 입력 레이아웃을 설정합니다. 
    DX11.GetDeviceContext()->IASetInputLayout(_InputLayout);
    // 삼각형을 그릴 정점 셰이더와 픽셀 셰이더를 설정합니다.   
    DX11.GetDeviceContext()->VSSetShader(_VertexShader, NULL, 0);
    DX11.GetDeviceContext()->PSSetShader(_PixelShader, NULL, 0);
    // 삼각형을 그립니다.
    DX11.GetDeviceContext()->DrawIndexed(_IndexCount, 0, 0);

    return;
}

void ESpriteRendererComponent::renderBuffer()
{
    //정점 버퍼와 인덱스 버퍼를 파이프라인에 넣어 그릴 준비를 합니다.
    unsigned int stride;
    unsigned int offset;

    stride = sizeof(VertexType);
    offset = 0;

    //생성한 버텍스 버퍼를 입력 레이아웃 스테이지(Input Assembler)에 활성화하여 그려질 수 있게 한다.
    DX11.GetDeviceContext()->IASetVertexBuffers(0, 1, &_VertexBuffer, &stride, &offset);
    //인덱스 버퍼도 마찬가지로 설정한다.
    DX11.GetDeviceContext()->IASetIndexBuffer(_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    //정점 버퍼로 그릴 기본형을 설정합니다.
    DX11.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool ESpriteRendererComponent::initializeBuffer()
{
    //버텍스 버퍼 생성
    bool result = initializeVertexBuffer();
    if (false == result) return false;
    
    //인덱스 버퍼 생성
    result = initializeIndexBuffer();
    if (false == result) return false;

    return true;
}

bool ESpriteRendererComponent::initializeVertexBuffer()
{
    //1.생성할 버텍스 버퍼의 데이터 형식을 정의하는 D3D11_BUFFER_DESC 구조체 선언
    _VertexCount = 3;
    D3D11_BUFFER_DESC xyzBufferDesc;
    xyzBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    xyzBufferDesc.ByteWidth = sizeof(VertexType) * _VertexCount;
    xyzBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    xyzBufferDesc.CPUAccessFlags = 0;
    xyzBufferDesc.MiscFlags = 0;
    xyzBufferDesc.StructureByteStride = 0;

    //2.서브 리소스(리소스의 실제 데이터)의 초기화 데이터로 D3D11_SUBRESOURCE_DATA 구조체를 정의
    //2-1.서브 리소스 초기화
    VertexType* vertices = new VertexType[_VertexCount];
    vertices[0].Position = Vec3(-0.5f, -0.50f, 0.0f);  // Bottom left.
    vertices[0].Color = Vec4(1.0f, 0.0f, 0.0f, 1.0f);

    vertices[1].Position = Vec3(0.0f, 0.50f, 0.0f);  // Top middle.
    vertices[1].Color = Vec4(1.0f, 0.0f, 0.0f, 1.0f);

    vertices[2].Position = Vec3(0.5f, -0.5f, 0.0f);  // Bottom right.
    vertices[2].Color = Vec4(1.0f, 0.0f, 0.0f, 1.0f);

    //2-2.서브 리소스 정의
    D3D11_SUBRESOURCE_DATA xyzSubData;
    xyzSubData.pSysMem = vertices;
    xyzSubData.SysMemPitch = 0;
    xyzSubData.SysMemSlicePitch = 0;

    //3.CreateBuffer 호출
    HRESULT result = DX11.GetDevice()->CreateBuffer(&xyzBufferDesc, &xyzSubData, &_VertexBuffer);
    if (FAILED(result)) { return false; }

    delete[] vertices;

    return true;
}

bool ESpriteRendererComponent::initializeIndexBuffer()
{
    //인덱스 버퍼도 버퍼리소스의 한 종류이므로 버텍스 버퍼와 생성방식이 비슷하다.
    _IndexCount = 3;
    //1.인덱스 버퍼 정의
    D3D11_BUFFER_DESC idBufferDesc;
    idBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    idBufferDesc.ByteWidth = sizeof(unsigned long) * _IndexCount;
    idBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    idBufferDesc.CPUAccessFlags = 0;
    idBufferDesc.MiscFlags = 0;
    idBufferDesc.StructureByteStride = 0;

    //2.인덱스 버퍼 서브리소스 초기화
    unsigned long* indices = new unsigned long[_IndexCount];
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;

    //3.인덱스 버퍼 서브리소스 정의
    D3D11_SUBRESOURCE_DATA idxSubData;
    idxSubData.pSysMem = indices;
    idxSubData.SysMemPitch = 0;
    idxSubData.SysMemSlicePitch = 0;

    //4.인덱스버퍼 생성
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

    //위의 데이터를 가지고 입력 어셈블러 스테이지(IA)가 버텍스버퍼의 데이터를 어떻게 읽어들일까 지시하기 위해
    //입력 레이아웃 오브젝트를 생성해야 한다.
    HRESULT hr = DX11.GetDevice()->CreateInputLayout(polygonLayout, numElements, pBlobVS->GetBufferPointer(), pBlobVS->GetBufferSize(), &_InputLayout);
    if (FAILED(hr)) return false;

    return true;
}

bool ESpriteRendererComponent::initializeShader(const TCHAR* vsFilename, const TCHAR* psFilename)
{
    ID3D10Blob* errorMessage = 0;

    //Dx9와 달리 고정된 파이프라인이 폐지되어 모든 셰이더 코드를 작성해야 한다.
    //1. 셰이더 코드를 컴파일 한다.
    ID3DBlob* pBlobVs = nullptr; //컴파일된 HLSL 바이트 코드를 저장해두는 변수(VertexShader)
    ID3DBlob* pBlobPs = nullptr; //컴파일된 HLSL 바이트 코드를 저장해두는 변수(PixelShader)

   // 버텍스 셰이더 컴파일
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

    //픽셀 셰이더 컴파일
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


    //2.컴파일하면 ID3DBlob 인터페이스로 데이터가 넘어오는데 이걸로 버텍스,픽셀 셰이더 오브젝트를 만든다.
    hr1 = DX11.GetDevice()->CreateVertexShader(pBlobVs->GetBufferPointer(), pBlobVs->GetBufferSize(),
        nullptr, &_VertexShader);
    if (FAILED(hr1)) return false;

    hr2 = DX11.GetDevice()->CreatePixelShader(pBlobPs->GetBufferPointer(), pBlobPs->GetBufferSize(),
        nullptr, &_PixelShader);
    if (FAILED(hr2)) return false;

    //3.입력 레이아웃
    bool result = initializeInputLayout(pBlobVs);
    if (false == result) return false;

    //행렬 상수버퍼 생성
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
    //상수 버퍼를 쓰기 위해 잠급니다.
    HRESULT result = DX11.GetDeviceContext()->Map(_MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    if (FAILED(result)) return false;

    //상수 버퍼의 데이터에 대한 포인터를 가져옵니다.
    MatrixBufferType* dataPtr;
    dataPtr = (MatrixBufferType*)mappedResource.pData;

    //행렬을 상수 버퍼에 복사합니다.
    dataPtr->world = XMMatrixTranspose(worldMatrix);
    dataPtr->view = XMMatrixTranspose(viewMatrix);
    dataPtr->projection = XMMatrixTranspose(projectionMatrix);

    //상수 버퍼의 잠금을 풉니다.
    DX11.GetDeviceContext()->Unmap(_MatrixBuffer, 0);

    //정점 셰이더에서 상수 버퍼의 위치를 설정합니다.
    unsigned int bufferNumber = 0;

    //업데이트된 값으로 정점 셰이더에서 상수 버퍼를 설정합니다.
    DX11.GetDeviceContext()->VSSetConstantBuffers(bufferNumber, 1, &_MatrixBuffer);

    return true;
}