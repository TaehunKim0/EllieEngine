#include "Precompiled.h"
#include "EGameObject.h"

EGameObject::EGameObject()
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
    if (false == m_IsEnable)
        return;
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
    m_IsEnable = enable;

    for (const auto& child : m_Components)
    {
        if (nullptr == child) continue;
        child->SetIsEnable(m_IsEnable);
    }
}