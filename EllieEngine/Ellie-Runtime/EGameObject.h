#pragma once
#include<list>
#include "EObject.h"
#include "EComponent.h"

class EComponent;
class EGameObject : public EObject
{
private:
	std::list<EGameObject*> m_Children;
	EGameObject* m_Parent = nullptr;

	std::list<EComponent*> m_Components;

private:
	bool m_IsPendingKill = false;
	bool m_IsEnable = true;

public:
	EGameObject();
	~EGameObject();

	virtual void Begin();
	virtual void Update();

public:
	void AddChild(EGameObject* child);
	void RemoveChild(EGameObject* child);
	void RemoveChildren();

	void SetParent(EGameObject* parent);
	EGameObject* GetParent();
	void RemoveParent();

public:
	void AddComponent(EComponent* component);
	void DeleteComponent(EComponent* component);

	template<class T>
	T* GetComponent();
	template<class T>
	T* CreateComponent();

	bool InitializeComponent();

public:
	virtual void Excute() override;
	virtual void Destroy();

public:
	virtual void SetIsEnable(bool enable);
};

template<class T>
inline T* EGameObject::GetComponent()
{
	for (const auto component : m_Components)
	{
		if (nullptr == component) continue;
		if (dynamic_cast<T*>(component)) //업캐스팅 허용 (업캐스팅 : 자식 클래스의 객체가 부모 클래스 타입으로 형변환 되는 것)
			//다이나믹으로 검사 후 성공하면 속도가 빠른 스태틱 캐스트로 반환한다. //타입이 같은 클래스도 성공하고, 다른 클래스는 불가능하다
		{
			return static_cast<T*>(component); //업, 다운 캐스팅 허용 (다운캐스팅 : 업캐스팅 된것을 다시 원상태로 돌리는 것)
		}
	}

	return nullptr;
}

template<class T>
inline T* EGameObject::CreateComponent()
{
	T* component = new T();
	AddComponent(component);
	return component;
}