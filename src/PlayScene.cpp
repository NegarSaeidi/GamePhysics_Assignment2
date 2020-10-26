#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "Util.h"
// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "CollisionManager.h"


#define PI 3.14159265
const int PPM = 50;

PlayScene::PlayScene() : rampFriction(0), groundFriction(0.42), mass(12.8), activateButton(false)
{
	TextureManager::Instance()->load("../Assets/textures/background.png", "background");
	vertices[0] = glm::vec2(92, 570);
	vertices[1] = glm::vec2(292, 570);
	vertices[2] = glm::vec2(92, 420);
	PlayScene::start();
	xPos = 112;
	yPos = 410;
	velMag =0.0f;
	frictionForce = 0.0f;
	GfrictionForce = groundFriction * 9.8 * mass;

	xPosStr = std::to_string(xPos);
	yPosStr = std::to_string(yPos);
	velMagStr = std::to_string(velMag);
	fForceStr = std::to_string(frictionForce);
	GForceStr = std::to_string(GfrictionForce);

	staticKey[0] = new Label("X Position: " + xPosStr, "Consolas", 18, { 179,45,0,255 }, glm::vec2(640.0f, 20.0f));
	staticKey[0]->setParent(this);
	addChild(staticKey[0]);
	staticKey[1] = new Label("Y Position: " + yPosStr, "Consolas", 18, { 179,45,0,255 }, glm::vec2(640.0f, 40.0f));
	staticKey[1]->setParent(this);
	addChild(staticKey[1]);
	staticKey[2] = new Label("Magnitude Velocity: " + velMagStr, "Consolas", 18, { 179,45,0,255 }, glm::vec2(640.0f, 60.0f));
	staticKey[2]->setParent(this);
	addChild(staticKey[2]);
	staticKey[3] = new Label("Ramp's Friction force: " + fForceStr, "Consolas", 18, {179,45,0,255 }, glm::vec2(640.0f, 80.0f));
	staticKey[3]->setParent(this);
	addChild(staticKey[3]);
	staticKey[4] = new Label("Ground's Friction force: " + GForceStr, "Consolas", 18, { 179,45,0,255 }, glm::vec2(640.0f, 100.0f));
	staticKey[4]->setParent(this);
	addChild(staticKey[4]);

	
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance()->draw("background", 0, 0, 0, 255, false, SDL_FLIP_NONE);

	Util::DrawLine(vertices[0], vertices[1]);
	Util::DrawLine(vertices[2], vertices[0]);
	Util::DrawLine(vertices[2], vertices[1]);
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
		xPos = m_pBox->getTransform()->position.x;
		yPos = m_pBox->getTransform()->position.y;
		velMag = Util::magnitude(m_pBox->getRigidBody()->velocity);
		frictionForce = m_pBox->getRigidBody()->mass * rampFriction * 9.8f * cos(Util::Deg2Rad * m_pBox->getCurrentHeading());
		GfrictionForce = groundFriction * 9.8 * mass;
		xPosStr = std::to_string(xPos);
		yPosStr = std::to_string(yPos);
		velMagStr = std::to_string(velMag);
		fForceStr = std::to_string(frictionForce);
		GForceStr = std::to_string(GfrictionForce);
	}
	
	staticKey[0]->setText("X Position: " + xPosStr );
	staticKey[1]->setText("Y Position: " + yPosStr);
	staticKey[2]->setText("Magnitude Velocity: " + velMagStr);
	staticKey[3]->setText("Ramp's Friction force: " + fForceStr);
	staticKey[4]->setText("Ground's Friction force: " + GForceStr);

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	if (boxCollision())
	{
		m_pBox->setOnGround(true);
		m_pBox->setCurrentHeading(0.0f);
	}
	updateDisplayList();
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	SoundManager::Instance().playMusic("playscene", -1);
	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	
	m_pBox = new Box();
	addChild(m_pBox);
	triangleHeight = -(vertices[2].y - vertices[0].y) / PPM;
	triangleWidth = (vertices[1].x - vertices[0].x) / PPM;
	float x = vertices[0].x;
	float y = vertices[0].y - (triangleHeight * PPM);
	vertices[2] = glm::vec2(x, y);
	x = vertices[0].x + (triangleWidth * PPM);
	y = vertices[0].y;
	vertices[1] = glm::vec2(x, y);
	m_pBox->setCurrentHeading(180 / PI * atan((vertices[0].y - vertices[2].y) / (vertices[1].x - vertices[0].x)));
	m_pBox->getTransform()->position = glm::vec2(vertices[2].x + 20, vertices[2].y - 10);

}
bool PlayScene::boxCollision()
{
	return CollisionManager::lineRectCheck(glm::vec2(0, vertices[1].y), glm::vec2(800, vertices[1].y), m_pBox->getTransform()->position, 20,20);
}
void PlayScene::GUI_Function() 
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if(ImGui::Button("Activate"))
	{
		std::cout << "Activated" << std::endl;
		m_pBox->setActivated(true);
		activateButton = true;

	}
	ImGui::SameLine();
	if (ImGui::Button("Reset"))
	{
		activateButton = false;
		mass = 12.8;
		groundFriction = 0.42;
		rampFriction = 0.0;
		vertices[0] = glm::vec2(92, 570);
		vertices[1] = glm::vec2(292, 570);
		vertices[2] = glm::vec2(92, 420);
		m_pBox->getTransform()->position = glm::vec2(vertices[2].x + 20, vertices[2].y - 10);
		m_pBox->setActivated(false);
		m_pBox->setOnGround(false);
		m_pBox->getRigidBody()->velocity= glm::vec2(0.0f, 0.0f);
		m_pBox->setRampFriction(rampFriction);
		m_pBox->setGroundFriction(groundFriction);
		m_pBox->getRigidBody()->mass = mass;
	}
	ImGui::Separator();

	triangleHeight = -(vertices[2].y-vertices[0].y)/PPM;
	triangleWidth = (vertices[1].x - vertices[0].x)/PPM;
	
	if(ImGui::SliderFloat("Ramp's Height", &triangleHeight, 50.0f/PPM, 300.0f/PPM))
	{
		float x = vertices[0].x;
		float y= vertices[0].y - (triangleHeight*PPM);
		vertices[2] = glm::vec2(x, y);
	}

	if (ImGui::SliderFloat("Ramp's Width", &triangleWidth, 50.0f/PPM, 300.0f/PPM))
	{
		float x = vertices[0].x+ (triangleWidth*PPM);
		float y = vertices[0].y ;
		vertices[1] = glm::vec2(x , y );
	}
	if(!activateButton)
	m_pBox->getTransform()->position = glm::vec2(vertices[2].x+20, vertices[2].y-10 );
	if (ImGui::SliderFloat("Ramp's Coefficient of Friction", &rampFriction, 0.0f, 1.0f))
	{
		m_pBox->setRampFriction(rampFriction);
	}
	if (ImGui::SliderFloat("Ground's Coefficient of Friction", &groundFriction, 0.0f, 1.0f))
	{
		m_pBox->setGroundFriction(groundFriction);
	}
	if (ImGui::SliderFloat("Mass", &mass, 0.0f, 20.0f))
	{
		m_pBox->getRigidBody()->mass = mass;
	}
	if(!activateButton)
	m_pBox->setCurrentHeading(180 / PI* atan((vertices[0].y-vertices[2].y)/(vertices[1].x-vertices[0].x)));
	
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}

