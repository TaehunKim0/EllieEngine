#pragma once
#include "IManager.h"
class CameraMgr : public IManager
{
public:
	void Init() final;
	void Tick() final;
	void Excute() final;
};