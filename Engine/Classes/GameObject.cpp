#include "GameObject.h"
#include <iostream>
#include <algorithm>

using namespace TEG;

Vector2 defaultVector(0, 0);

GameObject::GameObject(Vector2 position_, int width_, int height_, char symbol_, bool hasFill_)
    : Object(position_), width(width_), height(height_), symbol(symbol_), hasFill(hasFill_)
{
}

GameObject::GameObject() : Object(defaultVector)
{
}

GameObject *GameObject::Instantiate(Vector2 pos, int width, int height, char symbol, bool hasFill)
{
    GameObject *obj = new GameObject(pos, width, height, symbol, hasFill);
    Object::objects.push_back(*obj);
    return obj;
}

void GameObject::Render(const CONSOLE_SCREEN_BUFFER_INFO &csbi) const
{
    // Ensure 'this' is in the objects vector
    auto it = std::find_if(Object::objects.begin(), Object::objects.end(), [this](Object &ref)
                           { return &ref == this; });

    if (it == Object::objects.end())
    {
        std::cerr << "Error: 'this' not found in objects vector." << std::endl;
        return;
    }

    // Retrieve object properties
    Vector2 startPos = this->GetPos();

    // Create a HANDLE to the console output buffer
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set up the rectangle to be updated
    SMALL_RECT rect;
    rect.Top = static_cast<SHORT>(startPos.y);
    rect.Left = static_cast<SHORT>(startPos.x);
    rect.Bottom = static_cast<SHORT>(startPos.y + height - 1);
    rect.Right = static_cast<SHORT>(startPos.x + width - 1);

    // Create a CHAR_INFO buffer for the GameObject
    std::vector<CHAR_INFO> charBuffer(width * height);

    // Initialize each element of the CHAR_INFO vector
    for (int i = 0; i < width * height; ++i)
    {
        charBuffer[i].Char.UnicodeChar = ' ';
        charBuffer[i].Attributes = FOREGROUND_BLUE; // Customize the color based on object properties
    }

    // Draw the outline only if hasFill is not checked
    if (!hasFill)
    {
        // Draw top and bottom borders
        for (int i = 0; i < width; ++i)
        {
            charBuffer[i].Char.UnicodeChar = symbol;                        // Top border
            charBuffer[i + (height - 1) * width].Char.UnicodeChar = symbol; // Bottom border
        }

        // Draw left and right borders
        for (int i = 0; i < height; ++i)
        {
            charBuffer[i * width].Char.UnicodeChar = symbol;               // Left border
            charBuffer[i * width + (width - 1)].Char.UnicodeChar = symbol; // Right border
        }
    }
    else
    {
        // Fill the entire buffer if hasFill is checked
        for (int i = 0; i < width * height; ++i)
        {
            charBuffer[i].Char.UnicodeChar = symbol;
        }
    }

    // Update the screen buffer with the GameObject
    WriteConsoleOutput(hConsole, charBuffer.data(), {static_cast<SHORT>(width), static_cast<SHORT>(height)}, {0, 0}, &rect);
}

std::vector<std::reference_wrapper<TEG::Object>> TEG::Object::objects = {};
