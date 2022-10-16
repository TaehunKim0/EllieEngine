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

        //���� ������Ʈ�� �����Ǿ�� �Ѵٸ� �����Ѵ�.
        //if(object->GetStatus() == STATUS.DESTROY)
        //object->Destroy();
    }

}

void GameObjectMgr::Excute()
{
}
