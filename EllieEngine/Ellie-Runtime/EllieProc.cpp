#include "Precompiled.h"
#include "EllieProc.h"
#include "EllieCore.h"

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
