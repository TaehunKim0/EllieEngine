#pragma once

#include "EGameObject.h"

class ESprite;
class ESpriteRendererComponent;
class DemoObject : public EGameObject
{
public:
	void Begin() final;
	void Update() final;

	void Excute() final;
	void Destroy() final;

private:
	ESprite* m_BackgroundSprite;
	ESpriteRendererComponent* m_SpriteRenderer;
};