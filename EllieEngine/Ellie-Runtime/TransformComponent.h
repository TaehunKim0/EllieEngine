#pragma once
#include "EComponent.h"



class ETransformComponent : public EComponent
{
public:
	ETransformComponent();
	virtual ~ETransformComponent();

public:
	bool Init() final;
	void Tick() final;
	void Excute() final;

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

	void GetMatrix(Mat4x4 outWorld, Mat4x4 outView, Mat4x4 outProjection) {
		outWorld = m_WorldMatrix;
		outView = m_ViewMatrix;
		outProjection = m_ProjectionMatrix;
	}

private:
	Mat4x4 m_WorldMatrix;
	Mat4x4 m_ViewMatrix;
	Mat4x4 m_ProjectionMatrix;

	Vec3 m_Scale;
	Vec3 m_Rotation;
	Vec3 m_Position;
};