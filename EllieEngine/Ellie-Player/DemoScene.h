#pragma once
#include "EScene.h"

class ESprite;
class ESpriteRendererComponent;
class DemoScene : public EScene
{
private:
	ESprite* m_BackgroundSprite;
	ESpriteRendererComponent* m_SpriteRenderer;

public:
	void Init();
	void Tick();
	void Excute();
	void Destroy();
};