#pragma once
#include "EObject.h"

/*
텍스처 사용법
1. 텍스처 리소스(이미지 데이터)를 생성한다.
2. 텍스처에 액세스하기 위한 텍스처 리소스 뷰를 생성한다.
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
	//자신을 해제할 때 호출.
	void Excute() override;

	//메모리 관리자에게서 자신을 제거한다.
	void Destroy() override;
};

