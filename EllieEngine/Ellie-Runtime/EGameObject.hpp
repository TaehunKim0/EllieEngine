#pragma once
#include<list>

class EComponent;
class EGameObject
{
public:
	EGameObject();
	~EGameObject();

	virtual void Begin();
	virtual void Update();

	virtual void Excute();
	virtual void Destroy();

public:
	void AddChild(EGameObject* child);
	void RemoveChild(EGameObject* child);
	void RemoveChildren();

	void SetParent(EGameObject* parent);
	EGameObject* GetParent();
	void RemoveParent();

public:
	virtual void SetIsEnable(bool enable);

public:
	void AddComponent(EComponent* component);
	void DeleteComponent(EComponent* component);

	template<class T>
	T* GetComponent();
	template<class T>
	T* CreateComponent();

	bool InitializeComponent();

private:
	bool _bIsPendingKill;
	bool _bIsEnable;

private:
	std::list<EGameObject*> _Children;
	EGameObject* _Parent = nullptr;

	std::list<EComponent*> _Components;
};

template<class T>
inline T* EGameObject::GetComponent()
{
	for (const auto component : _Components)
	{
		if (nullptr == component) continue;
		if (dynamic_cast<T*>(component)) //��ĳ���� ��� (��ĳ���� : �ڽ� Ŭ������ ��ü�� �θ� Ŭ���� Ÿ������ ����ȯ �Ǵ� ��)
			//���̳������� �˻� �� �����ϸ� �ӵ��� ���� ����ƽ ĳ��Ʈ�� ��ȯ�Ѵ�. //Ÿ���� ���� Ŭ������ �����ϰ�, �ٸ� Ŭ������ �Ұ����ϴ�
		{
			return static_cast<T*>(component); //��, �ٿ� ĳ���� ��� (�ٿ�ĳ���� : ��ĳ���� �Ȱ��� �ٽ� �����·� ������ ��)
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