#pragma once
#include "EObject.h"

class ETexture : public EObject
{
public:
	ETexture();
	~ETexture();

	bool LoadTexture(ID3D11Device* g_pDevice, const WCHAR* path);
	ID3D11ShaderResourceView* GetTexture() {
		return m_TextureResourceView;
	}
public:
	void Excute() final;
	void Destroy() final;

private:
	D3DX11_IMAGE_INFO m_ImageInfo;
	ID3D11Resource* m_TextureResource = NULL;
	ID3D11ShaderResourceView* m_TextureResourceView = NULL;
};

