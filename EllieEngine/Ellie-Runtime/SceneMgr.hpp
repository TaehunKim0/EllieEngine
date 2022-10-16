#pragma once

#include "IManager.hpp"
#include "EScene.hpp"
#include "EllieCore.hpp"

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