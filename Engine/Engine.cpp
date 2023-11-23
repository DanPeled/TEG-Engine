#include "Engine.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace TEG;
using namespace std;

void Engine::init()
{
	Input::Initialize();
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	screen = string(consoleWidth * consoleHeight, ' ');

	cout << "Engine initialized." << endl;
}

void Engine::updateLoop()
{
	Vector2 startingPosition(0, 1);
	GameObject myGameObject = GameObject::instantiate(startingPosition, 3, 1, '#');

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

		Engine::printScreen(myGameObject);

		this_thread::sleep_for(chrono::milliseconds(0));
	}
	stop();
}

void Engine::stop()
{
	cout << "Engine stopped." << endl;
	Input::Cleanup();
}

void Engine::printScreen(const GameObject &obj)
{
	// Retrieve object properties
	Vector2 startPos = obj.getPos();
	int width = obj.getWidth();
	int height = obj.getHeight();
	char symbol = obj.getSymbol();

	// Create a HANDLE to the console output buffer
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Clear the console screen buffer
	COORD topLeft = {0, 0};
	DWORD dwCharsWritten;
	FillConsoleOutputCharacter(hConsole, ' ', csbi.dwSize.X * csbi.dwSize.Y, topLeft, &dwCharsWritten);

	// Create a CHAR_INFO buffer
	std::vector<CHAR_INFO> charBuffer(width * height);

	// Initialize each element of the CHAR_INFO vector
	for (int i = 0; i < width * height; ++i)
	{
		charBuffer[i].Char.UnicodeChar = symbol;
		charBuffer[i].Attributes = FOREGROUND_INTENSITY;
	}

	// Set up the rectangle to be updated
	SMALL_RECT rect;
	rect.Top = static_cast<SHORT>(startPos.y);
	rect.Left = static_cast<SHORT>(startPos.x);
	rect.Bottom = static_cast<SHORT>(startPos.y + height - 1);
	rect.Right = static_cast<SHORT>(startPos.x + width - 1);

	// Update the screen buffer with the GameObject
	WriteConsoleOutput(hConsole, charBuffer.data(), {static_cast<SHORT>(width), static_cast<SHORT>(height)}, {0, 0}, &rect);
}

std::string Engine::screen = "";
bool Engine::RUNNING = true;
CONSOLE_SCREEN_BUFFER_INFO Engine::csbi = {};
std::mutex Engine::screenMutex;
