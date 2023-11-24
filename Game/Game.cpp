#include "Game.h"

#include <vector>
using namespace TEG;
using namespace std;
Vector2 startingPosition(12, 4);
GameObject *myGameObject;
UI::Text *myGameObject2;
void Game::start()
{
	myGameObject = GameObject::instantiate(startingPosition, 5, 3, '#');
	myGameObject2 = UI::Text::instantiate(Vector2(12, 8), "Joe", Color::BLUE);
}
void Game::update()
{
	// cout << "Game::update() called" << endl;

	// Gather input events
	std::vector<InputEvent> inputEvents = Input::GetInputEvents();

	// // Debug output for input events
	// for (const auto &event : inputEvents)
	// {
	// 	cout << "Input Event: Type=" << static_cast<int>(event.type);
	// 	if (event.type == InputEventType::KeyClicked)
	// 	{
	// 		cout << ", Key=" << std::get<char>(event.data);
	// 	}
	// 	cout << endl;
	// }

	// Process input events
	for (const auto &event : inputEvents)
	{
		if (event.type == InputEventType::KeyClicked)
		{
			char pressedKey = std::get<char>(event.data);
			switch ((char)toupper(pressedKey))
			{
			case 'W':
				myGameObject->setPos(myGameObject->getPos() + Vector2(0, -2));
				break;
			case 'A':
				myGameObject->setPos(myGameObject->getPos() + Vector2(-2, 0));
				break;
			case 'S':
				myGameObject->setPos(myGameObject->getPos() + Vector2(0, 2));
				break;
			case 'D':
				myGameObject->setPos(myGameObject->getPos() + Vector2(2, 0));
				break;
			case 'Q':
				Engine::stop();
				break;
			}
		}
	}
	// // Debug output
	// cout << "After input handling" << endl;
	// cout << "Game::update() completed" << endl;
}

void Game::exit()
{
}