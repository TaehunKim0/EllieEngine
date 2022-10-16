#include "Precompiled.hpp"
#include "EllieCore.hpp"

#include "IManager.hpp"
#include "GameObjectMgr.hpp"
#include "CameraMgr.hpp"
#include "SceneMgr.hpp"

void EllieCore::CreateCores()
{
	//���� ������Ʈ ����
	_GameObjectMgr = new GameObjectMgr();
	_Managers.push_back(_GameObjectMgr);

	//ī�޶� ����
	_CameraMgr = new CameraMgr();
	_Managers.push_back(_CameraMgr);
	
	//�� ����
	_SceneMgr = new SceneMgr();
	_Managers.push_back(_SceneMgr);

}

void EllieCore::Init()
{
	for (const auto& core : _Managers)
		core->Init();
}

void EllieCore::Tick()
{
	for (const auto& core : _Managers)
		core->Tick();
}

void EllieCore::Excute()
{
	for (const auto& core : _Managers)
		core->Excute();
}