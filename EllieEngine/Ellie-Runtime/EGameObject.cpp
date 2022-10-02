#include "Precompiled.h"
#include "EGameObject.h"
#include "EComponent.h"


EGameObject::EGameObject()
    : _bIsEnable(true),
    _bIsPendingKill(false),
    _Parent(nullptr)
{
}

EGameObject::~EGameObject()
{
}

void EGameObject::Begin()
{
}

void EGameObject::Update()
{
    if (false == _bIsEnable)
        return;

    for (const auto& component : _Components) {
        if (component == nullptr) continue;

        if (component->GetIsEnable())
            component->Tick();
    }
}

void EGameObject::AddChild(EGameObject* child)
{
    if (nullptr == child)
        return;
    _Children.push_back(child);
    child->_Parent = this;
}

void EGameObject::RemoveChild(EGameObject* child)
{
    if (nullptr == child)
        return;
    _Children.remove(child);
    child->_Parent = nullptr;
}

void EGameObject::RemoveChildren()
{
    _Children.clear();
}

void EGameObject::SetParent(EGameObject* parent)
{
    parent->AddChild(this);
}

EGameObject* EGameObject::GetParent()
{   
    return _Parent;
}

void EGameObject::RemoveParent()
{
    _Parent = nullptr;
}

void EGameObject::AddComponent(EComponent* component)
{
    _Components.push_back(component);
    component->SetRootObject(this);
}

void EGameObject::DeleteComponent(EComponent* component)
{
    _Components.remove(component);
}

bool EGameObject::InitializeComponent()
{
    for (const auto& component : _Components)
    {
        if (component->Init() == false)
            return false;
    }

    return true;
}

void EGameObject::Excute()
{

}

void EGameObject::Destroy()
{
}

void EGameObject::SetIsEnable(bool enable)
{
    _bIsEnable = enable;

    for (const auto& child : _Components)
    {
        if (nullptr == child) continue;
        child->SetIsEnable(_bIsEnable);
    }
}