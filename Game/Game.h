#pragma once
#include "../Engine/Engine.h"
#include "../Engine/Classes/Vector2.h"
#include "../Engine/Classes/GameObject.h"
#include "../Engine/Classes/UI/UI.h"
#include <windows.h>
#include <mutex>
#include "../Engine/Classes/Input.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

// Inherit from this class to make your main game file
class Game
{
public:
	static void Start();
	static void Update();
	static void Exit();
};