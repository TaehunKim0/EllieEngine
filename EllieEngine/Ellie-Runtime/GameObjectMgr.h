#pragma once
#include "IManager.h"
#include "Container.h"
#include "EGameObject.h"

class GameObjectMgr : public IManager , public Container<EGameObject>
{
private:

public:
	void Init();
	void Tick();
	void Excute();
};