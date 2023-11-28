
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
The `Engine::Init(Game game_)` function starts up the Input class, and calls the start function on the game class provided to it on the main file. </br></br>
<u>Example Usage: </u>
```cpp
Engine::Init(Game()); // Doesn't have to be the Game class, can be any class that derives from the Game class
```

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
The Object class is an abstract class that behaves as a template for classes such as the `GameObject` class, and has some basic function that are the same for all the instances. </br></br>
**<u>Take in notice:</u>** The Object class should **NOT** be used be used by itself, and instead be used by classes that derive from it. 

## Main Class
### Constructor
The constructor recives the initial position of the Object instance, saves it into memory, and assigns an ID to the object according to it's position in memory. The constructor shouldn't be used by itself most of the time, instead you might use the `Instantiate()`function, provided by classes such as `GameObject` & `Text`.

### Enabling & Disabling An Instance
The `SetEnabled(bool state)` function sets the state (Enabled / Disabled) of the object its being called on. For an example in this code snippet: 
```cpp
GameObject *obj = GameObject::Instantiate(args...); // Replace with actual args
obj->SetEnabled(false);
```
it disables the object & it's children from being rendered on the screen.

---
### Child-Parent Relations
Child-Parent relations let you accomplish stuff like disabling multiple objects at the same time, or moving objects in-sync.
#### Adding Children
The `AddChild(Object *child)` function takes in a refrence to the child you want to add to the parent object, and adds it's ID to the children array, and should be used like this: 
```cpp
// Using the GameObject class as an example
GameObject *parent = GameObject::Instantiate(args...);
GameObject *child = GameObject::Instantiate(args...);
parent->AddChild(child);
```

#### Getting Amount Of Children
It is possible to get the amount of children of an `Object` class-derived instance using the `GetChildCount()` function, like in the following code snippet: 
```cpp
// Using the GameObject class as an example
GameObject *obj = GameObject::Instantiate(args...);
std::cout << obj->GetChildCount();
```

#### Getting Children Refrences
The `GetChildren()` function returns a vector of refrences to the children of the object its being used on, like in the following snippet:
```cpp
// Using the GameObject class as an example
GameObject *parent = GameObject::Instantiate(args...);
GameObject *child = GameObject::Instantiate(args...);
parent->AddChild(child); // Adding a child

std::cout << parent->GetChildren()[0].get().GetID(); // Prints out the ID of the first child in the parent's children
```

---
## Console Attributes Class
The ConsoleAttributes class holds data for coloring text and objects in the terminal, with variables such as BLACK, RED, GREEN.

---

