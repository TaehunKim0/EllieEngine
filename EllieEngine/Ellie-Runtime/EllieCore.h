#pragma once
#include "Singleton.h"
/*
Manager ���� ������ �ִ� Core Ŭ����
Manager���� List�� �߰��ϰ�,
Manager-> Init, Tick ����

WindowsApp�� Tick �ȿ��� Core Tick ����
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
class EllieCore : public Singleton<EllieCore>
{
public:
    CREATE_GETCORE_FUNCTION(GameObjectMgr, m_GameObjectMgr);

    void CreateCores();
    void Init();
    void Tick();
    void Excute();

private:
    std::vector<IManager*> m_Managers;
    GameObjectMgr* m_GameObjectMgr = nullptr;
};
