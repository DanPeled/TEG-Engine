#pragma once

#include <windows.h>
#include <vector>
#include <variant>

enum class InputEventType
{
    KeyPressed,
    KeyReleased,
    KeyClicked,
    MousePressed,
    MouseReleased,
    MouseClicked,
    MouseMoved,
    MouseButtonPressed,
};

enum class MouseButton
{
    Left,
    Right,
    Middle,
};

struct InputEvent
{
    InputEventType type;
    std::variant<char, MouseButton> data;

    InputEvent(InputEventType t, char k) : type(t), data(k) {}
    InputEvent(InputEventType t, MouseButton button) : type(t), data(button) {}
    // Add other members if needed
};

class Input
{
public:
    static HANDLE hStdin;
    static DWORD fdwSaveOldMode;
    static DWORD fdwMode;

    static void Initialize();
    static void Cleanup();
    static std::vector<InputEvent> GetInputEvents();

private:
    static void ErrorExit(LPCSTR lpszMessage);
};
