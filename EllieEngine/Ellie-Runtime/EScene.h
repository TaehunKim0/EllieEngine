#pragma once
#include "EGameObject.h"

class EScene : public EGameObject
{
public:
	EScene() = default;
	~EScene() = default;

public:
	virtual void Init() = 0;
	virtual void Tick() = 0;

	void Excute() override = 0;
	void Destroy() override = 0;

public:
	const std::string& GetName() {
		return m_Name;
	}
	void SetName(const std::string& name) {
		m_Name = name;
	}

private:
	std::string m_Name;
};

