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

	//ex) 60 * ����/180 = 1/3 ����
	//ex) 60 * 0.0174532925f = 1.04719755f(60��)
	//���� �� ���� ����.
	pitch = m_Rotation.y * 0.0174532925f; //�Ϲ����� ���Ϸ����� �������� �ٲ۴�. = D3DXToRadian
	yaw = m_Rotation.x * 0.0174532925f;
	roll = m_Rotation.z * 0.0174532925f;

	rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(yaw, pitch, roll);

	//lookAt �� up ���͸� ȸ�� ��ķ� �����Ͽ� �䰡 �������� �ùٸ��� ȸ���ǵ����մϴ�.
	//D3DXVec3TransformCoord : ���� ��ȯ�� ���� �Լ� , ���Ϳ� ����� ���ؼ� ����� ����� ������ �Ǵ� ���͸� ��ȯ
	XMVECTOR lookAtVector = XMVector3TransformCoord(XMLoadFloat3(&lookAt), rotationMatrix);
	XMVECTOR upVector = XMVector3TransformCoord(XMLoadFloat3(&up), rotationMatrix);

	//ȸ�� �� ī�޶� ��ġ�� ��� ��ġ�� ��ȯ�մϴ�.
	//lookAt = position + lookAt;
	lookAtVector = XMVectorAdd(XMLoadFloat3(&position), lookAtVector);

	//���������� ������Ʈ �� �� ���Ϳ��� �� ����� ����ϴ�.
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