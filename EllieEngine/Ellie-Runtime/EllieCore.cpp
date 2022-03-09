#include "Precompiled.h"
#include "EllieCore.h"

#include "IManager.h"
#include "GameObjectMgr.h"
#include "CameraMgr.h"
#include "SceneMgr.h"

void EllieCore::CreateCores()
{
	//���� ������Ʈ ����
	m_GameObjectMgr = new GameObjectMgr();
	m_Managers.push_back(m_GameObjectMgr);

	//ī�޶� ����
	m_CameraMgr = new CameraMgr();
	m_Managers.push_back(m_CameraMgr);
	
	//�� ����
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