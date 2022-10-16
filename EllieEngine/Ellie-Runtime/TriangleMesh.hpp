#pragma once
#include "EMesh.hpp"

class TriangleMesh : public EMesh
{
public:
	TriangleMesh();
	virtual ~TriangleMesh();
	struct Vertex { float x; float y; float z; };

public:
	virtual bool InitializeBuffers(ID3D11Device* InDevice, ID3DBlob* InVertexShaderBuffer);

};