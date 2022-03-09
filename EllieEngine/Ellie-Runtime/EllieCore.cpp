#include "Precompiled.h"
#include "EllieCore.h"

#include "IManager.h"
#include "GameObjectMgr.h"
#include "CameraMgr.h"
#include "SceneMgr.h"

void EllieCore::CreateCores()
{
	//게임 오브젝트 관리
	m_GameObjectMgr = new GameObjectMgr();
	m_Managers.push_back(m_GameObjectMgr);

	//카메라 관리
	m_CameraMgr = new CameraMgr();
	m_Managers.push_back(m_CameraMgr);
	
	//씬 관리
	m_SceneMgr = new SceneMgr();
	m_Managers.push_back(m_SceneMgr);

}

void EllieCore::Init()
{
	for (const auto& core : m_Managers)
		core->Init();
}

void EllieCore::Tick()
{
	for (const auto& core : m_Managers)
		core->Tick();
}

void EllieCore::Excute()
{
	for (const auto& core : m_Managers)
		core->Excute();
}