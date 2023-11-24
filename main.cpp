#include "Engine/Engine.h"
#include <thread>

using namespace TEG;

int main()
{
	Engine::init();
	std::thread updateThread(&Engine::updateLoop);
	updateThread.join();
	return 0;
}
