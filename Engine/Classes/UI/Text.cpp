#include "Text.h"
using namespace TEG;
#include <algorithm>

Text::Text(Vector2 position_, std::string text_)
	: Object(position_), position(position_), text(text_)
{
}

Text::Text()
	: Object(Vector2(0, 0)), position(Vector2(0, 0)), text("")
{
}
Text Text::instantiate(Vector2 pos, std::string text)
{
	Text obj = Text(pos, text);
	Object::objects.push_back(std::ref(obj));
	return obj;
}

void Text::render(const CONSOLE_SCREEN_BUFFER_INFO &csbi) const
{
	// Retrieve object properties
	Vector2 startPos = this->getPos();

	// Create a HANDLE to the console output buffer
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Convert UTF-8 string to wide character string
	int wideCharCount = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, nullptr, 0);
	std::vector<WCHAR> wideText(wideCharCount);
	MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, wideText.data(), wideCharCount);

	// Set the cursor position
	COORD cursorPos = {static_cast<SHORT>(startPos.x), static_cast<SHORT>(startPos.y)};
	SetConsoleCursorPosition(hConsole, cursorPos);

	// Set up the console attributes for intensity without clearing the background
	SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);

	// Write each character to the console
	for (WCHAR wideChar : wideText)
	{
		DWORD charsWritten;
		if (!WriteConsoleOutputCharacterW(hConsole, &wideChar, 1, cursorPos, &charsWritten))
		{
			DWORD error = GetLastError();
			std::cerr << "Error writing to console. Error code: " << error << std::endl;
		}

		// Move the cursor to the next position
		cursorPos.X++;
	}
}
