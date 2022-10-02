#pragma once
#include "EComponent.h"
#include "Rotator.h"

class ETransformComponent : public EComponent
{
public:
	ETransformComponent() {}
	virtual ~ETransformComponent() {}

public:
	void SetPosition(const Vec3& InPos) { _Position = InPos; }
	void SetRotation(const Rotator& InRotation) { _Rotation = InRotation; }
	void SetScale(const Vec3& InScale) { _Scale = InScale; }

	void AddYawRotation(const float InDegree) { _Rotation.Yaw += InDegree; }
	void AddPitchRotation(const float InDegree) { _Rotation.Pitch += InDegree; }
	void AddRollRotation(const float InDegree) { _Rotation.Roll += InDegree; }

	Vec3 GetPosition() { return _Position; }
	Rotator GetRotation() { return _Rotation; }
	Vec3 GetScale() { return _Scale; }

private:
	FORCEINLINE Mat4x4 GetWorldMatrix()const;

public:
	bool Init() { return false; }
	void Tick() {}
	void Excute() {}

private:
	Vec3 _Scale;
	Vec3 _Position;
	Rotator _Rotation;

	Vec3 _Right;
	Vec3 _Left;
	Vec3 _Up;
};

FORCEINLINE Mat4x4 ETransformComponent::GetWorldMatrix() const
{
	
}