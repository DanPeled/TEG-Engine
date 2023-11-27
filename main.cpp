#include "Engine/Engine.h"
#include <thread>
#include "Game/Game.h"
using namespace TEG;

int main()
{
	Engine::Init(Game());
	std::thread updateThread(&Engine::UpdateLoop);
	updateThread.join();
	return 0;
}
