#pragma once

#include "EObject.h"
#include <typeinfo>

class EGameObject;
class EComponent: public EObject
{
public:
	EComponent();
	virtual ~EComponent();

public:
	virtual bool Init();
	virtual void Tick();

public:
	void SetRootObject(EGameObject* object) { m_RootObject = object; }
	virtual void SetIsEnable(bool enable) { m_bIsEnable = enable; };
	void SetComponentType(std::string type) { m_ComponentType = type; }

	virtual EGameObject* GetRootComponent() const { return m_RootObject; }
	virtual bool GetIsEnable() const { return m_bIsEnable;  }
	const std::string& GetComponentType() const { return m_ComponentType; }

private:
	EGameObject* m_RootObject = nullptr;
	bool m_bIsEnable = true;
	std::string m_ComponentType;

};

