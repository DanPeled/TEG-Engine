#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

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
	// Class for representing a basic game object rectangle-like shaped
	class GameObject : public Object
	{
	public:
		// Public members
		bool hasFill; // Indicates whether the object has a fill

		// Constructor with parameters
		GameObject(Vector2 position_, int width_, int height_, char symbol_, bool hasFill_);

		// Default constructor
		GameObject();

		// Static function to instantiate a GameObject
		static GameObject *Instantiate(Vector2 pos, int width, int height, char symbol, bool hasFill_);

		// Getter for the width of the GameObject
		inline int GetWidth() const
		{
			return width;
		}

		// Getter for the height of the GameObject
		inline int GetHeight() const
		{
			return height;
		}

		// function to get the symbol of the GameObject
		inline char GetSymbol() const
		{
			return symbol;
		}

		// Overridden Render function for rendering the GameObject
		virtual void Render(const CONSOLE_SCREEN_BUFFER_INFO &csbi) const override;

	private:
		int width;	 // Width of the GameObject
		int height;	 // Height of the GameObject
		char symbol; // Symbol representing the GameObject
	};
}
#endif