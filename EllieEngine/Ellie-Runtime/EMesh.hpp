#pragma once

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "TransformBuffer.hpp"
#include "InputLayout.hpp"
#include "TransformComponent.hpp"

class EMesh
{
public:
	EMesh() {} ;
	virtual ~EMesh() {};

public:
	virtual bool InitializeBuffers(ID3D11Device* InDevice, ID3DBlob* InVertexShaderBuffer) = 0;
	virtual void RenderBuffers(ID3D11DeviceContext* InDeviceContext);

	virtual void BindBuffers(ID3D11DeviceContext* InDeviceContext);
	virtual void DrawBuffers(ID3D11DeviceContext* InDeviceContext);
	virtual void UpdateBuffers(ID3D11DeviceContext* InDeviceContext);

protected:
	VertexBuffer _VertexBuffer;
	IndexBuffer _IndexBuffer;
	TransformBuffer _TransformBuffer;
	InputLayout _InputLayout;
	ETransformComponent _Transform;
};