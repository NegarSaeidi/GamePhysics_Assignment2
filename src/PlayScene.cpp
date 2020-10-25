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
	}

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
//	SoundManager::Instance().playMusic("playscene", -1);
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

