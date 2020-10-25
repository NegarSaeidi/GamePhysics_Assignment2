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
	bool boxCollision();
	
private:
	// IMGUI Function
	void GUI_Function() ;
	std::string m_guiTitle;
	glm::vec2 vertices[3];
	glm::vec2 m_mousePosition;
	bool activateButton;
	float triangleHeight, triangleWidth;
	float groundFriction, rampFriction, mass;
	bool m_playerFacingRight;
	Box* m_pBox;
	Label* staticKey[5];
	std::string xPosStr;
	std::string yPosStr;
	std::string velMagStr;
	std::string fForceStr;
	std::string GForceStr;
	float xPos;
	float yPos;
	float velMag;
	float frictionForce;
	float GfrictionForce;
	// UI Items

};

#endif /* defined (__PLAY_SCENE__) */