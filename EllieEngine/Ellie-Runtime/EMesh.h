#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "TransformBuffer.h"
#include "InputLayout.h"
#include "TransformComponent.h"

class EMesh
{
public:
	EMesh() {} ;
	virtual ~EMesh() {};

public:
	virtual bool InitializeBuffers(ID3D11Device* InDevice, ID3DBlob* InVertexShaderBuffer) = 0;

protected:
	VertexBuffer _VertexBuffer;
	IndexBuffer _IndexBuffer;
	TransformBuffer _TransformBuffer;
	InputLayout _InputLayout;
	ETransformComponent _Transform;
};