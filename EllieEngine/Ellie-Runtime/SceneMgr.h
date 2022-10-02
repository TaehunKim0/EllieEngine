#pragma once

#include "IManager.h"
#include "EScene.h"
#include "EllieCore.h"

class SceneMgr : public IManager
{
public:
	void Init() final;
	void Tick() final;
	void Excute() final;

public:
	void SetScene(EScene* scene);
	EScene* GetCurrentScene() const;

private:
	EScene* _Scene;
};