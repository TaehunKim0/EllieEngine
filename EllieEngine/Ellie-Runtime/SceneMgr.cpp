#include "Precompiled.h"
#include "SceneMgr.h"

void SceneMgr::Init()
{
	if (_Scene == nullptr)
		return;

	_Scene->Init();
}

void SceneMgr::Tick()
{
	if (_Scene == nullptr)
		return;

	_Scene->Update();
	_Scene->Render();
}

void SceneMgr::Excute()
{
	_Scene->Excute();
}

void SceneMgr::SetScene(EScene* scene)
{
    _Scene = scene;

    if (_Scene != nullptr)
        _Scene->Init();
}

EScene* SceneMgr::GetCurrentScene() const
{
	return _Scene;
}