#pragma once

#include "EObject.h"
#include "EGameObject.h"`

class EGameObject;
class EComponent: public EObject
{
private:
	EGameObject* m_RootObject = nullptr;
	bool m_IsEnable = true;
	std::string m_ComponentType;

public:
	EComponent();
	virtual ~EComponent();

public:
	virtual bool Init();		
	virtual void Tick();

public:
	void SetRootObject(EGameObject* object) { m_RootObject = object; }
	virtual void SetIsEnable(bool enable) { m_IsEnable = enable; };
	void SetComponentType(std::string type) { m_ComponentType = type; }

	virtual EGameObject* GetRootComponent() const { return m_RootObject; }
	virtual bool GetIsEnable() const { return m_IsEnable;  }
	std::string GetComponentType() const { return m_ComponentType; }
};