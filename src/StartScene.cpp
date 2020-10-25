#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	TextureManager::Instance()->load("../Assets/textures/startscene.png", "background");
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	TextureManager::Instance()->draw("background", 0, 0, 0, 255, false, SDL_FLIP_NONE);
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{
	const SDL_Color black= { 0, 0, 0, 255 };
	m_pNameLabel[0] = new Label("Negar Saeidi", "Consolas", 15, black, glm::vec2(518.0f, 232.0f));
	m_pNameLabel[0]->setParent(this);
	addChild(m_pNameLabel[0]);

	m_pNameLabel[1] = new Label("Negin Saeidi", "Consolas", 15, black, glm::vec2(385.0f, 265.0f));
	m_pNameLabel[1]->setParent(this);
	addChild(m_pNameLabel[1]);

	m_pNameLabel[1] = new Label("Mehrara Sarabi", "Consolas", 15, black, glm::vec2(560.0f, 132.0f));
	m_pNameLabel[1]->setParent(this);
	addChild(m_pNameLabel[1]);

	m_pIDLabel[0] = new Label("101261396", "Consolas", 12, black, glm::vec2(500.0f, 250.0f));
	m_pIDLabel[0]->setParent(this);
	addChild(m_pIDLabel[0]);

	m_pIDLabel[1] = new Label("101261395", "Consolas", 12, black, glm::vec2(366.0f, 285.0f));
	m_pIDLabel[1]->setParent(this);
	addChild(m_pIDLabel[1]);

	m_pIDLabel[1] = new Label("101247463", "Consolas", 12, black, glm::vec2(535.0f, 150.0f));
	m_pIDLabel[1]->setParent(this);
	addChild(m_pIDLabel[1]);

	


	
	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->getTransform()->position = glm::vec2(242.0f, 160.0f); 

	m_pStartButton->addEventListener(CLICK, [&]()-> void
	{
			//SoundManager::Instance().playSound("click", 0);
		m_pStartButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});
	
	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pStartButton->setAlpha(128);
	});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pStartButton->setAlpha(255);
	});
	addChild(m_pStartButton);

	
}

