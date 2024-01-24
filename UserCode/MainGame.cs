using TEG;
using TEG.Classes;
using TEG.Classes.BasicComponents;
using TEG.TEGEngine;
namespace MainCode
{
    public class MainGame : Game
    {
        Vec2 vec = new(1, 3);
        Entity? entity, entity2;
        public override void Start()
        {
            Console.WriteLine(vec);
            Console.WriteLine(-vec);
            entity = new(vec);
            entity.GetComponent<Renderer>().sprite = "X";
            entity.AddComponent<CustomComp>();
            entity2 = new(new Vec2(0, 6));
            entity2.GetComponent<Renderer>().sprite = "/////////\n/////////\n/////////\n/////////";
            entity2.tag = "test";
            Engine.Instantiate(entity);
            Engine.Instantiate(entity2);
        }
        public override void Update()
        {


        }
        public override void OnStop()
        {
        }
    }
}