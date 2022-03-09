#pragma once

#include "IManager.h"
#include "EScene.h"
#include "EllieCore.h"

class SceneMgr : public IManager
{
private:
	EScene* m_Scene = nullptr;

public:
    void SetScene(EScene* scene);
    EScene* GetCurrentScene() const;

public:
	void Init();
	void Tick();
	void Excute();
};