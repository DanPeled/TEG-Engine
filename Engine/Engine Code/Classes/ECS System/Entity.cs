using System;
using System.Collections.Generic;
using TEG.Classes.BasicComponents;
using TEG.TEGEngine;

namespace TEG.Classes
{
    public class Entity
    {
        private bool enabled = true;
        private List<EntityComponent> components;
        public uint ID { get; private set; }
        public bool Enabled
        {
            get
            {
                return enabled;
            }
            set
            {
                this.enabled = value;
            }
        }
        public Entity(Vec2 initialPos)
        {
            // Initialize components list
            components = new List<EntityComponent>();
            ID = Engine.ObtainID(this);
            AddComponent<Transform>().Position = initialPos;
        }

        public T AddComponent<T>() where T : EntityComponent, new()
        {
            T comp = new();
            // Add the component to the list
            components.Add(comp);

            comp.Start();
            return comp;
        }
        public T? GetComponent<T>() where T : EntityComponent
        {
            T? res = components.FirstOrDefault(c => c.GetType() == typeof(T)) as T;
            return res;
        }
        public void Update()
        {
            foreach (EntityComponent c in components)
            {
                c.Update();
            }
        }
    }
}
