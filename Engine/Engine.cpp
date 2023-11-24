#include "Engine.h"
#include "Classes/UI/UI.h"
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
}

void Engine::updateLoop()
{
	Vector2 startingPosition(12, 4);
	GameObject myGameObject = GameObject::instantiate(startingPosition, 5, 3, '#');
	Text myGameObject2 = Text::instantiate(Vector2(12, 8), "Joe");
	while (Engine::RUNNING)
	{
		std::lock_guard<std::mutex> lock(screenMutex);

		// Gather input events
		vector<InputEvent> inputEvents = Input::GetInputEvents();

		// Process input events
		for (const auto &event : inputEvents)
		{
			if (event.type == InputEventType::KeyClicked)
			{
				char pressedKey = std::get<char>(event.data);
				// cout << "KeyClicked! Key: " << pressedKey << std::endl;

				switch ((char)toupper(pressedKey))
				{
				case 'W':
					myGameObject.setPos(myGameObject.getPos() + Vector2(0, -1));
					break;
				case 'A':
					myGameObject.setPos(myGameObject.getPos() + Vector2(-1, 0));
					break;
				case 'S':
					myGameObject.setPos(myGameObject.getPos() + Vector2(0, 1));
					break;
				case 'D':
					myGameObject.setPos(myGameObject.getPos() + Vector2(1, 0));
					break;
				case 'Q':
					Engine::RUNNING = false;
					break;
				}
			}
		}

		Engine::printScreen();

		this_thread::sleep_for(chrono::milliseconds(0));
	}
	stop();
}

void Engine::stop()
{
	cout << "Engine stopped." << endl;
	Input::Cleanup();
}

void Engine::printScreen()
{
	std::size_t vectorLength = Object::objects.size();
	for (unsigned int i = 0; i < vectorLength; i++)
	{
		Object::objects[i].get().render(csbi);
	}
}

std::string Engine::screen = "";
bool Engine::RUNNING = true;
CONSOLE_SCREEN_BUFFER_INFO Engine::csbi = {};
std::mutex Engine::screenMutex;
