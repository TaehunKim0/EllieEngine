#include "Precompiled.h"
#include "GameObjectMgr.h"

void GameObjectMgr::Init()
{

}

void GameObjectMgr::Tick()
{
    auto iterator = m_Objects.begin();
    while (iterator != m_Objects.end())
    {
        iterator->Tick();
        ++iterator;

        //���� ������Ʈ�� �����Ǿ�� �Ѵٸ� �����Ѵ�.
        //if(object->GetStatus() == STATUS.DESTROY)
        //object->Destroy();
    }

}

void GameObjectMgr::Excute()
{
}
