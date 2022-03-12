#include "Precompiled.h"
#include "CameraMgr.h"

void CameraMgr::Init()
{
}

void CameraMgr::Tick()
{
}

void CameraMgr::Excute()
{
}

void CameraMgr::SetPosition(float x, float y, float z)
{
	m_Position = Vec3(x, y, z);
	return;
}


void CameraMgr::SetRotation(float x, float y, float z)
{
	m_Rotation = Vec3(x, y, z);
	return;
}

void CameraMgr::GetPosition(Vec3& pos)
{
	pos = m_Position;
	return;
}

void CameraMgr::GetRotation(Vec3& rot)
{
	m_Rotation = rot;
	return;
}

void CameraMgr::Render()
{
	XMFLOAT3 up, position, lookAt;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	position.x = m_Position.x;
	position.y = m_Position.y;
	position.z = m_Position.z;

	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	//ex) 60 * 파이/180 = 1/3 파이
	//ex) 60 * 0.0174532925f = 1.04719755f(60도)
	//위의 두 식은 같다.
	pitch = m_Rotation.y * 0.0174532925f; //일반적인 오일러각을 라디안으로 바꾼다. = D3DXToRadian
	yaw = m_Rotation.x * 0.0174532925f;
	roll = m_Rotation.z * 0.0174532925f;

	rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(yaw, pitch, roll);

	//lookAt 및 up 벡터를 회전 행렬로 변형하여 뷰가 원점에서 올바르게 회전되도록합니다.
	//D3DXVec3TransformCoord : 벡터 변환을 위한 함수 , 벡터에 행렬을 곱해서 행렬이 적용된 포인터 또는 벡터를 반환
	XMVECTOR lookAtVector = XMVector3TransformCoord(XMLoadFloat3(&lookAt), rotationMatrix);
	XMVECTOR upVector = XMVector3TransformCoord(XMLoadFloat3(&up), rotationMatrix);

	//회전 된 카메라 위치를 뷰어 위치로 변환합니다.
	//lookAt = position + lookAt;
	lookAtVector = XMVectorAdd(XMLoadFloat3(&position), lookAtVector);

	//마지막으로 업데이트 된 세 벡터에서 뷰 행렬을 만듭니다.
	m_ViewMatrix = DirectX::XMMatrixLookAtLH(XMLoadFloat3(&position), lookAtVector, upVector);
}

void CameraMgr::GetViewMatrix(Mat4x4& outviewMatrix)
{
	outviewMatrix = m_ViewMatrix;
	return;
}


void CameraMgr::GenerateBaseViewMatrix()
{
	Vec3 up, position, lookAt;
	float radians;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	position.x = m_Position.x;
	position.y = m_Position.y;
	position.z = m_Position.z;

	radians = m_Rotation.y * 0.0174532925f;

	lookAt.x = sinf(radians) + m_Position.x;
	lookAt.y = m_Position.y;
	lookAt.z = cosf(radians) + m_Position.z;

	m_BaseViewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&position), XMLoadFloat3(&lookAt), XMLoadFloat3(&up));
	return;
}


void CameraMgr::GetBaseViewMatrix(Mat4x4& outViewMatrix)
{
	outViewMatrix = m_ViewMatrix;
	return;
}