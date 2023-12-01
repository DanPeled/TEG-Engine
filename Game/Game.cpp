#include "Game.h"
using namespace TEG;
using namespace std::chrono;

Vector2 startingPosition(12, 4);
GameObject *parentObj;
UI::Text *text1;
UI::Text *fpsText;
void Game::Start()
{
	parentObj = GameObject::Instantiate(startingPosition, 5, 5, '#', false);
	text1 = UI::Text::Instantiate(startingPosition - Vector2(0, 1), "cheese", ConsoleAttributes().GREEN /*, +[]()
											{ cout << "Test"; }*/
	);
	fpsText = UI::Text::Instantiate(startingPosition - Vector2(0, 2), "FPS: 0", ConsoleAttributes().BLUE);
	parentObj->AddChild(text1);
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
				parentObj->AddChild(text1);
				std::cout << parentObj->GetChildren().size();
				break;
			case 'E':
				parentObj->SetEnabled(!parentObj->GetEnabled());
				break;
			case 'W':
				Engine::sleepTime += 1;
				break;
			case 'S':
				Engine::sleepTime -= 1;
				break;
			}
		}
	}

	parentObj->SetPos(parentObj->GetGlobalPosition() + Vector2(1, 0));
	std::string text = "- " + std::to_string(parentObj->GetID()) + "\n" + std::to_string(text1->GetParentOffset().x) +
					   " " + std::to_string(text1->GetParentOffset().y) + "\n";
	fpsText->text = "FPS: " + std::to_string(Engine::CalculateFPS()) + "\n" + "Sleep Time: " + std::to_string(Engine::sleepTime);
	for (Object &child : parentObj->GetChildren())
	{
		text += "\tL " + std::to_string(child.GetID()) + "\n";
	}
	text1->text = text;
	if (parentObj->GetGlobalPosition().x >= 118)
	{
		parentObj->SetPos(Vector2(-3, parentObj->GetGlobalPosition().y));
	}
}

void Game::Exit()
{
	system("cls");
}
