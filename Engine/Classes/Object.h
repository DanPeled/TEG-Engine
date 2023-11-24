#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <windows.h>
#include <functional>
#include "Vector2.h"

namespace TEG
{
	class Object
	{
		Vector2 position;

	public:
		Object(Vector2 position_) : position(position_) {}

		virtual void render(const CONSOLE_SCREEN_BUFFER_INFO &csbi) const = 0;

		static std::vector<std::reference_wrapper<Object>> objects;
	};
}
