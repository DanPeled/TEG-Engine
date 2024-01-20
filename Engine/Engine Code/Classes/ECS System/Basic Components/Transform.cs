namespace TEG.Classes.BasicComponents
{
    public class Transform : EntityComponent
    {
        private Vec2? globalPosition;
        public Vec2 ParentOffset { get; set; } = new(0, 0);
        public Vec2? GlobalPosition
        {
            get
            {
                return globalPosition;
            }
            set
            {
                globalPosition = value;
                foreach (Transform? childTransform in entity?.GetChildren()?.Select(c => c.GetComponent<Transform>()))
                {
                    if (childTransform != null)
                    {
                        childTransform.GlobalPosition = value - childTransform.ParentOffset;
                        childTransform.ParentOffset = CalculateParentChildOffset(childTransform);
                    }
                    else
                    {
                        continue;
                    }
                }

            }
        }
        public Vec2 LocalPosition => (ParentOffset - GlobalPosition);
        public override void Start()
        {
        }

        public override void Update()
        {
        }
        private Vec2 CalculateParentChildOffset(Transform child)
        {
            return (GlobalPosition ?? new Vec2(0, 0)) - (child.GlobalPosition ?? new Vec2(0, 0));
        }
    }
}