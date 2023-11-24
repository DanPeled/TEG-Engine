#include "Engine.h"
#include "Classes/UI/UI.h"
#include "../Game/Game.h"
using namespace TEG;
using namespace std;

void Engine::init()
{
	Input::Initialize();
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	screen = string(consoleWidth * consoleHeight, ' ');
	system("cls");
	cout << "Engine initialized." << endl;
	Game::start();
}

void Engine::updateLoop()
{
	while (Engine::RUNNING)
	{
		std::lock_guard<std::mutex> lock(screenMutex);
		Game::update();
		Engine::printScreen();
		this_thread::sleep_for(chrono::milliseconds(30));
	}
	onStop();
}

void Engine::stop()
{
	Engine::RUNNING = false;
}
void Engine::onStop()
{
	system("cls");
	cout << "Engine stopped." << endl;
	Input::Cleanup();
}

void Engine::printScreen()
{
	system("cls"); // Clear the screen once before rendering objects
	std::size_t vectorLength = Object::objects.size();
	for (std::size_t i = 0; i < vectorLength; ++i)
	{
		Object::objects[i].get().render(csbi);
	}
}

std::string Engine::screen = "";
bool Engine::RUNNING = true;
CONSOLE_SCREEN_BUFFER_INFO Engine::csbi = {};
std::mutex Engine::screenMutex;
