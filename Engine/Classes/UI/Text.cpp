#include "Text.h"
using namespace TEG;

UI::Text::Text(Vector2 position_, std::string text_)
	: Object(position_), text(text_), color(ConsoleAttributes().WHITE)
{
}

UI::Text::Text(Vector2 position_, std::string text_, WORD color_) : Object(position_), text(text_), color(color_)
{
}

UI::Text::Text()
	: Object(Vector2(0, 0)), text(""), color(ConsoleAttributes().WHITE)
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
	Vector2 startPos = this->GetGlobalPosition();

	// Create a HANDLE to the console output buffer
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Set the cursor position
	COORD cursorPos = {static_cast<SHORT>(startPos.x), std::max<SHORT>(0, static_cast<SHORT>(startPos.y))};

	// Hide the cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &cursorInfo);

	// Process special characters in the entire text
	std::string processedText = ProcessSpecialCharacters(text);

	// Split the text into lines based on "\n" character
	std::vector<std::string> lines;
	std::istringstream iss(processedText);
	std::string line;
	while (std::getline(iss, line, '\n'))
	{
		lines.push_back(line);
	}

	// Set the buffer size and region for writing to the console
	COORD bufferCoord = {0, 0};

	for (const auto &currentLine : lines)
	{
		// Create a CHAR_INFO buffer to hold character and attributes
		std::vector<CHAR_INFO> charBuffer(currentLine.size(), {' ', color});

		// Copy text to CHAR_INFO buffer
		for (size_t i = 0; i < currentLine.size(); ++i)
		{
			charBuffer[i].Char.AsciiChar = currentLine[i];
		}

		// Set the buffer size and region for writing to the console
		COORD bufferSize = {static_cast<SHORT>(currentLine.size()), 1};
		SMALL_RECT writeRegion = {
			static_cast<SHORT>(cursorPos.X),
			static_cast<SHORT>(cursorPos.Y),
			static_cast<SHORT>(cursorPos.X + bufferSize.X - 1),
			static_cast<SHORT>(cursorPos.Y + bufferSize.Y - 1)};

		// Write the CHAR_INFO buffer to the console
		if (!WriteConsoleOutputA(hConsole, charBuffer.data(), bufferSize, bufferCoord, &writeRegion))
		{
			// ... (error handling code)
		}

		// Move the cursor to the next line
		cursorPos.Y++;
	}

	// Show the cursor again after rendering
	cursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

std::string UI::Text::ProcessSpecialCharacters(const std::string &input) const
{
	std::string result;

	for (char c : input)
	{
		if (c == '\t')
		{
			// Handle tabs by adding spaces to align to the next tab stop
			const int tabWidth = 4; // Adjust as needed
			result.append(tabWidth - result.size() % tabWidth, ' ');
		}
		else
		{
			result.push_back(c);
		}
	}

	return result;
}