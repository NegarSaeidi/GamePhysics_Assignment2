#include "Box.h"
#include "glm/gtx/string_cast.hpp"
#include "PlayScene.h"
#include "TextureManager.h"
#include "Util.h"

Box::Box() : m_maxSpeed(10.0f), rampFriction(0), groundFriction(0.42)
{
	TextureManager::Instance()->load("../Assets/textures/box.png","box");

	auto size = TextureManager::Instance()->getTextureSize("box");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(SHIP);
	
	m_currentHeading = 20.0f; // current facing angle
	m_currentDirection = glm::vec2(1.0f, 0.0f); // facing right
	m_turnRate = 5.0f; // 5 degrees per frame
}


Box::~Box()
= default;

void Box::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the ship
	TextureManager::Instance()->draw("box", x, y, m_currentHeading, 255, true);
}


void Box::update()
{
	move();
	m_checkBounds();
}

void Box::clean()
{
}

void Box::turnRight()
{
	m_currentHeading += m_turnRate;
	if (m_currentHeading >= 360) 
	{
		m_currentHeading -= 360.0f;
	}
	m_changeDirection();
}

void Box::turnLeft()
{
	m_currentHeading -= m_turnRate;
	if (m_currentHeading < 0)
	{
		m_currentHeading += 360.0f;
	}

	m_changeDirection();
}

void Box::moveForward()
{
	getRigidBody()->velocity = m_currentDirection * m_maxSpeed;
}

void Box::moveBack()
{
	getRigidBody()->velocity = m_currentDirection * -m_maxSpeed;
}

void Box::move()
{
	getTransform()->position += getRigidBody()->velocity;
	getRigidBody()->velocity *= 0.9f;
}

glm::vec2 Box::getTargetPosition() const
{
	return m_targetPosition;
}

glm::vec2 Box::getCurrentDirection() const
{
	return m_currentDirection;
}

float Box::getMaxSpeed() const
{
	return m_maxSpeed;
}

void Box::setTargetPosition(glm::vec2 newPosition)
{
	m_targetPosition = newPosition;

}

void Box::setCurrentDirection(glm::vec2 newDirection)
{
	m_currentDirection = newDirection;
}

void Box::setCurrentHeading(float newDirection)
{
	m_currentHeading = newDirection;
}

void Box::setMaxSpeed(float newSpeed)
{
	m_maxSpeed = newSpeed;
}



void Box::m_checkBounds()
{

	if (getTransform()->position.x > Config::SCREEN_WIDTH)
	{
		getTransform()->position = glm::vec2(0.0f, getTransform()->position.y);
	}

	if (getTransform()->position.x < 0)
	{
		getTransform()->position = glm::vec2(800.0f, getTransform()->position.y);
	}

	if (getTransform()->position.y > Config::SCREEN_HEIGHT)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 0.0f);
	}

	if (getTransform()->position.y < 0)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 600.0f);
	}

}

void Box::m_reset()
{
	getRigidBody()->isColliding = false;
	const int halfWidth = getWidth() * 0.5f;
	const auto xComponent = rand() % (640 - getWidth()) + halfWidth + 1;
	const auto yComponent = -getHeight();
	getTransform()->position = glm::vec2(xComponent, yComponent);
}

void Box::m_changeDirection()
{
	const auto x = cos(m_currentHeading * Util::Deg2Rad);
	const auto y = sin(m_currentHeading * Util::Deg2Rad);
	m_currentDirection = glm::vec2(x, y);

	glm::vec2 size = TextureManager::Instance()->getTextureSize("ship");
}
void Box::setRampFriction(float rFriction)
{
	rampFriction = rFriction;
}
void Box::setGroundFriction(float gFriction)
{
	groundFriction = gFriction;
}
float Box::getGroundFriction()
{
	return groundFriction;
}
float Box::getRampFriction()
{
	return rampFriction;
}