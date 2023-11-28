#include "Engine/Engine.h"
#include "Game/Game.h"
#include <thread>
using namespace TEG;

int main()
{
	Engine::Init(Game());
	std::thread updateThread(&Engine::UpdateLoop);
	updateThread.join();
	return 0;
}
