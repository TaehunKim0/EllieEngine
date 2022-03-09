#include "Precompiled.h"
#include "ESprite.h"

ESprite::ESprite()
{
}

ESprite::~ESprite()
{
}

void ESprite::Begin()
{

}

void ESprite::Tick()
{
	EGameObject::Tick();


}

bool ESprite::CreateTexture(ID3D11Device* g_pDevice, const WCHAR* path)
{
	m_Texture = new ETexture();
	m_Texture->LoadTexture(g_pDevice, path);

	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	HRESULT hr = DX11.GetDevice()->CreateSamplerState(&samplerDesc, &m_SampleState);
	if (FAILED(hr)) return false;

	return true;
}

void ESprite::Excute()
{
	m_TransformComponent->Excute();
	m_Texture->Excute();
	SAFE_RELEASE(m_SampleState);
}

void ESprite::Destroy()
{
}
