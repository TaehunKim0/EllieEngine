#pragma once
#include "EComponent.h"



class ETransformComponent : public EComponent
{
private:
	Mat4x4 m_Matrix;
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
	Vec3 GetPosition() {
		return m_Position;
	}
	Vec3 GetRotation() {
		return m_Rotation;
	}
	Vec3 GetScale() {
		return m_Scale;
	}



};