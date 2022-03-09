#pragma once
#include "IManager.h"
class CameraMgr : public IManager
{
public:
	void Init();
	void Tick();
	void Excute();
};