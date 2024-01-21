<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Fira+Code">
<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Cascadia+Code">

<span style="font-family: 'Fira Code', 'Cascadia Code'; font-variant-ligatures: common-ligatures;">

<div align="center">

  # TEG Game Engine

[![Licence](https://img.shields.io/github/license/Ileriayo/markdown-badges?style=for-the-badge)](./LICENSE) ![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white) ![C#](https://img.shields.io/badge/csharp-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white) ![Windows Terminal](https://img.shields.io/badge/Windows%20Terminal-%234D4D4D.svg?style=for-the-badge&logo=windows-terminal&logoColor=white)
> <span style="font-weight: bold; color: white;">TEG Game Engine - A text based game engine made in C#</span>
</div>

---
# Documentation :
# Engine Class
> <span style="font-weight: bold; color: white;">The `Engine` class takes care of the screen rendering and initializing the game & engine.</span> </br>

Sample main code:
```csharp
using TEG.TEGEngine;

namespace MainCode
{
    public class MainClass
    {
        static readonly MainGame game = new();

        public static void Main(string[] args)
        {
            Engine.Init(game, ConsoleColor.Black);
            Engine.UpdateLoop();
        }
    }
}

```
```csharp
using TEG;
using TEG.Classes;
using TEG.Classes.BasicComponents;
using TEG.TEGEngine;
namespace MainCode
{
    public class MainGame : Game
    {
        public override void Start()
        {
            
        }
        public override void Update()
        {
            Console.WriteLine("Test");
        }
        public override void OnStop()
        {
        }
    }
}
```
## Init
The `Engine.Init(Game)` function starts up the engine, and calls the start function on the game class provided to it on the main file. </br></br>
<u>Example Usage: </u>
```chsarp
Engine.Init(new MainGame());
```
It doesn't have to be the `Game` class, can be any class that derives from the `Game` class

---
## Update Loop
On the `Engine.UpdateLoop()` function, rendering of all of the entity is being handled, mostly using the `Engine.Tick()` function.

### Print Screen
The `Engine.Tick()` function handles rendering the screen and going through the following steps:
- Clear the screen.
- Render all the entitys onto the screen using the `RenderEntitys()` method.
- Call the `Update()` method on the `game` refrence entity.
- Call the `UpdateLoop()` method on the `Input` class.

---
## Stop
The `Engine.StopEngine()` function handles stopping the engine, and goes through the following steps:
- starts by calling the `OnStop()` function on the game variable (that was passed in the `Engine.Init(Game)` function).
- Clears the screen.
- Prints out "Stopping Engine." for debug purposes.
- Resets any changes made to the console settings.
---

# Entity
The Entity class is a simple class made for representing  

## Main Class
### Constructor
The constructor recives the initial position of the `Entity` instance, saves it into memory, and assigns an ID to the entity according to it's position in memory.

### Enabling & Disabling An Instance
The `Enabled` attribute sets the state (Enabled / Disabled) of the entity its being called on. For an example in this code snippet: 
```csharp
Entity obj = new(new Vec2(0,0));
Engine.Instantiate(obj);
obj.Enabled = false;
```
it disables the entity & it's children from being rendered on the screen.

---

### Child-Parent Relations
Child-Parent relations let you accomplish stuff like disabling multiple entitys at the same time, or moving entitys in-sync.

#### Adding Children
The `AddChild(Entity child)` function takes in a refrence to the child you want to add to the parent entity, and adds it's ID to the children array, and should be used like this: 
```csharp
        Vec2 vec = new(1, 3);
        Entity? entity, entity2;
        public override void Start()
        {
            entity = new(vec);
            Engine.Instantiate(entity);
            entity2 = new(new Vec2(0, 6));
            Engine.Instantiate(entity2);
            entity.AddChild(entity2);
        }
```

#### Position-Relation
Every time you will set the `GlobalPosition` attribute on a entity, it will trigger the function also for all its children, and make them move aswell, according to their initial offset from their parent.

#### Getting Amount Of Children
It is possible to get the amount of children of an `Entity` instance using the `GetChildCount()` function, like in the following code snippet: 
```csharp
Entity entity = new(vec);
Engine.Instantiate(entity);
Console.WriteLine(entity.GetChildCount());
```

#### Getting Children Refrences
The `GetChildren()` function returns a vector of refrences to the children of the entity its being used on, like in the following snippet:
```csharp
Entity entity = new(vec);
Engine.Instantiate(entity);
Console.WriteLine(entity.GetChildren()[0].ID);
```

---

### Entity Components 
Entity components are used to add more functionality to a entity, outside of the `Game` class.

#### Adding Components
Using the `AddComponent<T>()`, you can add instances of classes that derive from the `EntityComponent` class. Here's an example:
```csharp
// EntityComponent derived class
public class CustomComp : EntityComponent
{
    public override void Start()
    {
    }

    public override void Update()
    {
        if (Input.IsKeyPressed(ConsoleKey.D))
        {
            entity.transform.GlobalPosition += new Vec2(1, 0);
        }
    }
}
// in the Game derived class: 
Entity entity = new(vec);
entity.AddComponent<CustomComp>();
```
And then the `Start()` function will be called after it has been added.

#### Getting Components
You can get a refrence of a component using the `GetComponent<T>()` function.

---

---
# Component
The `Component` class is a abstract class that is derived to make entity components (Explained in the `Entity` class documentation), that have a few basic functions: 

`Start()` - Called when adding the component onto an entity

`Update()` - Called every frame

`Stop()` - Called after the component / entity has been disabled 

## Basic Components
---


</span>
