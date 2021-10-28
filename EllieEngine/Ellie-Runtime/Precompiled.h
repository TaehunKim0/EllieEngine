#pragma once
#define WIN32_LEAN_AND_MEAN

//*Header*//
#include <Windows.h>
#include <tchar.h>s

#include <d3D11.h>
#include <DirectXMath.h>

//*using*//
using namespace DirectX;

//*Custom Class*//
#include "Dx11.h"


//*Custom Define*//
template<class T>
void const SAFE_RELEASE(T* x) { x->Release(); x = nullptr; }