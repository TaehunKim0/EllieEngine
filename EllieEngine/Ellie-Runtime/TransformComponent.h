#pragma once
#include "EComponent.h"



class ETransformComponent : public EComponent
{
private:
	Mat4x4 m_WorldMatrix;
	Mat4x4 m_ViewMatrix;
	Mat4x4 m_ProjectionMatrix;

	Vec3 m_Scale;
	Vec3 m_Rotation;
	Vec3 m_Position;
	
public:
	ETransformComponent();
	virtual ~ETransformComponent();

public:
	bool Init() override;
	void Tick() override;
	void Excute() override;

public:
	void SetPosition(float x, float y, float z) {
		m_Position.x = x; m_Position.y = y; m_Position.z = z;
	}


	Vec3 GetPosition() {
		return m_Position;
	}
	Vec3 GetRotation() {
		return m_Rotation;
	}
	Vec3 GetScale() {
		return m_Scale;
	}

	void GetMatrix(Mat4x4 world, Mat4x4 view, Mat4x4 projection) {
		world = m_WorldMatrix;
		view = m_ViewMatrix;
		projection = m_ProjectionMatrix;
	}

};