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
	UI::Text myGameObject2 = UI::Text::instantiate(Vector2(12, 8), "Joe", Color::BLUE);
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
					myGameObject.setPos(myGameObject.getPos() + Vector2(0, -2));
					break;
				case 'A':
					myGameObject.setPos(myGameObject.getPos() + Vector2(-2, 0));
					break;
				case 'S':
					myGameObject.setPos(myGameObject.getPos() + Vector2(0, 2));
					break;
				case 'D':
					myGameObject.setPos(myGameObject.getPos() + Vector2(2, 0));
					break;
				case 'Q':
					Engine::RUNNING = false;
					break;
				}
			}
		}

		Engine::printScreen();
		this_thread::sleep_for(chrono::milliseconds(30));
	}
	stop();
}

void Engine::stop()
{
	system("cls");
	cout << "Engine stopped." << endl;
	Input::Cleanup();
}

void Engine::printScreen()
{
	// Clear the screen
	system("cls");

	// Render all objects
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
