#pragma once
#include "Dx11.h"

class TransformBuffer
{
public:
	TransformBuffer(){}
	virtual ~TransformBuffer() = default;

	bool Create(ID3D11Device* device, Mat4x4 InMatrix);
	void Bind(ID3D11DeviceContext* deviceContext);

	Mat4x4 _TransformMatrix;

private:
	ComPtr<ID3D11Buffer> _ConstantBuffer;
};