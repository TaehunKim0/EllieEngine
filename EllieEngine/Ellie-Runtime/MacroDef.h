#pragma once

//*Custom Define*//
template<class T>
void const SAFE_RELEASE(T* x) { x->Release(); x = nullptr; }

template<class T>
void const SAFE_DELETE(T* x) { delete x; x = nullptr; }

#ifdef _DEBUG
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#endif
