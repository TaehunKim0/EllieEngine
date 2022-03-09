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
	bool Init();
	void Tick();
	void Render();

	void Excute() override;
	void Destroy();

public:
	void SetSprite(ESprite* sprite);

private:
	bool InitializeBuffer();
	bool InitializeVertexBuffer();
	bool InitializeIndexBuffer();

	bool InitializeShader(const TCHAR* vsFilename, const TCHAR* psFilename);
	bool SetShaderParameters(D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture);
	bool InitializeInputLayout(ID3D10Blob* pBlobVS);

	void RenderShader();
	void RenderBuffer();

private:
	ETransformComponent* m_TransformComponent = nullptr;
	ESprite* m_Sprite;

	struct VertexType
	{
		XMFLOAT3 Position;
	};
	struct MatrixBufferType { D3DXMATRIX world; D3DXMATRIX view; D3DXMATRIX projection; };

	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_IndexBuffer;
	ID3D11Buffer* m_MatrixBuffer;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_InputLayout;

	int m_IndexCount;
};