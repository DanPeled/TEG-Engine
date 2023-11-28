
<div align="center">

  # TEG Game Engine

[![Licence](https://img.shields.io/github/license/Ileriayo/markdown-badges?style=for-the-badge)](./LICENSE) ![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white) ![Windows Terminal](https://img.shields.io/badge/Windows%20Terminal-%234D4D4D.svg?style=for-the-badge&logo=windows-terminal&logoColor=white)
> <span style="font-weight: bold; color: white;">TEG Game Engine - A text based game engine made in C++</span>
</div>

# Getting Started: 

**TEG engine is currently only *Windows* supported** </br>
In order to make the project into an executable, run the compile.bat file, here's the cmd command:
```bash
compile.bat
```
or 
```bash
.\compile.bat
```

---
# Documentation :
# [Engine.cpp](https://github.com/DanPeled/TEG-Engine/blob/main/Engine/Engine.cpp)
> <span style="font-weight: bold; color: white;">The `Engine` class takes care of the screen rendering and initializing the game & engine.</span>
## Init
The `Engine::Init(Game game_)` function starts up the Input class, and calls the start function on the game class provided to it on the main file.

---
## Update Loop
On the `Engine::UpdateLoop()` function, the `Engine::PrintScreen()` function

### Print Screen
The `PrintScreen()` function handles rendering the screen and going through the following steps:
- Clear the screen.
- Go through the `Object::objects` refrence vector, and call the Render function on each one.

---
## Stop
The `Engine::OnStop()` function handles stopping the engine, and goes through the following steps:
- starts by calling the `Exit()` function on the game variable (that was passed in the [`Engine::Init(Game game_)`](https://github.com/DanPeled/TEG-Engine/tree/main#init) function).
- Clears the screen.
- Prints out "Engine Stopped." for debug purposes.
- Cleans up the Input class by calling the `Input::Cleanup()` function.

# Object.cpp
The Object class is an abstract class that behaves as a template for classes such as the GameObject class, and has some basic function that are the same for all the instances.
## Main Class
### Constructor
The constructor recives the initial position of the Object instance, and saves it into memory, and it shouldn't be used by itself most of the time, instead you might use the Instantiate() function.
## Console Attributes Class
The ConsoleAttributes class holds data for coloring text and objects in the terminal, with variables such as BLACK, RED, GREEN.

---
