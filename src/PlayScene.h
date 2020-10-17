#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "Box.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;


private:
	// IMGUI Function
	void GUI_Function() ;
	std::string m_guiTitle;
	glm::vec2 vertices[3];
	glm::vec2 m_mousePosition;

	float triangleHeight, triangleWidth;
	bool m_playerFacingRight;
	Box* m_pBox;

	// UI Items

};

#endif /* defined (__PLAY_SCENE__) */