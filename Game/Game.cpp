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
UI::Text *myGameObject2;
void Game::Start()
{
	myGameObject = GameObject::Instantiate(startingPosition, 5, 5, '#', false);
	myGameObject2 = UI::Text::Instantiate(startingPosition - Vector2(0, 1), "cheese", FOREGROUND_GREEN);
	myGameObject->AddChild(myGameObject2);
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
			case 'D':
				myGameObject->Destroy();
				break;
			case 'E':
				myGameObject->SetEnabled(!myGameObject->GetEnabled());
				break;
			}
		}
	}

	myGameObject->SetPos(myGameObject->GetPos() + Vector2(1, 0));
	std::string text = "- " + std::to_string(myGameObject->GetID()) + "\n";
	for (Object &child : myGameObject->GetChildren())
	{
		text += "\tL " + std::to_string(child.GetID()) + "\n";
	}
	myGameObject2->text = text;
	if (myGameObject->GetPos().x >= 118)
	{
		myGameObject->SetPos(Vector2(-3, myGameObject->GetPos().y));
	}
}

void Game::Exit()
{
	system("cls");
}
