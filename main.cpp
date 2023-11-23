#include "Engine/Engine.h"
#include <thread>

using namespace TEG;

int main()
{
	// Initialize the engine
	Engine::init();

	// Start the update loop in a separate thread
	std::thread updateThread(&Engine::updateLoop);

	// Wait for the updateThread to finish before returning from main
	updateThread.join();

	return 0;
}
