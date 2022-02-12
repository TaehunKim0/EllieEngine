#pragma once
#define WIN32_LEAN_AND_MEAN
#define _CRTDBG_MAP_ALLOC

//*Header*//
#include <Windows.h>
#include <tchar.h>
#include <crtdbg.h>
#include <stdlib.h>

#include <d3D11.h>
#include <DirectXMath.h>

#include <string>

//*using*//
using namespace DirectX;

//*Custom Class*//
#include "Dx11.h"


//*Custom Define*//
template<class T>
void const SAFE_RELEASE(T* x) { x->Release(); x = nullptr; }

template<class T>
void const SAFE_DELETE(T* x) {delete x; x = nullptr; }

#ifdef _DEBUG
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#endif
