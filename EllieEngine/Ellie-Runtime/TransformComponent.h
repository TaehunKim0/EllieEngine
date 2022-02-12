#pragma once
#include "EComponent.h"

class ETransformComponent : public EComponent
{
private:
	

public:
	ETransformComponent();
	virtual ~ETransformComponent();

public:
	bool Init() override;
	void Tick() override;
	void Excute() override;

public:
	
};