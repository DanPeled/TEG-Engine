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
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace TEG;
using namespace std;
using namespace std::chrono;
namespace TEG
{
	class Engine
	{
	public:
		static void Init();
		static void UpdateLoop();
		static void PrintScreen();
		static void Stop();
		static double CalculateFPS();

	private:
		static void OnStop();
		static std::string screen;
		static bool RUNNING;
		static CONSOLE_SCREEN_BUFFER_INFO csbi;
		static std::mutex screenMutex;
		static int ticks;
		static int frames;
		static double lastFPS;
		static high_resolution_clock::time_point lastTime;
	};
}
