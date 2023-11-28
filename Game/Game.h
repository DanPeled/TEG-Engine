#pragma once
#ifndef GAME_H
#define GAME_H

#pragma region ENGINE INCLUDES
#include "../Engine/Engine.h"
#include "../Engine/Classes/Vector2.h"
#include "../Engine/Classes/GameObject.h"
#include "../Engine/Classes/UI/UI.h"
#include "../Engine/Classes/Input.h"
#include "../Engine/Classes/Audio/Audio.h"
#pragma endregion

#include <windows.h>
#include <mutex>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>

// Inherit from this class to make your main game file
class Game
{
public:
	static void Start();
	static void Update();
	static void Exit();
};
#endif