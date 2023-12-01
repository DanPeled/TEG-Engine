#include <iostream>
#include <thread>
#include "Engine.h"
#include "../Game/Game.h"
int Engine::ticks = 0;
int Engine::frames = 0;
high_resolution_clock::time_point Engine::lastTime;
double Engine::lastFPS = 0;
Game game;
std::vector<std::reference_wrapper<TEG::Object>> TEG::Object::objects = {};
std::vector<Log> Engine::logs;
void Engine::Init(Game game_)
{
	logs = {};
	game = game_;
	Input::Initialize();
	cout << "Engine initialized." << endl;
	game.Start();
	lastTime = high_resolution_clock::now();
}

void Engine::UpdateLoop()
{
	while (Engine::RUNNING)
	{
		ticks += 1;
		frames += 1;
		Engine::PrintScreen();
		game.Update();
		this_thread::sleep_for(chrono::milliseconds(22));
	}
	OnStop();
}

void Engine::Stop()
{
	Engine::RUNNING = false;
}

void Engine::OnStop()
{
	game.Exit();
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
		if (Object::objects[i].get().GetEnabled())
			Object::objects[i].get().Render(csbi);
	}
}
double Engine::CalculateFPS()
{
	high_resolution_clock::time_point currentTime = high_resolution_clock::now();
	duration<double> timeElapsed = duration_cast<duration<double>>(currentTime - lastTime);

	// Check if one second has passed
	if (timeElapsed.count() >= 1.0)
	{
		double fps = frames / timeElapsed.count();

		// Reset counters for the next second
		frames = 0;
		lastTime = currentTime;
		lastFPS = fps;
		return fps;
	}

	return lastFPS;
}

void Engine::LogOut(LogType type, std::string content)
{
	Log l;
	l.type = type;
	l.content = content;
	logs.push_back(l);
}

std::string Engine::screen = "";
bool Engine::RUNNING = true;
CONSOLE_SCREEN_BUFFER_INFO Engine::csbi = {};
std::mutex Engine::screenMutex;
