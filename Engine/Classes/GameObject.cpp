#include "GameObject.h"

using namespace TEG;
GameObject::GameObject(Vector2 position_, int width_, int height_, char symbol_)
    : Object(position_), position(position_), width(width_), height(height_), symbol(symbol_)
{
}

GameObject::~GameObject()
{
}

GameObject GameObject::instantiate(Vector2 pos, int width, int height, char symbol)
{
    GameObject obj = GameObject(pos, width, height, symbol);
    Object::objects.push_back(std::ref(obj));
    return obj;
}

void GameObject::render(const CONSOLE_SCREEN_BUFFER_INFO &csbi) const
{
    // Retrieve object properties
    Vector2 startPos = this->getPos();
    int width = this->getWidth();
    int height = this->getHeight();
    char symbol = this->getSymbol();

    // Create a HANDLE to the console output buffer
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Create a CHAR_INFO buffer for the GameObject
    std::vector<CHAR_INFO> charBuffer(width * height);

    // Initialize each element of the CHAR_INFO vector
    for (int i = 0; i < width * height; ++i)
    {
        charBuffer[i].Char.UnicodeChar = symbol;
        charBuffer[i].Attributes = FOREGROUND_INTENSITY;
    }

    // Set up the rectangle to be updated
    SMALL_RECT rect;
    rect.Top = static_cast<SHORT>(startPos.y);
    rect.Left = static_cast<SHORT>(startPos.x);
    rect.Bottom = static_cast<SHORT>(startPos.y + height - 1);
    rect.Right = static_cast<SHORT>(startPos.x + width - 1);

    // Update the screen buffer with the GameObject
    WriteConsoleOutput(hConsole, charBuffer.data(), {static_cast<SHORT>(width), static_cast<SHORT>(height)}, {0, 0}, &rect);
}

std::vector<std::reference_wrapper<TEG::Object>> TEG::Object::objects;