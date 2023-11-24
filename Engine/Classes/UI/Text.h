#pragma once
#include "../Vector2.h"
#include "UI.h"
#include <iostream>
namespace TEG
{
	class Text : public Object
	{
		Vector2 position;

	public:
		Text(Vector2 position_, std::string text_);
		Text();
		Vector2 getPos() const
		{
			return position;
		}
		std::string text;
		void render(const CONSOLE_SCREEN_BUFFER_INFO &csbi) const;
		static Text instantiate(Vector2 pos, std::string text);
		inline void setPos(Vector2 newPos)
		{
			position = newPos;
		}
	};
}