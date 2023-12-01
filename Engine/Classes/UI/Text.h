#pragma once
#include <windows.h>
#include "../Vector2.h"
#include <string>
#include "../Object.h"
#include <algorithm>
#include <sstream>
#include <string>
namespace TEG
{
    namespace UI
    {
        class Text : public Object
        {
        public:
            std::string text;
            WORD color; // WORD for console attributes

            Text(Vector2 position_, std::string text_);
            Text(Vector2 globalPosition, std::string text_, WORD color_);
            Text();

            void Render(const CONSOLE_SCREEN_BUFFER_INFO &csbi) const;

            static Text *Instantiate(Vector2 pos, std::string text);
            static Text *Instantiate(Vector2 pos, std::string text, WORD color);

        private:
            std::string ProcessSpecialCharacters(const std::string &input) const;
        };
    }
}
