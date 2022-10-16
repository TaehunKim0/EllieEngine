#include "Precompiled.hpp"
#include "EllieProc.hpp"
#include "EllieCore.hpp"

void EllieProc::Init()
{
	CORE.CreateCores();
	CORE.Init();
}

void EllieProc::Tick()
{
	CORE.Tick();
}

void EllieProc::Excute()
{
	CORE.Excute();
}
