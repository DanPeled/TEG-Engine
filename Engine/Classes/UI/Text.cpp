#include "Text.h"
using namespace TEG;
#include <algorithm>

UI::Text::Text(Vector2 position_, std::string text_)
	: Object(position_), position(position_), text(text_), color(ConsoleAttributes().WHITE)
{
}

UI::Text::Text(Vector2 position_, std::string text_, WORD color_) : Object(position_), position(position), text(text_), color(color_)
{
}

UI::Text::Text()
	: Object(Vector2(0, 0)), position(Vector2(0, 0)), text(""), color(ConsoleAttributes().WHITE)
{
}

UI::Text *UI::Text::Instantiate(Vector2 pos, std::string text, WORD color)
{
	UI::Text *obj = new UI::Text(pos, text, color);
	Object::objects.push_back(*obj);
	return obj;
}

UI::Text *UI::Text::Instantiate(Vector2 pos, std::string text)
{
	return Instantiate(pos, text, ConsoleAttributes().GREEN | ConsoleAttributes().BOLD);
}

void UI::Text::Render(const CONSOLE_SCREEN_BUFFER_INFO &csbi) const
{
	// Retrieve object properties
	Vector2 startPos = this->GetPos();

	// Create a HANDLE to the console output buffer
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Set the cursor position
	COORD cursorPos = {static_cast<SHORT>(startPos.x), std::max<SHORT>(0, static_cast<SHORT>(startPos.y))};

	SetConsoleCursorPosition(hConsole, cursorPos);

	// Create a CHAR_INFO buffer to hold character and attributes
	std::vector<CHAR_INFO> charBuffer(text.size(), {' ', color});

	// Copy text to CHAR_INFO buffer
	for (size_t i = 0; i < text.size(); ++i)
	{
		charBuffer[i].Char.AsciiChar = text[i];
	}

	// Write the CHAR_INFO buffer to the console
	COORD bufferSize = {static_cast<SHORT>(text.size()), 1};
	COORD bufferCoord = {0, 0};

	// Explicitly cast values to SHORT to address narrowing conversion warnings
	SMALL_RECT writeRegion = {
		static_cast<SHORT>(cursorPos.X),
		static_cast<SHORT>(cursorPos.Y),
		static_cast<SHORT>(cursorPos.X + bufferSize.X - 1),
		static_cast<SHORT>(cursorPos.Y + bufferSize.Y - 1)};

	if (!WriteConsoleOutputA(hConsole, charBuffer.data(), bufferSize, bufferCoord, &writeRegion))
	{
		DWORD error = GetLastError();
		std::cerr << "Error writing to console. Error code: " << error << std::endl;

		// Print more details about the error
		std::cerr << "CursorPos: (" << cursorPos.X << ", " << cursorPos.Y << ")" << std::endl;
		std::cerr << "Text: " << text << std::endl;

		// Exit the function or handle the error as needed
		return;
	}
}
