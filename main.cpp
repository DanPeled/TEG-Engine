#include "Engine/Engine.h"
#include <thread>

using namespace TEG;

int main()
{
	Engine::Init();
	std::thread updateThread(&Engine::UpdateLoop);
	updateThread.join();
	return 0;
}
