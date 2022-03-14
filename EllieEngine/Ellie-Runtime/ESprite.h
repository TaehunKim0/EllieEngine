#pragma once

#include "ETexture.h"
#include "TransformComponent.h"
#include "EGameObject.h"

//2D 그래픽 오브젝트
//Texture를 어떻게 그려낼지 결정하는 클래스
class ESprite : public EGameObject
{
public:
	ESprite();
	~ESprite();

public:
	void Begin() final;
	void Tick() final;

	void Excute() final;
	void Destroy() final;

public:
	bool CreateTexture(ID3D11Device* g_pDevice, const WCHAR* path);
	ID3D11ShaderResourceView* GetTexture() {
		return m_Texture->GetTexture();
	}
	void GetMatrix(Mat4x4 outWorld, Mat4x4 outView, Mat4x4 outProjection) {
		m_TransformComponent->GetMatrix(outWorld, outView, outProjection);
	}
	ID3D11SamplerState** GetSamplerState() {
		return &m_SampleState;
	}

private:
	ETransformComponent* m_TransformComponent;
	ID3D11SamplerState* m_SampleState;
	ETexture* m_Texture;
};