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
            entity.sprite = "######\n######\n######\n######";
            entity.AddComponent<CustomComp>();
            Engine.Instantiate(entity);
            entity = new(new Vec2(0, 4));
            entity.sprite = "/////////\n/////////\n/////////\n/////////";
            Engine.Instantiate(entity);
        }
        public override void Update()
        {


        }
        public override void OnStop()
        {
            throw new NotImplementedException();
        }
    }
}