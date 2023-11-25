#include "Game.h"
#include <algorithm>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>
using namespace TEG;
using namespace std::chrono;

Vector2 startingPosition(12, 4);
GameObject *myGameObject;
GameObject *myGameObject2;
void Game::Start()
{
	myGameObject = GameObject::Instantiate(startingPosition, 5, 3, '#');
	myGameObject2 = GameObject::Instantiate(startingPosition, 5, 7, '#');
}

void Game::Update()
{

	// Gather input events
	std::vector<InputEvent> inputEvents = Input::GetInputEvents();

	// Simulate space key
	Input::SimulateKeyPress(' ', false, false, false);

	// Process input events
	for (const auto &event : inputEvents)
	{
		if (event.type == InputEventType::KeyClicked)
		{
			char pressedKey = std::get<char>(event.data);
			switch ((char)toupper(pressedKey))
			{
			case 'Q':
				Engine::Stop();
				break;
			case 'A':
				myGameObject->AddChild(myGameObject2);
				cout << myGameObject->GetChildren().size();
				break;
			}
		}
	}

	myGameObject->SetPos(myGameObject->GetPos() + Vector2(1, 0));

	// myGameObject2->text = "FPS: " + std::to_string(Engine::CalculateFPS());

	if (myGameObject->GetPos().x >= 118)
	{
		myGameObject->SetPos(Vector2(-3, myGameObject->GetPos().y));
	}
}

void Game::Exit()
{
	system("cls");
}
