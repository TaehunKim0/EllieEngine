#pragma once

#include <typeinfo>

class EGameObject;
class EComponent
{
public:
	EComponent() {};
	virtual ~EComponent() {};

public:
	virtual bool Init() { return false; };
	virtual void Tick() {};
	virtual void Excute() {};
	virtual void Destroy() {};

public:
	void SetRootObject(EGameObject* object) { _RootObject = object; }
	virtual void SetIsEnable(bool enable) { _bIsEnable = enable; };
	void SetComponentType(std::string type) { _ComponentType = type; }

	virtual EGameObject* GetRootComponent() const { return _RootObject; }
	virtual bool GetIsEnable() const { return _bIsEnable;  }
	const std::string& GetComponentType() const { return _ComponentType; }

private:
	EGameObject* _RootObject = nullptr;
	bool _bIsEnable = true;
	std::string _ComponentType;

};

