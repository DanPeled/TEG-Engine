#pragma once
#include <windows.h>
#include "../Vector2.h"
#include <string>
#include "../Object.h"
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
        static const WORD BOLD = FOREGROUND_INTENSITY;
    };

    namespace UI
    {
        class Text : public Object
        {
            Vector2 position;

        public:
            std::string text;
            WORD color; // Use WORD for console attributes
            Text(Vector2 position_, std::string text_);
            Text(Vector2 position, std::string text_, WORD color_);
            Text();
            void Render(const CONSOLE_SCREEN_BUFFER_INFO &csbi) const;
            static Text *Instantiate(Vector2 pos, std::string text);
            static Text *Instantiate(Vector2 pos, std::string text, WORD color);
        };
    }
}
