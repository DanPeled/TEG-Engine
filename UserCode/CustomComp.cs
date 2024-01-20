using TEG.Classes;
using TEG.Classes.BasicComponents;

public class CustomComp : EntityComponent
{
    public override void Start()
    {
    }

    public override void Update()
    {
        this.entity.GetComponent<Transform>().Position += new Vec2(1, 0);
    }
}