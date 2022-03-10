#pragma once
#include "IManager.h"
#include "Container.h"
#include "EGameObject.h"

class GameObjectMgr : public IManager , public Container<EGameObject>
{
public:
	void Init() final;
	void Tick() final;
	void Excute() final;
};