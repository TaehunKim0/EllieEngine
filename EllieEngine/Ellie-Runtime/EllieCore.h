#pragma once
#include "Singleton.h"
/*
Manager 들을 가지고 있는 Core 클래스
Manager들을 List에 추가하고,
Manager-> Init, Tick 수행

WindowsApp의 Tick 안에서 Core Tick 수행
*/

#include <vector>

#define GetCore(CORENAME) Get##CORENAME##Core()

#define CREATE_GETCORE_FUNCTION(CORENAME, core_instance)  \
CORENAME* Get##CORENAME##Core() const {               \
    return static_cast<CORENAME*>(core_instance);   \
}

#define CORE EllieCore::GetInstance()

class IManager;
class GameObjectMgr;
class CameraMgr;
class SceneMgr;
class EllieCore : public Singleton<EllieCore>
{
public:
    CREATE_GETCORE_FUNCTION(GameObjectMgr, m_GameObjectMgr);
    CREATE_GETCORE_FUNCTION(CameraMgr, m_CameraMgr);
    CREATE_GETCORE_FUNCTION(SceneMgr, m_SceneMgr);

    void CreateCores();
    void Init();
    void Tick();
    void Excute();

private:
    std::vector<IManager*> m_Managers;
    GameObjectMgr* m_GameObjectMgr = nullptr;
    CameraMgr* m_CameraMgr = nullptr;
    SceneMgr* m_SceneMgr = nullptr;
};
