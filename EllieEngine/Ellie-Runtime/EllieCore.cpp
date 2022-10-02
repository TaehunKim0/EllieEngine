#include "Precompiled.h"
#include "EllieCore.h"

#include "IManager.h"
#include "GameObjectMgr.h"
#include "CameraMgr.h"
#include "SceneMgr.h"

void EllieCore::CreateCores()
{
	//게임 오브젝트 관리
	_GameObjectMgr = new GameObjectMgr();
	_Managers.push_back(_GameObjectMgr);

	//카메라 관리
	_CameraMgr = new CameraMgr();
	_Managers.push_back(_CameraMgr);
	
	//씬 관리
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