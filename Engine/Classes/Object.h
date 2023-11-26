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
#include <set>
namespace TEG
{
	class ConsoleAttributes
	{
	public:
		static const WORD RESET = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; // Default console attributes
		static const WORD BLACK = 0;
		static const WORD RED = FOREGROUND_RED;
		static const WORD GREEN = FOREGROUND_GREEN;
		static const WORD YELLOW = FOREGROUND_RED | FOREGROUND_GREEN;
		static const WORD BLUE = FOREGROUND_BLUE;
		static const WORD MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE;
		static const WORD CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE;
		static const WORD WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		static const WORD UNDERLINE = COMMON_LVB_UNDERSCORE; /*Might not work in some terminals*/
		static const WORD STRIKETHROUGH = 0x8000;			 /*Might not work in some terminals*/
		static const WORD BOLD = FOREGROUND_INTENSITY;		 /*Might not work in some terminals*/
	};
	class Object : public std::enable_shared_from_this<Object>
	{
	public:
		Object(Vector2 position_) : globalPosition(position_)
		{
			this->SetEnabled(true);
			this->ID = ObtainID(this);
		};
		~Object();
		virtual void Render(const CONSOLE_SCREEN_BUFFER_INFO &csbi) const;

		inline void SetPos(Vector2 newPos)
		{
			globalPosition = newPos;
		}
		inline Vector2 GetPos() const
		{
			return globalPosition;
		}
		void Destroy();
		void DestroyChildren()
		{
			for (std::reference_wrapper<Object> child : GetChildren())
			{
				child.get().Destroy();
			}
		}

		void AddChild(Object *child)
		{
			unsigned int childID = ObtainID(child);
			children.insert(childID);
		}
		int GetChildCount()
		{
			return this->children.size();
		};

		std::vector<std::reference_wrapper<Object>> GetChildren() const;
		static Object GetObjectWithID(unsigned int ID);
		bool GetEnabled();
		void SetEnabled(bool state);
		unsigned int GetID() { return this->ID; };
		static std::vector<std::reference_wrapper<TEG::Object>> objects;

	private:
		Vector2 localPosition;
		Vector2 globalPosition;
		std::set<unsigned int> children; // A set to prevent multiple instances of the same object
		std::uintptr_t ID;
		bool enabled;
		unsigned int ObtainID(Object *obj)
		{
			std::uintptr_t address = reinterpret_cast<std::uintptr_t>(obj);
			return address;
		}
	};
}
