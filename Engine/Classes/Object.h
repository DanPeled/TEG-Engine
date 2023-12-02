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
#include <string>
#include <set>
#include "Component.h"
#include <unordered_set>

namespace TEG
{
	// Class for handling console attributes
	class ConsoleAttributes
	{
	public:
		// Constants for console attributes
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

	// Base class for game objects
	class Object : public std::enable_shared_from_this<Object>
	{
	public:
		// Constructor
		Object(Vector2 position_) : globalPosition(position_), parentOffset(Vector2(0, 0))
		{
			this->SetEnabled(true);
			this->ID = ObtainID(this);
			this->components = {};
		}

		// Destructor
		~Object();

		// Virtual function for rendering the object
		virtual void Render(const CONSOLE_SCREEN_BUFFER_INFO &csbi) const;

		// Set position of the object and its children
		inline void SetPos(Vector2 newPos)
		{
			globalPosition = newPos;
			for (std::reference_wrapper<Object> child : GetChildren())
			{
				child.get().SetPos(newPos - child.get().GetParentOffset());
				child.get().parentOffset = CalculateParentChildOffset(child.get());
			}
		}

		// Get local position of the object
		inline Vector2 GetLocalPositon()
		{
			return this->parentOffset - this->globalPosition;
		};

		// Get global position of the object
		inline Vector2 GetGlobalPosition() const
		{
			return globalPosition;
		}

		// Destroy the object and its children
		void Destroy();

		template <typename T>
		void AddComponent(std::shared_ptr<T> addedComp)
		{
			components.push_back(addedComp);
			Component &component = *addedComp;
			component.Start();
		}

		const std::vector<std::shared_ptr<Component>> GetComponents() const
		{
			return components;
		}
		// Destroy only the children of the object
		void DestroyChildren()
		{
			for (std::reference_wrapper<Object> child : GetChildren())
			{
				child.get().Destroy();
			}
		}

		// Add a child object to the object
		void AddChild(Object *child)
		{
			unsigned int childID = ObtainID(child);
			std::set<unsigned int>::iterator it = children.find(childID);
			if (it != children.end())
			{
				return; // Prevent from the same child to be added twice
			}
			children.insert(childID);
			child->SetPos(child->GetGlobalPosition() - GetGlobalPosition());
			child->parentOffset = CalculateParentChildOffset(*child);
		}

		// Get parent offset of the object
		Vector2 GetParentOffset()
		{
			return this->parentOffset;
		}

		// Get the count of children of the object
		int GetChildCount()
		{
			return this->children.size();
		}

		// Get a vector of references to children of the object
		std::vector<std::reference_wrapper<Object>> GetChildren() const;

		// Get an object with a specific ID
		static Object GetObjectWithID(unsigned int ID);

		// Check if the object is enabled
		bool GetEnabled();

		// Set the enabled state of the object
		void SetEnabled(bool state);

		// Get the ID of the object
		unsigned int GetID() { return this->ID; }

		// Static vector to store all objects refrences
		static std::vector<std::reference_wrapper<Object>> objects;

	private:
		Vector2 parentOffset;								// Offset from the parent object
		Vector2 globalPosition;								// Global position of the object
		std::set<unsigned int> children;					// Set of child IDs
		std::vector<std::shared_ptr<Component>> components; // Vector to store Object components
		std::uintptr_t ID;									// Unique ID of the object
		bool enabled;										// Flag indicating if the object is enabled

		// Obtain a unique ID for an object based on its memory address
		unsigned int ObtainID(Object *obj)
		{
			std::uintptr_t address = reinterpret_cast<std::uintptr_t>(obj);
			return address;
		}

		// Calculate the offset between parent and child
		Vector2 CalculateParentChildOffset(Object child)
		{
			return globalPosition - child.GetGlobalPosition();
		}
	};
}
