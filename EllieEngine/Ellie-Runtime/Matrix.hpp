#pragma once
#include "Precompiled.hpp"


namespace Math
{
	typedef XMMATRIX Matrix4x4;

	enum MatrixType{World, View, Projection};
}


#define Mat4x4 Math::Matrix4x4