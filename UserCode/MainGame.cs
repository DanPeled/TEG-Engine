using TEG;
using TEG.Classes;
using TEG.Classes.BasicComponents;
using TEG.TEGEngine;
namespace MainCode
{
    public class MainGame : Game
    {
        Vec2 vec = new(1, 3);
        Entity? entity;
        public override void Start()
        {
            Console.WriteLine(vec);
            Console.WriteLine(-vec);
            entity = new(vec);
            Engine.Instantiate(entity);
            entity = new(vec + new Vec2(0, 1));
            Engine.Instantiate(entity);
        }
        public override void Update()
        {
            vec += new Vec2(1, 0);
            entity.GetComponent<Transform>().Position += new Vec2(1, 0);

        }
        public override void OnStop()
        {
            throw new NotImplementedException();
        }
    }
}