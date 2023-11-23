#include "GameObject.h"

using namespace TEG;
GameObject::GameObject(Vector2 position_, int width_, int height_, char symbol_)
        : position(position_), width(width_), height(height_), symbol(symbol_)
    {
    }

    GameObject::~GameObject()
    {
        // Destructor logic, if needed
    }

    GameObject GameObject::instantiate(Vector2 pos, int width, int height, char symbol)
    {
        return GameObject(pos, width, height, symbol);
    }
