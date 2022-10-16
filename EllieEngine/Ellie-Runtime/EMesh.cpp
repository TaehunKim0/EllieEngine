#include "Precompiled.hpp"
#include "EMesh.hpp"

void EMesh::RenderBuffers(ID3D11DeviceContext* InDeviceContext)
{
	BindBuffers(InDeviceContext);
	DrawBuffers(InDeviceContext);
}

void EMesh::BindBuffers(ID3D11DeviceContext* InDeviceContext)
{
	_VertexBuffer.Bind(InDeviceContext);
	_IndexBuffer.Bind(InDeviceContext);
	_InputLayout.Bind(InDeviceContext);
	InDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	_TransformBuffer.Bind(InDeviceContext);
}

void EMesh::DrawBuffers(ID3D11DeviceContext* InDeviceContext)
{
	InDeviceContext->DrawIndexed(_IndexBuffer.Count(), 0, 0);
}

void EMesh::UpdateBuffers(ID3D11DeviceContext* InDeviceContext)
{

}
