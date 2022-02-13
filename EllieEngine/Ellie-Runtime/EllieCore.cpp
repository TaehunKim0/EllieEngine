#include "Precompiled.h"
#include "EllieCore.h"

EllieCore::EllieCore()
{
}

EllieCore::~EllieCore()
{
}

void EllieCore::Init()
{
	for (const auto& core : m_Managers)
		core->Init();
}

void EllieCore::Tick()
{
	for (const auto& core : m_Managers)
		core->Tick();
}

void EllieCore::Excute()
{
	for (const auto& core : m_Managers)
		core->Excute();
}
