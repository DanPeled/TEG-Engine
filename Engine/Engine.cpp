#include <iostream>
#include <thread>
#include "Engine.h"
#include "../Game/Game.h"
#include <fstream>
#include <future>
#include "Classes/Component.h"

Game game;

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
		Tick();
	}
	OnStop();
}

void Engine::Tick()
{
	ticks += 1;
	frames += 1;
	Engine::RenderObjects();
	game.Update();
	this_thread::sleep_for(chrono::milliseconds(sleepTime));
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

void Engine::RenderObjects()
{
	system("cls");

	const std::size_t vectorLength = Object::objects.size();
	const std::size_t numThreads = std::thread::hardware_concurrency();

	std::vector<std::future<void>> futures;

	// Function to process a range of objects in parallel
	auto processRange = [](std::size_t start, std::size_t end)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		for (std::size_t j = start; j < end; ++j)
		{
			auto &currentObject = Object::objects[j].get();

			if (currentObject.GetEnabled())
			{
				// Move the cursor to the correct position before rendering
				COORD cursorPos = {static_cast<SHORT>(currentObject.GetGlobalPosition().x),
								   static_cast<SHORT>(std::max<SHORT>(0, currentObject.GetGlobalPosition().y))};
				SetConsoleCursorPosition(hConsole, cursorPos);

				// Render the object directly to the console
				currentObject.Render(csbi);

				// Get components and run the Update function on each enabled one
				const auto &components = currentObject.GetComponents();
				for (const auto &componentPtr : components)
				{
					Component &component = *componentPtr;
					if (component.GetEnabled())
					{
						component.Update();
					}
				}
			}
		}
	};

	// Divide the rendering work among multiple threads
	for (std::size_t i = 0; i < numThreads; ++i)
	{
		std::size_t start = i * vectorLength / numThreads;
		std::size_t end = (i + 1) * vectorLength / numThreads;

		futures.emplace_back(std::async(std::launch::async, [=]()
										{ processRange(start, end); }));
	}

	// Wait for all threads to finish
	for (auto &future : futures)
	{
		future.wait();
	}
}

double Engine::CalculateFPS()
{
	high_resolution_clock::time_point currentTime = high_resolution_clock::now();
	duration<double> timeElapsed = duration_cast<duration<double>>(currentTime - lastTime);

	// Check if one second has passed
	if (timeElapsed.count() >= 0.1)
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
	LogOut(l);
}

void Engine::LogOut(Log l)
{
	std::string typePrefix = "";
	switch (l.type)
	{
	case Warning:
	{
		typePrefix = "Warning";
		break;
	}
	case Error:
	{
		typePrefix = "Error";
		break;
	}
	case None:
	{
		break;
	}
	case Debug:
	{
		typePrefix = "Debug";
		break;
	}
	};
	std::ofstream file("logs.txt", std::ios_base::app);

	if (!file.is_open())
	{
		std::cerr << "Error opening logs.txt for writing" << std::endl;
		return;
	}

	auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string timestamp = std::ctime(&now);

	// Remove newline character from the timestamp
	timestamp.pop_back();

	file << timestamp << " " << typePrefix << ": " << l.content << std::endl;
	file.close();

	logs.push_back(l);
}

std::string Engine::screen = "";
bool Engine::RUNNING = true;
CONSOLE_SCREEN_BUFFER_INFO Engine::csbi = {};
std::mutex Engine::screenMutex;
std::vector<std::reference_wrapper<TEG::Object>> TEG::Object::objects = {};
std::vector<Log> Engine::logs;
high_resolution_clock::time_point Engine::lastTime;
int Engine::ticks = 0;
int Engine::frames = 0;
double Engine::lastFPS = 0;
unsigned int Engine::sleepTime = 18;