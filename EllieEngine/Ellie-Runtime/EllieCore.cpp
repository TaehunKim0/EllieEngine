#include "Precompiled.h"
#include "EllieCore.h"
#include "IManager.h"
#include "GameObjectMgr.h"


void EllieCore::CreateCores()
{
	m_GameObjectMgr = new GameObjectMgr();
	m_Managers.push_back(m_GameObjectMgr);
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