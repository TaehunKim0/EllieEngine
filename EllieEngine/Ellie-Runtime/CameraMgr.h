#pragma once
#include "IManager.h"
#include "Matrix.h"
#include "Vector.h"

class CameraMgr : public IManager
{
public:
	void Init() final;
	void Tick() final;
	void Excute() final;

public:
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	void GetPosition(Vec3& pos);
	void GetRotation(Vec3& rot);

	void Render();
	void GetViewMatrix(Mat4x4& viewMatrix);

	void GenerateBaseViewMatrix();
	void GetBaseViewMatrix(Mat4x4& viewMatrix);

private:
	Vec3 m_Position;
	Vec3 m_Rotation;
	Mat4x4 m_ViewMatrix, m_BaseViewMatrix;
};