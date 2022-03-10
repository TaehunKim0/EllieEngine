#include "PreCompiled.h"
#include "DemoObject.h"
#include "PreCompiled.h"
#include "DemoObject.h"

#include "ESprite.h"
#include "SpriteRendererComponent.h"

void DemoObject::Begin()
{
	m_BackgroundSprite = new ESprite;
	m_BackgroundSprite->CreateTexture(DX11.GetDevice(), TEXT("../Resource/BackGround.png"));

	m_SpriteRenderer = CreateComponent<ESpriteRendererComponent>();
	m_SpriteRenderer->SetSprite(m_BackgroundSprite);
}

void DemoObject::Tick()
{
	EGameObject::Tick();
}

void DemoObject::Excute()
{
	EGameObject::Excute();
}

void DemoObject::Destroy()
{
}