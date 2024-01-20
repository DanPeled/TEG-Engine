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
                if (!enabled) Stop();
                else Awake();
            }
        }
        public Entity? entity;
        public virtual void Start() { }
        public virtual void Awake() { }
        public virtual void Update() { }
        public virtual void Stop() { }
        public void Attach(Entity entity)
        {
            this.entity = entity;
        }
        public EntityComponent()
        {

        }
    }
}