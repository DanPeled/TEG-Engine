#pragma once

#include "Vector2.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <windows.h>
#include <functional>
#include "Object.h"
namespace TEG
{
	class GameObject : public Object
	{

	public:
		bool hasFill;
		GameObject(Vector2 position_, int width_, int height_, char symbol_, bool hasFill_);
		GameObject();
		static GameObject *Instantiate(Vector2 pos, int width, int height, char symbol, bool hasFill_);
		inline int GetWidth() const
		{
			return width;
		}

		inline int GetHeight() const
		{
			return height;
		}

		virtual inline char GetSymbol() const
		{
			return symbol;
		}
		virtual void Render(const CONSOLE_SCREEN_BUFFER_INFO &csbi) const override;

	private:
		int width;
		int height;
		char symbol;
	};
}
