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
        private List<uint> childrenIDs;
        public Transform transform { get; private set; }
        public string tag;

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
            set
            {
                enabled = value;
                foreach (Entity child in GetChildren())
                {
                    child.Enabled = value;
                }
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Entity"/> class with the specified initial position.
        /// </summary>
        /// <param name="initialPos">The initial position of the entity.</param>
        public Entity(Vec2 initialPos)
        {
            // Initialize components list
            components = new List<EntityComponent>();
            childrenIDs = new List<uint>();
            transform = AddComponent<Transform>();
            transform.GlobalPosition = initialPos;
            AddComponent<Renderer>();
        }

        /// <summary>
        /// Adds a new component of type <typeparamref name="T"/> to the entity.
        /// </summary>
        /// <typeparam name="T">The type of the component to add.</typeparam>
        /// <returns>The newly added component.</returns>
        public T AddComponent<T>() where T : EntityComponent, new()
        {
            T comp = new();
            // Add the component to the list
            components.Add(comp);
            comp.Attach(this);
            comp.Start();
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
        /// Removes a component of type <typeparamref name="T"/> from the entity.
        /// </summary>
        /// <typeparam name="T">The type of the component to remove.</typeparam>
        public void RemoveComponent<T>() where T : EntityComponent
        {
            if (components.Count == 0)
            {
                return;
            }
            EntityComponent componentToRemove = components.FirstOrDefault(c => c.GetType() == typeof(T));

            if (componentToRemove != null)
            {
                componentToRemove.Stop();
                components.Remove(componentToRemove);
            }
        }

        /// <summary>
        /// Updates all components attached to the entity.
        /// </summary>
        public void Update()
        {
            foreach (EntityComponent c in components)
            {
                if (c.Enabled)
                    c?.Update();
            }
        }

        /// <summary>
        /// Retrieves an array of child entities.
        /// </summary>
        /// <returns>An array of child entities.</returns>
        public Entity[] GetChildren()
        {
            List<Entity> children = new List<Entity>();
            foreach (uint ID in childrenIDs)
            {
                children.Add(Engine.GetEntityWithID(ID) ?? new Entity(new Vec2(0, 0)));
            }
            return children.ToArray();
        }

        /// <summary>
        /// Gets the count of child entities.
        /// </summary>
        /// <returns>The count of child entities.</returns>
        public int GetChildCount()
        {
            return childrenIDs.Count;
        }

        /// <summary>
        /// Adds a child entity to the current entity.
        /// </summary>
        /// <param name="child">The child entity to add.</param>
        public void AddChild(Entity child)
        {
            child.transform.ParentOffset = transform.CalculateParentChildOffset(child.transform);
            childrenIDs.Add(child.ID);
        }

        /// <summary>
        /// Destroys the entity and its children.
        /// </summary>
        public void Destroy()
        {
            foreach (Entity child in GetChildren())
            {
                child.Destroy();
            }
            Engine.DestroyEntity(this);
        }

        /// <summary>
        /// Checks wheter an object is obscured by an another
        /// </summary>
        /// <param name="other">The object which might obscure</param>
        /// <returns>Wheter the object is obscured or not</returns>
        public bool IsObscuredBy(Entity other)
        {
            // TODO: MAKE LOGIC
            return other.ID > ID;
        }
    }
}
