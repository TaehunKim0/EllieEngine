#include "Precompiled.hpp"
#include "ETexture.hpp"

ETexture::ETexture()
    : _ImageInfo({0,})
{
}

ETexture::~ETexture()
{
}

bool ETexture::LoadTexture(ID3D11Device* g_pDevice, const WCHAR* path)
{
    /*밑의 모든 과정을 간소화 한 함수*/
    /*HRESULT result;
    result = D3DX11CreateShaderResourceViewFromFileW(g_pDevice, path, NULL, NULL, &_TextureResourceView, NULL);
    if (FAILED(result))
        return false;*/



    //1. 이미지 파일 조사
    //해당 파일의 사이즈나 포맷에 맞춘 텍스처를 만들고 싶은 경우에 사용한다.
    D3DX11_IMAGE_INFO imageinfo;
    HRESULT hr; 
    
    D3DX11GetImageInfoFromFile(path, NULL, &imageinfo, &hr);
    if (FAILED(hr)) return false;
    _ImageInfo = imageinfo;

    //2. 텍스처 리소스 생성
    ID3D11Resource* g_pTexture = NULL;
    D3DX11CreateTextureFromFile(g_pDevice, path, NULL /*디폴트 설정*/, NULL/*비동기 설정*/, &g_pTexture, &hr);

    /*
    //만약 텍스처에 대한 설정값을 넣고 싶다면
    D3DX11_IMAGE_LOAD_INFO imageLoadInfo;
    imageLoadInfo.Width = 256;
    imageLoadInfo.Height = 256;
    imageLoadInfo.Depth = 0;
    imageLoadInfo.FirstMipLevel = 0;
    imageLoadInfo.MipLevels = 8;
    imageLoadInfo.Usage = D3D11_USAGE_DEFAULT;
    imageLoadInfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    imageLoadInfo.CpuAccessFlags = 0;
    imageLoadInfo.MiscFlags = 0;
    imageLoadInfo.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    imageLoadInfo.Filter = D3DX11_FILTER_LINEAR;
    imageLoadInfo.pSrcInfo = NULL;

    D3DX11CreateTextureFromFile(g_pDevice, path, &imageLoadInfo, NULL, &g_pTexture, &hr);
    */
    if (FAILED(hr)) return false;
    _TextureResource = g_pTexture;


    //3. 텍스처 리소스를 셰이더에서 액세스 하려면 [셰이더 리소스 뷰]를 생성해야 한다.
    ID3D11ShaderResourceView* g_pTextureRV = NULL;
    hr = g_pDevice->CreateShaderResourceView(g_pTexture, NULL, &g_pTextureRV);
    if (FAILED(hr)) return false;
    _TextureResourceView = g_pTextureRV;

    return true;
}

void ETexture::Excute()
{
    _TextureResource->Release();
    _TextureResourceView->Release();
}

void ETexture::Destroy()
{
}