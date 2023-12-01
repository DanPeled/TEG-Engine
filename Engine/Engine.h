#pragma once
#ifndef ENGINE_H
#define ENGINE_H

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
#include <algorithm>
#include <string>

using namespace TEG;
using namespace std;
using namespace std::chrono;
class Game;
namespace TEG
{
	class Engine
	{
	public:
		static void Init(Game game_);
		static void UpdateLoop();
		static void PrintScreen();
		static void Stop();
		static double CalculateFPS();
		static void LogOut(LogType type, std::string content);

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
		static vector<Log> logs;
	};
	enum LogType
	{
		None,
		Warning,
		Error,
		Debug
	};
	struct Log
	{
		LogType type;
		std::string content;
	};

}

#endif