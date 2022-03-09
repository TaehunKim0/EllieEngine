#pragma once
#include "Precompiled.h"


namespace Math
{
	typedef D3DXMATRIX Matrix4x4;

	enum MatrixType{World, View, Projection};
}


#define Mat4x4 Math::Matrix4x4