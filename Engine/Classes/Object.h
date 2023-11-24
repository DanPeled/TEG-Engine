#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <windows.h>
#include <functional>
#include "Vector2.h"
#include <memory>
#include <functional>
#include <string>
#include <iostream>

namespace TEG
{
	class Object : public std::enable_shared_from_this<Object>
	{
		Vector2 position;

	public:
		Object(Vector2 position_) : position(position_) {}

		virtual void render(const CONSOLE_SCREEN_BUFFER_INFO &csbi) const = 0;
		inline void setPos(Vector2 newPos)
		{
			position = newPos;
		}
		inline Vector2 getPos()
		{
			return position;
		}
		static std::vector<std::reference_wrapper<TEG::Object>> objects;
	};
}
