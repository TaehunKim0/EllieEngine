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
    /*���� ��� ������ ����ȭ �� �Լ�*/
    /*HRESULT result;
    result = D3DX11CreateShaderResourceViewFromFileW(g_pDevice, path, NULL, NULL, &_TextureResourceView, NULL);
    if (FAILED(result))
        return false;*/



    //1. �̹��� ���� ����
    //�ش� ������ ����� ���˿� ���� �ؽ�ó�� ����� ���� ��쿡 ����Ѵ�.
    D3DX11_IMAGE_INFO imageinfo;
    HRESULT hr; 
    
    D3DX11GetImageInfoFromFile(path, NULL, &imageinfo, &hr);
    if (FAILED(hr)) return false;
    _ImageInfo = imageinfo;

    //2. �ؽ�ó ���ҽ� ����
    ID3D11Resource* g_pTexture = NULL;
    D3DX11CreateTextureFromFile(g_pDevice, path, NULL /*����Ʈ ����*/, NULL/*�񵿱� ����*/, &g_pTexture, &hr);

    /*
    //���� �ؽ�ó�� ���� �������� �ְ� �ʹٸ�
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


    //3. �ؽ�ó ���ҽ��� ���̴����� �׼��� �Ϸ��� [���̴� ���ҽ� ��]�� �����ؾ� �Ѵ�.
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