using TEG.TEGEngine;

namespace MainCode
{
    public class MainClass
    {
        static readonly MainGame game = new();

        public static void Main(string[] args)
        {
            Engine.Init(game);
            Engine.UpdateLoop();
        }
    }
}
