#include "Text.h"
using namespace TEG;

UI::Text::Text(Vector2 position_, std::string text_)
	: Object(position_), globalPosition(position_), text(text_), color(ConsoleAttributes().WHITE)
{
}

UI::Text::Text(Vector2 position_, std::string text_, WORD color_) : Object(position_), globalPosition(globalPosition), text(text_), color(color_)
{
}

UI::Text::Text()
	: Object(Vector2(0, 0)), globalPosition(Vector2(0, 0)), text(""), color(ConsoleAttributes().WHITE)
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

	// Split the text into lines based on "\n" character
	std::vector<std::string> lines;
	std::istringstream iss(text);
	std::string line;
	while (std::getline(iss, line, '\n'))
	{
		lines.push_back(line);
	}

	// Set the cursor globalPosition
	COORD cursorPos = {static_cast<SHORT>(startPos.x), std::max<SHORT>(0, static_cast<SHORT>(startPos.y))};

	// Render each line separately
	for (const auto &currentLine : lines)
	{
		// Handle special characters like '\t'
		std::string processedLine = ProcessSpecialCharacters(currentLine);

		// Create a CHAR_INFO buffer to hold character and attributes
		std::vector<CHAR_INFO> charBuffer(processedLine.size(), {' ', color});

		// Copy text to CHAR_INFO buffer
		for (size_t i = 0; i < processedLine.size(); ++i)
		{
			charBuffer[i].Char.AsciiChar = processedLine[i];
		}

		// Write the CHAR_INFO buffer to the console
		COORD bufferSize = {static_cast<SHORT>(processedLine.size()), 1};
		COORD bufferCoord = {0, 0};

		// Explicitly cast values to SHORT to address narrowing conversion warnings
		SMALL_RECT writeRegion = {
			static_cast<SHORT>(cursorPos.X),
			static_cast<SHORT>(cursorPos.Y),
			static_cast<SHORT>(cursorPos.X + bufferSize.X - 1),
			static_cast<SHORT>(cursorPos.Y + bufferSize.Y - 1)};

		if (!WriteConsoleOutputA(hConsole, charBuffer.data(), bufferSize, bufferCoord, &writeRegion))
		{
			// ... (error handling code)
		}

		// Move the cursor to the next line
		cursorPos.Y++;
	}
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