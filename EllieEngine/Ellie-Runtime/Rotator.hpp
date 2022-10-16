#pragma once
#include "Dx11.hpp"

class Rotator
{
public:
	FORCEINLINE constexpr Rotator() = default;
	FORCEINLINE constexpr Rotator(float InYaw, float InRoll, float InPitch) : Yaw(InYaw), Roll(InRoll), Pitch(InPitch) { }

public:
	static const Rotator Identity;
	float Yaw = 0.f, Pitch = 0.f, Roll = 0.f;
};