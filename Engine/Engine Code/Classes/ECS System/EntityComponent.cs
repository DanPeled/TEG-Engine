namespace TEG.Classes
{
    public abstract class EntityComponent
    {
        private readonly bool enabled = true;
        public bool Enabled => enabled;
        public Entity? entity;
        public abstract void Start();
        public abstract void Update();
        public void Stop() { }
        public void Attach(Entity entity)
        {
            this.entity = entity;
        }
        public EntityComponent()
        {

        }
    }
}