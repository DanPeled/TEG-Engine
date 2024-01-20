using System;
using System.Collections.Generic;
using System.Linq;
using TEG.Classes.BasicComponents;
using TEG.TEGEngine;

namespace TEG.Classes
{
    /// <summary>
    /// Represents an entity in the game world.
    /// </summary>
    public class Entity
    {
        private bool enabled = true;
        private List<EntityComponent> components;

        /// <summary>
        /// Gets or sets the unique identifier of the entity.
        /// </summary>
        public uint ID { get; private set; }

        /// <summary>
        /// Gets or sets a value indicating whether the entity is enabled.
        /// </summary>
        public bool Enabled
        {
            get { return enabled; }
            set { enabled = value; }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Entity"/> class with the specified initial position.
        /// </summary>
        /// <param name="initialPos">The initial position of the entity.</param>
        public Entity(Vec2 initialPos)
        {
            // Initialize components list
            components = new List<EntityComponent>();
            ID = Engine.ObtainID(this);
            AddComponent<Transform>().Position = initialPos;
        }

        /// <summary>
        /// Adds a new component of type <typeparamref name="T"/> to the entity.
        /// </summary>
        /// <typeparam name="T">The type of the component to add.</typeparam>
        /// <returns>The newly added component.</returns>
        public T? AddComponent<T>() where T : EntityComponent, new()
        {
            T comp = new();
            if (comp != null)
            {
                // Add the component to the list
                components.Add(comp);
                comp.Attach(this);
                comp.Start();
            }
            return comp;
        }

        /// <summary>
        /// Gets the first component of type <typeparamref name="T"/> attached to the entity.
        /// </summary>
        /// <typeparam name="T">The type of the component to retrieve.</typeparam>
        /// <returns>The component of type <typeparamref name="T"/> if found, otherwise <c>null</c>.</returns>
        public T? GetComponent<T>() where T : EntityComponent
        {
            T? res = components.FirstOrDefault(c => c.GetType() == typeof(T)) as T;
            return res;
        }

        /// <summary>
        /// Updates all components attached to the entity.
        /// </summary>
        public void Update()
        {
            foreach (EntityComponent c in components)
            {
                c?.Update();
            }
        }
    }
}
