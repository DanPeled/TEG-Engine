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
	class Object : public std::enable_shared_from_this<Object>
	{
	public:
		Object(Vector2 position_) : position(position_)
		{
			this->SetEnabled(true);
			this->ID = ObtainID(this);
		}
		virtual void Render(const CONSOLE_SCREEN_BUFFER_INFO &csbi) const;

		inline void SetPos(Vector2 newPos)
		{
			position = newPos;
		}
		inline Vector2 GetPos() const
		{
			return position;
		}
		virtual void Destory(){

		};
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
		Vector2 position;
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
