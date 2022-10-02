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
    CREATE_GETCORE_FUNCTION(GameObjectMgr, _GameObjectMgr);
    CREATE_GETCORE_FUNCTION(CameraMgr, _CameraMgr);
    CREATE_GETCORE_FUNCTION(SceneMgr, _SceneMgr);

    void CreateCores();
    void Init();
    void Tick();
    void Excute();

private:
    std::vector<IManager*> _Managers;
    GameObjectMgr* _GameObjectMgr = nullptr;
    CameraMgr* _CameraMgr = nullptr;
    SceneMgr* _SceneMgr = nullptr;
};
