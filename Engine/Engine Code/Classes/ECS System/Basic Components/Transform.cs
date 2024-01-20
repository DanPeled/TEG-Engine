namespace TEG.Classes.BasicComponents
{
    class Transform : EntityComponent
    {
        private Vec2? position;
        public Vec2? Position
        {
            get
            {
                return position;
            }
            set
            {
                position = value;
            }
        }
        public override void Start()
        {
        }

        public override void Update()
        {
        }
    }
}