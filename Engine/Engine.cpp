#include <iostream>
#include <thread>
#include <chrono>
#include "../Game/Game.h"
#include "Engine.h"

using namespace TEG;
using namespace std;

void Engine::Init()
{
	Input::Initialize();
	cout << "Engine initialized." << endl;
	Game::Start();
}

void Engine::UpdateLoop()
{
	while (Engine::RUNNING)
	{
		Engine::PrintScreen();
		Game::Update();
		this_thread::sleep_for(chrono::milliseconds(30));
	}
	OnStop();
}

void Engine::Stop()
{
	Engine::RUNNING = false;
}

void Engine::OnStop()
{
	system("cls");
	cout << "Engine stopped." << endl;
	Input::Cleanup();
}

void Engine::PrintScreen()
{
	system("cls");
	std::size_t vectorLength = Object::objects.size();
	for (std::size_t i = 0; i < vectorLength; ++i)
	{
		Object::objects[i].get().Render(csbi);
	}
}

std::string Engine::screen = "";
bool Engine::RUNNING = true;
CONSOLE_SCREEN_BUFFER_INFO Engine::csbi = {};
std::mutex Engine::screenMutex;
