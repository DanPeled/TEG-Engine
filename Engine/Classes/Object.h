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
		static const WORD RESET = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		static const WORD BLACK = 0;
		static const WORD RED = FOREGROUND_RED;
		static const WORD GREEN = FOREGROUND_GREEN;
		static const WORD YELLOW = FOREGROUND_RED | FOREGROUND_GREEN;
		static const WORD BLUE = FOREGROUND_BLUE;
		static const WORD MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE;
		static const WORD CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE;
		static const WORD WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		static const WORD UNDERLINE = COMMON_LVB_UNDERSCORE;
		static const WORD STRIKETHROUGH = 0x8000;
		static const WORD BOLD = FOREGROUND_INTENSITY;
	};

	class Object : public std::enable_shared_from_this<Object>
	{
	public:
		Object(Vector2 position_) : globalPosition(position_), parentOffset(Vector2(0, 0))
		{
			this->SetEnabled(true);
			this->ID = ObtainID(this);
		}

		~Object();

		virtual void Render(const CONSOLE_SCREEN_BUFFER_INFO &csbi) const;

		inline void SetPos(Vector2 newPos)
		{
			globalPosition = newPos;
			for (std::reference_wrapper<Object> child : GetChildren())
			{
				child.get().SetPos(newPos - child.get().GetParentOffset());
				child.get().parentOffset = CalculateParentChildOffset(child.get());
			}
		}
		inline Vector2 GetLocalPositon()
		{
			return this->parentOffset - this->globalPosition;
		};
		inline Vector2 GetGlobalPosition() const
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
			child->SetPos(child->GetGlobalPosition() - GetGlobalPosition());
			child->parentOffset = CalculateParentChildOffset(*child);
		}
		Vector2 GetParentOffset()
		{
			return this->parentOffset;
		}
		int GetChildCount()
		{
			return this->children.size();
		}

		std::vector<std::reference_wrapper<Object>> GetChildren() const;
		static Object GetObjectWithID(unsigned int ID);
		bool GetEnabled();
		void SetEnabled(bool state);
		unsigned int GetID() { return this->ID; }
		static std::vector<std::reference_wrapper<Object>> objects;

	private:
		Vector2 parentOffset;
		Vector2 globalPosition;
		std::set<unsigned int> children;
		std::uintptr_t ID;
		bool enabled;
		unsigned int ObtainID(Object *obj)
		{
			std::uintptr_t address = reinterpret_cast<std::uintptr_t>(obj);
			return address;
		}
		Vector2 CalculateParentChildOffset(Object child)
		{
			return globalPosition - child.GetGlobalPosition();
		}
	};
}
