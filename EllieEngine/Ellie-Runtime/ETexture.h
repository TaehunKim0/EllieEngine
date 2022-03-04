#pragma once
#include "EObject.h"

/*
�ؽ�ó ����
1. �ؽ�ó ���ҽ�(�̹��� ������)�� �����Ѵ�.
2. �ؽ�ó�� �׼����ϱ� ���� �ؽ�ó ���ҽ� �並 �����Ѵ�.
3. 
*/

class ETexture : public EObject
{
private:
	D3DX11_IMAGE_INFO m_ImageInfo;
	ID3D11Resource* m_TextureResource = NULL;
	ID3D11ShaderResourceView* m_TextureResourceView = NULL;

public:
	ETexture();
	~ETexture();

	bool LoadTexture(ID3D11Device* g_pDevice, const WCHAR* path);
	
public:
	//�ڽ��� ������ �� ȣ��.
	void Excute() override;

	//�޸� �����ڿ��Լ� �ڽ��� �����Ѵ�.
	void Destroy() override;
};

