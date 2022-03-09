#pragma once

#include "ETexture.h"
#include "TransformComponent.h"

//2D �׷��� ������Ʈ
//Texture�� ��� �׷����� �����ϴ� Ŭ����
class ESprite : public EGameObject
{
private:
	ETransformComponent* m_TransformComponent;
	ID3D11SamplerState* m_SampleState;
	ETexture* m_Texture;

public:
	ESprite();
	~ESprite();

public:
	void Begin();
	void Tick();

	void Excute();
	void Destroy();

public:
	bool CreateTexture(ID3D11Device* g_pDevice, const WCHAR* path);
	ID3D11ShaderResourceView* GetTexture() {
		return m_Texture->GetTexture();
	}
	void GetMatrix(Mat4x4 world, Mat4x4 view, Mat4x4 projection) {
		m_TransformComponent->GetMatrix(world, view, projection);
	}


};