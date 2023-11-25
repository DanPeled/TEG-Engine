#pragma once
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
#include "../Engine/Engine.h"
class Game
{
public:
	static void Start();
	static void Update();
	static void exit();
};