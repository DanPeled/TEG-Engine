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
    static void SimulateKeyPress(char key, bool shift, bool ctrl, bool alt);
    static INPUT_RECORD CreateKeyEvent(char key, bool keyDown, bool shift, bool ctrl, bool alt);
    static void SimulateKeyPress(char key);

private:
    static void ErrorExit(LPCSTR lpszMessage);
};
