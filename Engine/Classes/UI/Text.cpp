#include "Text.h"
using namespace TEG;
#include <algorithm>
const std::string Color::RESET = "\033[0m";
const std::string Color::BLACK = "\033[30m";			  /* Black */
const std::string Color::RED = "\033[31m";				  /* Red */
const std::string Color::GREEN = "\033[32m";			  /* Green */
const std::string Color::YELLOW = "\033[33m";			  /* Yellow */
const std::string Color::BLUE = "\033[34m";				  /* Blue */
const std::string Color::MAGENTA = "\033[35m";			  /* Magenta */
const std::string Color::CYAN = "\033[36m";				  /* Cyan */
const std::string Color::WHITE = "\033[37m";			  /* White */
const std::string Color::BOLDBLACK = "\033[1m\033[30m";	  /* Bold Black */
const std::string Color::BOLDRED = "\033[1m\033[31m";	  /* Bold Red */
const std::string Color::BOLDGREEN = "\033[1m\033[32m";	  /* Bold Green */
const std::string Color::BOLDYELLOW = "\033[1m\033[33m";  /* Bold Yellow */
const std::string Color::BOLDBLUE = "\033[1m\033[34m";	  /* Bold Blue */
const std::string Color::BOLDMAGENTA = "\033[1m\033[35m"; /* Bold Magenta */
const std::string Color::BOLDCYAN = "\033[1m\033[36m";	  /* Bold Cyan */
const std::string Color::BOLDWHITE = "\033[1m\033[37m";	  /* Bold White */
UI::Text::Text(Vector2 position_, std::string text_)
	: Object(position_), position(position_), text(text_), color(Color::WHITE)
{
}
UI::Text::Text(Vector2 position_, std::string text_, std::string color_) : Object(position_), position(position), text(text_), color(color_)
{
}
UI::Text::Text()
	: Object(Vector2(0, 0)), position(Vector2(0, 0)), text(""), color(Color::WHITE)
{
}
UI::Text UI::Text::instantiate(Vector2 pos, std::string text, std::string color)
{
	std::unique_ptr<UI::Text> obj = std::make_unique<UI::Text>(pos, text, color);

	// Store a reference to the object in the vector
	Object::objects.push_back(std::ref(*obj));

	// Move ownership to the caller
	return *obj.release();
}
UI::Text UI::Text::instantiate(Vector2 pos, std::string text)
{
	return instantiate(pos, text, Color::WHITE);
}

void UI::Text::render(const CONSOLE_SCREEN_BUFFER_INFO &csbi) const
{
	// Retrieve object properties
	Vector2 startPos = this->getPos();

	// Create a HANDLE to the console output buffer
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Set the cursor position
	COORD cursorPos = {static_cast<SHORT>(startPos.x), static_cast<SHORT>(startPos.y)};
	SetConsoleCursorPosition(hConsole, cursorPos);

	// Write the UTF-8 text to the console
	DWORD charsWritten;
	if (!WriteConsoleOutputCharacterA(hConsole, text.c_str(), static_cast<DWORD>(text.size()), cursorPos, &charsWritten))
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
