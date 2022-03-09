#include "Precompiled.h"
#include "SceneMgr.h"

void SceneMgr::Init()
{
	if (m_Scene == nullptr)
		return;

	m_Scene->Init();
}

void SceneMgr::Tick()
{
	if (m_Scene == nullptr)
		return;

	m_Scene->Tick();
}

void SceneMgr::Excute()
{
	m_Scene->Excute();
}

void SceneMgr::SetScene(EScene* scene)
{
    m_Scene = scene;

    if (m_Scene != nullptr)
        m_Scene->Init();
}

EScene* SceneMgr::GetCurrentScene() const
{
	return m_Scene;
}