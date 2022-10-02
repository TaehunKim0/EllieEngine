#pragma once

#include "ETexture.h"
#include "TransformComponent.h"
#include "EGameObject.h"

//2D �׷��� ������Ʈ
//Texture�� ��� �׷����� �����ϴ� Ŭ����
class ESprite : public EGameObject
{
public:
	ESprite();
	~ESprite();

public:
	void Begin() final;
	void Update() final;

	void Excute() final;
	void Destroy() final;

public:
	bool CreateTexture(ID3D11Device* g_pDevice, const WCHAR* path);
	ID3D11ShaderResourceView* GetTexture() {
		return _Texture->GetTexture();
	}

	ID3D11SamplerState** GetSamplerState() {
		return &_SampleState;
	}

	ETransformComponent& GetTransform() {
		return _TransformComponent;
	}

private:
	ETransformComponent _TransformComponent;
	ID3D11SamplerState* _SampleState;
	ETexture* _Texture;
};