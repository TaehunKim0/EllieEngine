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

        //만약 오브젝트가 삭제되어야 한다면 삭제한다.
        //if(object->GetStatus() == STATUS.DESTROY)
        //object->Destroy();
    }

}

void GameObjectMgr::Excute()
{
}
