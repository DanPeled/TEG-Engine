#pragma once
#include "../Vector2.h"
#include "UI.h"
#include <iostream>
#include "../../Util/colors.h"

namespace TEG
{
	namespace UI
	{
		class Text : public Object
		{
			Vector2 position;

		public:
			std::string text;
			std::string color;
			Text(Vector2 position_, std::string text_);
			Text(Vector2 position, std::string text_, std::string color_);
			Text();
			Vector2 getPos() const
			{
				return position;
			}
			void render(const CONSOLE_SCREEN_BUFFER_INFO &csbi) const;
			static Text instantiate(Vector2 pos, std::string text);
			static Text instantiate(Vector2 pos, std::string text, std::string color);
			inline void setPos(Vector2 newPos)
			{
				system("cls");
				position = newPos;
			}
		};
	}
}