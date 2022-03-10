#pragma once
#include "EScene.h"

class ESprite;
class ESpriteRendererComponent;
class DemoScene : public EScene
{
public:
	void Init() final;
	void Tick() final;
	void Excute() final;
	void Destroy() final;

private:
	ESprite* m_BackgroundSprite;
	ESpriteRendererComponent* m_SpriteRenderer;
};