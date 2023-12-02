<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Fira+Code">
<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Cascadia+Code">

<span style="font-family: 'Fira Code', 'Cascadia Code'; font-variant-ligatures: common-ligatures;">

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
# [Engine Class](https://github.com/DanPeled/TEG-Engine/blob/main/Engine/Engine.cpp)
> <span style="font-weight: bold; color: white;">The `Engine` class takes care of the screen rendering and initializing the game & engine.</span> </br>

Sample main file:
```cpp
#include "Engine/Engine.h"
#include "Game/Game.h"
#include <thread>
using namespace TEG;

int main()
{
	Engine::Init(Game());

	std::thread updateThread(&Engine::UpdateLoop);

	updateThread.join();
	return 0;
}
```
## Init
The `Engine::Init(Game game_)` function starts up the Input class, and calls the start function on the game class provided to it on the main file. </br></br>
<u>Example Usage: </u>
```cpp
Engine::Init(Game());
```
It doesn't have to be the `Game` class, can be any class that derives from the `Game` class

---
## Update Loop
On the `Engine::UpdateLoop()` function, rendering of all of the object is being handled, mostly using the `Engine::PrintScreen()` function.

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

---

# [Object](https://github.com/DanPeled/TEG-Engine/blob/main/Engine/Classes/Object.h)
The Object class is an abstract class that behaves as a template for classes such as the `GameObject` class, and has some basic function that are the same for all the instances. </br></br>
**<u>Take in notice:</u>** The Object class should **NOT** be used be used by itself, and instead be used by classes that derive from it. 

## Main Class
### Constructor
The constructor recives the initial position of the Object instance, saves it into memory, and assigns an ID to the object according to it's position in memory. The constructor shouldn't be used by itself most of the time, instead you might use the `Instantiate()`function, provided by classes such as `GameObject` & `Text`.
### Object Render List
Inside of the `Object` class, you can find the `objects` refrence wrapper vector, that automatically stores refrences to all the objects that were created using `Instantiate()` function, and each frame of the engine calls the render function of each one of the refrences.
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
#### Position-Relation
Every time you will call the `SetPos()` function on a object, it will trigger the function also for all its children, and make them move aswell, according to their initial offset from their parent.

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
### Object Components 
Object components are used to add more functionality to a object, outside of the `Game` class.
#### Adding Components
Using the `AddComponent(shared_ptr<Object>)`, you can add instances of classes that derive from the Component class. Here's an example:
```cpp
// component derived class
class ExampleComp : public Component
{
    void Start() override 
    {
      cout << "Start() Ran";
    }
}

// in the Game derived class: 
GameObject *obj = Instantiate(args...);
obj->AddComponent(make_shared<ExampleComp>());

```
And then the `Start()` function will be called after it has been added.

#### Getting Components
You can get a `vector` of `shared pointers` to the components using the `GetComponents()` function.

---
## Console Attributes Class
The ConsoleAttributes class holds data for coloring text and objects in the terminal, with variables such as BLACK, RED, GREEN.

---
# [Component](https://github.com/DanPeled/TEG-Engine/blob/main/Engine/Classes/Component.h)
The `Component` class is a abstract class that is derived to make object components (Explained in [`Object`](https://github.com/DanPeled/TEG-Engine#object-components) class documentation), that have a few basic functions: 

`Start()` - Called when adding the component onto an object

`Update()` - Called every frame

`Stop()` - Called after the component / object has been disabled 

---
# [GameObject](https://github.com/DanPeled/TEG-Engine/blob/main/Engine/Classes/GameObject.h)
The GameObject class is a class for basic rectangle-like shape rendering, which will probably have more shapes to it in the future.

## Instantiation
Instantiation of an instance of this class is important for it to be automatically rendered into the screen, and is done by using the `GameObject::Instantiate()` static function, that takes in the following arguments:
- `Vector2 pos` - For the initial position of the GameObject.
- `int width` - For the width of the GameObject.
- `int height` - For the height of the GameObject.
- `char symbol` - For the symbol the GameObject will be constructed of, # for an example.
- `bool hasFill_` - For checking if the renderer should fill the shape.
</br>

The function should by used like in the following:
```cpp
GameObject *obj = GameObject::Instantiate(
  Vector2(3,5), // pos
  5,            // width
  5,            // height
  '#',          // symbol
  true          // hasFill
);  
``` 
* Take in care, the function returns back a *pointer* to the actual object

The function works by: 
1. First calling the constructor on a new GameObject instance it creates
1. Adding it to the `Object::objects` render array
1. Returning back the pointer to the object it created

## Render Function
The `Render()` function takes care of rendering the game object on the screen, and goes through the following steps: 

1. Makes sure the object used is in the `Object::objects` vector, and if it isn't throws an error message.

1. Goes through the positions the GameObject's instance rendering should be in, and adds them into a char buffer.

1. Renders the char buffer on the screen.

---

</span>