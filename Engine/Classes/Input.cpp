#include "Input.h"
#include <cstdio>
#include <vector>
#include <cstring>
#include <variant>

HANDLE Input::hStdin;
DWORD Input::fdwSaveOldMode;
DWORD Input::fdwMode;

void Input::Initialize()
{
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");

	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit("GetConsoleMode");

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode");
}

void Input::Cleanup()
{
	SetConsoleMode(hStdin, fdwSaveOldMode);
}

std::vector<InputEvent> Input::GetInputEvents()
{
	std::vector<InputEvent> events;

	DWORD cNumRead;
	INPUT_RECORD irInBuf[128];

	if (ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead))
	{
		for (DWORD i = 0; i < cNumRead; ++i)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT:
				events.push_back({irInBuf[i].Event.KeyEvent.bKeyDown ? InputEventType::KeyPressed : InputEventType::KeyReleased,
								  irInBuf[i].Event.KeyEvent.uChar.AsciiChar});
				if (irInBuf[i].Event.KeyEvent.bKeyDown)
				{
					events.push_back({InputEventType::KeyClicked, irInBuf[i].Event.KeyEvent.uChar.AsciiChar});
				}
				break;

				// case MOUSE_EVENT:
				// {
				// 	MOUSE_EVENT_RECORD mouseEvent = irInBuf[i].Event.MouseEvent;
				// 	events.push_back({InputEventType::MouseMoved, mouseEvent.dwMousePosition.X, mouseEvent.dwMousePosition.Y});

				// 	if (mouseEvent.dwEventFlags == MOUSE_MOVED)
				// 	{
				// 		// Handle mouse move event
				// 	}
				// 	else if (mouseEvent.dwEventFlags == 0)
				// 	{
				// 		// Handle mouse button press/release events
				// 		if (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
				// 			events.push_back({InputEventType::MouseButtonPressed, MouseButton::Left});
				// 		else if (mouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED)
				// 			events.push_back({InputEventType::MouseButtonPressed, MouseButton::Right});
				// 	}
				// 	break;
				// }

			default:
				break;
			}
		}
	}

	return events;
}

void Input::SimulateKeyPress(char key, bool shift, bool ctrl, bool alt)
{
	INPUT_RECORD irInBuf[2];

	// Key down event
	irInBuf[0] = CreateKeyEvent(key, true, shift, ctrl, alt);

	// Key up event
	irInBuf[1] = CreateKeyEvent(key, false, shift, ctrl, alt);

	DWORD cNumWritten;
	WriteConsoleInput(hStdin, irInBuf, 2, &cNumWritten);
}
void Input::SimulateKeyPress(char key)
{
	SimulateKeyPress(key, false, false, false);
}
INPUT_RECORD Input::CreateKeyEvent(char key, bool keyDown, bool shift, bool ctrl, bool alt)
{
	INPUT_RECORD ir;
	ir.EventType = KEY_EVENT;
	ir.Event.KeyEvent.bKeyDown = keyDown;
	ir.Event.KeyEvent.wRepeatCount = 1;		   // Number of times the key is to be pressed/released
	ir.Event.KeyEvent.wVirtualKeyCode = 0;	   // Virtual key code, not needed for ASCII characters
	ir.Event.KeyEvent.wVirtualScanCode = 0;	   // Scan code, not needed for ASCII characters
	ir.Event.KeyEvent.uChar.UnicodeChar = key; // ASCII character
	ir.Event.KeyEvent.dwControlKeyState =
		(shift ? SHIFT_PRESSED : 0) |
		(ctrl ? LEFT_CTRL_PRESSED : 0) |
		(alt ? LEFT_ALT_PRESSED : 0);
	return ir;
}

void Input::ErrorExit(LPCSTR lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);
	SetConsoleMode(hStdin, fdwSaveOldMode);
	ExitProcess(0);
}
