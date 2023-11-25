#pragma once

#include <windows.h>
#include "Classes/GameObject.h"
#include <mutex>
#include "Classes/Input.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "Classes/UI/UI.h"
namespace TEG
{
	class Engine
	{
	public:
		static void Init();
		static void UpdateLoop();
		static void PrintScreen();
		static void Stop();

	private:
		static void OnStop();
		static std::string screen;
		static bool RUNNING;
		static CONSOLE_SCREEN_BUFFER_INFO csbi;
		static std::mutex screenMutex;
	};
}
