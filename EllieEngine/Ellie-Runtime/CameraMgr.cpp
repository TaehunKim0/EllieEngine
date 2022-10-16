#include "Precompiled.hpp"
#include "CameraMgr.hpp"

void CameraMgr::Init()
{
	_Position = Vec3(0.0f,0.0f,-10.f);
	_Rotation = Vec3(0.0f,0.0f,0.0f);
}

void CameraMgr::Tick()
{
	Render();
}

void CameraMgr::Excute()
{
}

void CameraMgr::SetPosition(float x, float y, float z)
{
	_Position = Vec3(x, y, z);
	return;
}

void CameraMgr::SetRotation(float x, float y, float z)
{
	_Rotation = Vec3(x, y, z);
	return;
}

void CameraMgr::GetPosition(Vec3& pos)
{
	pos = _Position;
	return;
}

void CameraMgr::GetRotation(Vec3& rot)
{
	_Rotation = rot;
	return;
}

void CameraMgr::Render()
{
	//XMFLOAT3 up, position, lookAt;
	//float yaw, pitch, roll;
	//XMMATRIX rotationMatrix;

	//up.x = 0.0f;
	//up.y = 1.0f;
	//up.z = 0.0f;

	//position.x = _Position.x;
	//position.y = _Position.y;
	//position.z = _Position.z;

	//lookAt.x = 0.0f;
	//lookAt.y = 0.0f;
	//lookAt.z = 1.0f;

	////ex) 60 * ����/180 = 1/3 ����
	////ex) 60 * 0.0174532925f = 1.04719755f(60��)
	////���� �� ���� ����.
	//pitch = _Rotation.y * 0.0174532925f; //�Ϲ����� ���Ϸ����� �������� �ٲ۴�. = D3DXToRadian
	//yaw = _Rotation.x * 0.0174532925f;
	//roll = _Rotation.z * 0.0174532925f;

	//rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(yaw, pitch, roll);

	////lookAt �� up ���͸� ȸ�� ��ķ� �����Ͽ� �䰡 �������� �ùٸ��� ȸ���ǵ����մϴ�.
	////D3DXVec3TransformCoord : ���� ��ȯ�� ���� �Լ� , ���Ϳ� ����� ���ؼ� ����� ����� ������ �Ǵ� ���͸� ��ȯ
	//XMVECTOR lookAtVector = XMVector3TransformCoord(XMLoadFloat3(&lookAt), rotationMatrix);
	//XMVECTOR upVector = XMVector3TransformCoord(XMLoadFloat3(&up), rotationMatrix);

	////ȸ�� �� ī�޶� ��ġ�� ��� ��ġ�� ��ȯ�մϴ�.
	////lookAt = position + lookAt;
	//lookAtVector = XMVectorAdd(XMLoadFloat3(&position), lookAtVector);

	////���������� ������Ʈ �� �� ���Ϳ��� �� ����� ����ϴ�.
	//_ViewMatrix = DirectX::XMMatrixLookAtLH(XMLoadFloat3(&position), lookAtVector, upVector);

	XMFLOAT3 up, position, lookAt;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = _Position.x;
	position.y = _Position.y;
	position.z = _Position.z;

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = _Rotation.y * 0.0174532925f;
	yaw = _Rotation.x * 0.0174532925f;
	roll = _Rotation.z * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	//D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);
	rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	//D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	//D3DXVec3TransformCoord(&up, &up, &rotationMatrix);
	XMVECTOR lookAtVector = XMVector3TransformCoord(XMLoadFloat3(&lookAt), rotationMatrix);
	XMVECTOR upVector = XMVector3TransformCoord(XMLoadFloat3(&up), rotationMatrix);


	// Translate the rotated camera position to the location of the viewer.
	//lookAt = position + lookAt;
	lookAtVector = XMVectorAdd(XMLoadFloat3(&position), lookAtVector);

	// Finally create the view matrix from the three updated vectors.
	//D3DXMatrixLookAtLH(&_viewMatrix, &position, &lookAt, &up);
	_ViewMatrix = DirectX::XMMatrixLookAtLH(XMLoadFloat3(&position), lookAtVector, upVector);

	GenerateBaseViewMatrix();
}

void CameraMgr::GetViewMatrix(Mat4x4& outviewMatrix)
{
	outviewMatrix = _ViewMatrix;
	return;
}

void CameraMgr::GenerateBaseViewMatrix()
{
	Vec3 up, position, lookAt;
	float radians;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	position.x = _Position.x;
	position.y = _Position.y;
	position.z = _Position.z;

	radians = _Rotation.y * 0.0174532925f;

	lookAt.x = sinf(radians) + _Position.x;
	lookAt.y = _Position.y;
	lookAt.z = cosf(radians) + _Position.z;

	_BaseViewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&position), XMLoadFloat3(&lookAt), XMLoadFloat3(&up));
	return;
}


void CameraMgr::GetBaseViewMatrix(Mat4x4& outViewMatrix)
{
	outViewMatrix = _ViewMatrix;
	return;
}