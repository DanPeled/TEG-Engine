using TEG.Classes;
using TEG.Classes.BasicComponents;
using TEG.Classes.Input;
using TEG.TEGEngine;
namespace MainCode
{
    public class CustomComp : EntityComponent
    {
        public override void Start()
        {
        }

        public override void Update()
        {
            int maxWidth = Console.WindowWidth - 1; // 0-based index
            int maxHeight = Console.WindowHeight - 1; // 0-based index
            if (entity.transform.GlobalPosition.x >= maxWidth)
            {
                entity.transform.GlobalPosition = new Vec2(1, entity.transform.GlobalPosition.y);
            }
            if (Input.IsKeyPressed(ConsoleKey.D))
            {
                entity.transform.GlobalPosition += new Vec2(1, 0);
            }
            else if (Input.IsKeyPressed(ConsoleKey.Q))
            {
                Engine.StopEngine();
            }
        }
    }
}