#pragma once
#include "EGameObject.h"

class EScene : public EGameObject
{
public:
	EScene() = default;
	~EScene() = default;

public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	void Excute() override = 0;
	void Destroy() override = 0;

public:
	const std::string& GetName() {
		return _Name;
	}
	void SetName(const std::string& name) {
		_Name = name;
	}

private:
	std::string _Name;
};

