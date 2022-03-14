#include "Precompiled.h"
#include "DemoScene.h"
#include "ESprite.h"
#include "SpriteRendererComponent.h"

void DemoScene::Init()
{
	m_BackgroundSprite = new ESprite;
	m_BackgroundSprite->CreateTexture(DX11.GetDevice() , TEXT("../Resource/BackGround.png"));
	
	m_SpriteRenderer = CreateComponent<ESpriteRendererComponent>();
	m_SpriteRenderer->Init();
	m_SpriteRenderer->SetSprite(m_BackgroundSprite);
}

void DemoScene::Tick()
{
	m_SpriteRenderer->Render();
}

void DemoScene::Excute()
{
	EGameObject::Excute();
}

void DemoScene::Destroy()
{
	EGameObject::Destroy();
}