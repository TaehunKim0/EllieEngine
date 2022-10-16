#pragma once
#include "IManager.hpp"
#include "Container.hpp"
#include "EGameObject.hpp"

class GameObjectMgr : public IManager , public Container<EGameObject>
{
public:
	void Init() final;
	void Tick() final;
	void Excute() final;
};