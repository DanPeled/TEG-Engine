#pragma once

#include <windows.h>
#include "Classes/GameObject.h"
#include <mutex>
#include "Classes/Input.h"
namespace TEG
{
	class Engine
	{
	public:
		static void init();
		static void updateLoop();
		static void stop();
		static void printScreen(const GameObject &obj);

	private:
		static std::string screen;
		static bool RUNNING;
		static CONSOLE_SCREEN_BUFFER_INFO csbi;
		static std::mutex screenMutex;
	};
}
