#include "Precompiled.h"
#include "EGameObject.h"
#include "EComponent.h"


EGameObject::EGameObject()
    : m_bIsEnable(true),
    m_bIsPendingKill(false),
    m_Parent(nullptr)
{
}

EGameObject::~EGameObject()
{
}

void EGameObject::Begin()
{
}

void EGameObject::Tick()
{
    if (false == m_bIsEnable)
        return;

    for (const auto& component : m_Components) {
        if (component == nullptr) continue;

        if (component->GetIsEnable())
            component->Tick();
    }
}

void EGameObject::AddChild(EGameObject* child)
{
    if (nullptr == child)
        return;
    m_Children.push_back(child);
    child->m_Parent = this;
}

void EGameObject::RemoveChild(EGameObject* child)
{
    if (nullptr == child)
        return;
    m_Children.remove(child);
    child->m_Parent = nullptr;
}

void EGameObject::RemoveChildren()
{
    m_Children.clear();
}

void EGameObject::SetParent(EGameObject* parent)
{
    parent->AddChild(this);
}

EGameObject* EGameObject::GetParent()
{   
    return m_Parent;
}

void EGameObject::RemoveParent()
{
    m_Parent = nullptr;
}

void EGameObject::AddComponent(EComponent* component)
{
    m_Components.push_back(component);
    component->SetRootObject(this);
}

void EGameObject::DeleteComponent(EComponent* component)
{
    m_Components.remove(component);
}

bool EGameObject::InitializeComponent()
{
    for (const auto& component : m_Components)
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
    m_bIsEnable = enable;

    for (const auto& child : m_Components)
    {
        if (nullptr == child) continue;
        child->SetIsEnable(m_bIsEnable);
    }
}