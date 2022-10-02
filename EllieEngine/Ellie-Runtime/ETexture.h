#pragma once

class ETexture
{
public:
	ETexture();
	~ETexture();

	bool LoadTexture(ID3D11Device* g_pDevice, const WCHAR* path);
	ID3D11ShaderResourceView* GetTexture() {
		return _TextureResourceView;
	}
public:
	virtual void Excute();
	virtual void Destroy();

private:
	D3DX11_IMAGE_INFO _ImageInfo;
	ID3D11Resource* _TextureResource = NULL;
	ID3D11ShaderResourceView* _TextureResourceView = NULL;
};

