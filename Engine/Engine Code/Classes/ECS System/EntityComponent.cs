namespace TEG.Classes
{
    public abstract class EntityComponent
    {
        private bool enabled = true;
        public bool Enabled
        {
            get
            {
                return enabled;
            }
            set
            {
                enabled = value;
            }
        }
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