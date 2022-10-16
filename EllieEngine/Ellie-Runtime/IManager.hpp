#pragma once

class IManager
{
public:
	IManager() = default;
	virtual ~IManager() = default;

public:
	virtual void Init() = 0;
	virtual void Tick() = 0;
	virtual void Excute() = 0;
};