#pragma once

#include "EComponent.h"
#include "TransformComponent.h"
#include "ESprite.h"

//Sprite를 렌더링합니다
class ESpriteRendererComponent : public EComponent
{
public:
	ESpriteRendererComponent();
	~ESpriteRendererComponent();

public:
	bool Init() final;
	void Tick() final;
	void Render();

	void Excute() final;
	void Destroy() final;

public:
	void SetSprite(ESprite* sprite);

private:
	bool initializeBuffer();
	bool initializeVertexBuffer();
	bool initializeIndexBuffer();

	bool initializeShader(const TCHAR* vsFilename, const TCHAR* psFilename);
	bool setShaderParameters(Mat4x4 worldMatrix, Mat4x4 viewMatrix, Mat4x4 projectionMatrix, ID3D11ShaderResourceView* texture);
	bool initializeInputLayout(ID3D10Blob* pBlobVS);

	void renderShader(Mat4x4 worldMatrix, Mat4x4 viewMatrix, Mat4x4 projectionMatrix, ID3D11ShaderResourceView* texture);
	void renderBuffer();

private:
	ESprite* _Sprite;

	struct VertexType
	{
		Vec3 Position;
		Vec4 Color;
	};

	struct MatrixBufferType { Mat4x4 world; Mat4x4 view; Mat4x4 projection; };

	ID3D11Buffer* _VertexBuffer;
	ID3D11Buffer* _IndexBuffer;
	ID3D11Buffer* _MatrixBuffer;

	ID3D11VertexShader* _VertexShader;
	ID3D11PixelShader* _PixelShader;
	ID3D11InputLayout* _InputLayout;

	int _VertexCount;
	int _IndexCount;
};