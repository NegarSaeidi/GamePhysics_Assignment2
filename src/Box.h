#pragma once
#ifndef __BOX__
#define __BOX__

#include "DisplayObject.h"
#include "TextureManager.h"

class Box final : public DisplayObject
{
public:
	Box();
	~Box();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;

	void turnRight();
	void turnLeft();
	void moveForward();
	void moveBack();
	
	void move();

	// getters
	glm::vec2 getTargetPosition() const;
	glm::vec2 getCurrentDirection() const;
	float getCurrentHeading() const;
	float getMaxSpeed() const;

	// setters
	void setTargetPosition(glm::vec2 newPosition);
	void setCurrentDirection(glm::vec2 newDirection);
	void setCurrentHeading(float newDirection);
	void setMaxSpeed(float newSpeed);

	float getGroundFriction();
	float getRampFriction();
	bool getOnGround();
	bool getActivated();
	void setGroundFriction(float gFriction);
	void setRampFriction(float rFriction);
	void setOnGround(bool tmp);
	void setActivated(bool tmp);
private:
	void m_checkBounds();
	void m_reset();

	// steering behaviours
	float m_maxSpeed;
	float m_turnRate;
	float groundFriction, rampFriction;
	bool onGround;
	bool activated;
	void m_changeDirection();
	float m_currentHeading;
	glm::vec2 m_currentDirection;
	glm::vec2 m_targetPosition;
};


#endif /* defined (__SHIP__) */

