#include "Precompiled.hpp"
#include "GameObjectMgr.hpp"

void GameObjectMgr::Init()
{

}

void GameObjectMgr::Tick()
{
    auto iterator = _Objects.begin();
    while (iterator != _Objects.end())
    {
        iterator->Update();
        ++iterator;

        //만약 오브젝트가 삭제되어야 한다면 삭제한다.
        //if(object->GetStatus() == STATUS.DESTROY)
        //object->Destroy();
    }

}

void GameObjectMgr::Excute()
{
}
