#pragma once
#include "EScene.hpp"
#include "TriangleMesh.hpp"

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