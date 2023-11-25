#include "Game.h"

#include <vector>
using namespace TEG;
using namespace std;
Vector2 startingPosition(12, 4);
GameObject *myGameObject;
UI::Text *myGameObject2;
int ticks = 0;
void Game::Start()
{
	myGameObject = GameObject::instantiate(startingPosition, 5, 3, '#');
	myGameObject2 = UI::Text::instantiate(Vector2(12, 8), "Joe", Color::BLUE);
}
void Game::Update()
{
	ticks += 1;
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
	Input::SimulateKeyPress('~');
	// Process input events
	for (const auto &event : inputEvents)
	{
		if (event.type == InputEventType::KeyClicked)
		{
			char pressedKey = std::get<char>(event.data);
			switch ((char)toupper(pressedKey))
			{
			// case 'W':
			// 	myGameObject->setPos(myGameObject->getPos() + Vector2(0, -2));
			// 	break;
			// case 'A':
			// 	myGameObject->setPos(myGameObject->getPos() + Vector2(-2, 0));
			// 	break;
			// case 'S':
			// 	myGameObject->setPos(myGameObject->getPos() + Vector2(0, 2));
			// 	break;
			// case 'D':
			// 	myGameObject->setPos(myGameObject->getPos() + Vector2(2, 0));
			// 	break;
			case 'Q':
				Engine::Stop();
				break;
			}
		}
	}
	myGameObject->setPos(myGameObject->getPos() + Vector2(1, 0));
	std::string xCoordinate = std::to_string(myGameObject->getPos().x);
	std::string ticksValue = std::to_string(ticks);
	std::string concatenatedText = xCoordinate + " " + ticksValue;

	myGameObject2->text = concatenatedText;
	if (myGameObject->getPos().x >= 118)
	{
		myGameObject->setPos(Vector2(-3, myGameObject->getPos().y));
	}
	// // Debug output
	// cout << "After input handling" << endl;
	// cout << "Game::update() completed" << endl;
}

void Game::exit()
{
}