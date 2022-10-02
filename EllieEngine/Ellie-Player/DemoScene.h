#pragma once
#include "EScene.h"
#include "TriangleMesh.h"

class DemoScene : public EScene
{
public:
	void Init() final;
	void Update() final;
	void Render() final;
	void Excute() final;
	void Destroy() final;

private:
	TriangleMesh _Triangle;
	
};