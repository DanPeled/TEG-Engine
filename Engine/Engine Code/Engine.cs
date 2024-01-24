using System;
using System.Collections.Generic;
using System.Reflection;
using System.Text;
using TEG.Classes;
using TEG.Classes.BasicComponents;
using TEG.Classes.Input;
using TEG.Util;

namespace TEG.TEGEngine
{
    /// <summary>
    /// Represents the game engine.
    /// </summary>
    public class Engine
    {
        #region Class Vars

        /// <summary>
        /// The current game associated with the engine.
        /// </summary>
        private static Game? game;

        /// <summary>
        /// Flag indicating whether the engine is running.
        /// </summary>
        private static bool RUNNING;

        /// <summary>
        /// Number of frames processed.
        /// </summary>
        private static uint frames = 0;

        /// <summary>
        /// Target frames per second.
        /// </summary>
        private static int targetFPS = 30; // Set your desired FPS here

        /// <summary>
        /// Target time per frame.
        /// </summary>
        private static float targetFrameTime => 1000.0f / targetFPS;

        /// <summary>
        /// List of entity references.
        /// </summary>
        private static List<Entity> entities = new List<Entity>();

        #endregion

        #region Class Methods

        /// <summary>
        /// Initializes the game engine.
        /// </summary>
        /// <param name="game_">The game to be associated with the engine.</param>
        /// <param name="bgColor">The background color for the console.</param>
        public static void Init(Game game_, ConsoleColor bgColor)
        {
            Console.OutputEncoding = Encoding.UTF8;
            Console.BackgroundColor = bgColor;
            entities = new List<Entity>();
            Console.WriteLine("INITIALIZING ENGINE");
            game = game_;
            RUNNING = true;
            Console.CursorVisible = false;
            Console.WriteLine("FINISHED INITIALIZING ENGINE");
            Console.Clear();
            game.Start();
        }

        /// <summary>
        /// Initializes the game engine with a default background color (Black).
        /// </summary>
        /// <param name="game_">The game to be associated with the engine.</param>
        public static void Init(Game game_)
        {
            Init(game_, ConsoleColor.Black);
        }

        /// <summary>
        /// Main update loop of the game engine.
        /// </summary>
        public static void UpdateLoop()
        {
            long lastTickTime = DateTime.Now.Ticks;
            int frameCounter = 0;

            while (true)
            {
                long currentTime = DateTime.Now.Ticks;
                float elapsedMilliseconds = (currentTime - lastTickTime) / TimeSpan.TicksPerMillisecond;

                if (elapsedMilliseconds >= targetFrameTime)
                {
                    Console.Clear();
                    Tick();
                    lastTickTime = currentTime;
                    frameCounter++;

                    if (frameCounter % targetFPS == 0)
                    {
                        frames = 0;
                    }
                }
                if (!RUNNING)
                {
                    break;
                }
            }

            OnStop();
        }

        /// <summary>
        /// Renders game objects.
        /// </summary>
        public static void RenderObjects()
        {
            if (entities.Count == 0) return;
            foreach (Entity entity in entities)
            {
                if (entity != null && entity.Enabled)
                {
                    Render(entity);
                    entity?.Update();
                }
            }
        }

        /// <summary>
        /// Renders a specific entity.
        /// </summary>
        /// <param name="entity">The entity to render.</param>
        public static void Render(Entity entity)
        {
            Renderer? renderer = entity.GetComponent<Renderer>();
            if (entity == null || renderer == null || renderer.sprite == null)
            {
                return;
            }

            string[] lines = renderer.sprite.Split("\n") ?? new string[] { "" };

            int x = entity.transform.GlobalPosition.x;
            int y = entity.transform.GlobalPosition.y;

            foreach (string line in lines)
            {
                Console.SetCursorPosition(x, y);
                Console.ForegroundColor = renderer.color ?? ConsoleColor.White;
                Console.Write(line);
                Console.ResetColor();
                y++;
            }
        }

        /// <summary>
        /// Stops the game engine.
        /// </summary>
        public static void StopEngine()
        {
            game?.OnStop();
            RUNNING = false;
            Console.Clear();
            SetCursorPosition(new Vec2(0, 0));
            Console.WriteLine("Stopping Engine");
        }

        /// <summary>
        /// Called when the engine stops.
        /// </summary>
        private static void OnStop()
        {
            Console.BackgroundColor = ConsoleColor.Black;
        }

        /// <summary>
        /// Updates the engine for each frame.
        /// </summary>
        public static void Tick()
        {
            frames += 1;
            RenderObjects();
            game?.Update();
            Input.UpdateLoop();
        }

        /// <summary>
        /// Sets the console cursor position.
        /// </summary>
        /// <param name="vec">The position vector.</param>
        public static void SetCursorPosition(Vec2 vec)
        {
            Console.SetCursorPosition(vec.x, vec.y);
        }

        /// <summary>
        /// Instantiates a new entity in the engine.
        /// </summary>
        /// <param name="entity">The entity to instantiate.</param>
        public static void Instantiate(Entity entity)
        {
            PropertyInfo idProperty = entity.GetType().GetProperty("ID");
            if (idProperty != null)
            {
                idProperty.SetValue(entity, ObtainID(entity));
            }

            entities.Add(entity);
        }


        /// <summary>
        /// Removes an entity from the engine.
        /// </summary>
        /// <param name="e">The entity to remove.</param>
        public static void RemoveEntity(Entity e)
        {
            Entity entity = entities.FirstOrDefault(r => r == e);
            if (entity != null)
            {
                entities.Remove(entity);
            }
        }

        /// <summary>
        /// Obtains the ID of an entity.
        /// </summary>
        /// <param name="e">The entity.</param>
        /// <returns>The ID of the entity.</returns>
        /// <summary>
        /// Obtains the ID of an entity.
        /// </summary>
        /// <param name="e">The entity.</param>
        /// <returns>The ID of the entity.</returns>
        public static uint ObtainID(Entity e)
        {
            if (e != null)
            {
                // Check if the entity is already assigned an ID
                if (e.ID != 0)
                {
                    return e.ID;
                }
                else
                {
                    // Assign a new ID based on the current count
                    uint newID = (uint)entities.Count;
                    return newID;
                }
            }

            // Return 0 for cases where the entity is null
            return 0;
        }


        /// <summary>
        /// Retrieves an entity with a specific ID.
        /// </summary>
        /// <param name="id">The ID of the entity to retrieve.</param>
        /// <returns>The entity with the specified ID, or null if not found.</returns>
        public static Entity? GetEntityWithID(uint id)
        {
            Entity[] matchingEntities = entities.Where(r => r.ID == id).ToArray();

            if (matchingEntities.Length > 0)
            {
                return matchingEntities[0];
            }

            // Return null if no matching entity is found.
            return null;
        }


        /// <summary>
        /// Destroys an entity by its ID.
        /// </summary>
        /// <param name="ID">The ID of the entity to destroy.</param>
        public static void DestroyEntity(uint ID)
        {
            entities.Remove(GetEntityWithID(ID));
        }

        /// <summary>
        /// Destroys an entity.
        /// </summary>
        /// <param name="entity">The entity to destroy.</param>
        public static void DestroyEntity(Entity entity)
        {
            DestroyEntity(entity.ID);
        }

        /// <summary>
        /// Retrives all the entities with the provided tag
        /// </summary>
        /// <param name="tag">The tag to search for</param>
        /// <returns>An array of the entities with the matching tag</returns>
        public static Entity[] GetEntitiesWithTag(string tag)
        {
            var matchingEntities = entities?.Where(r => r != null && string.Equals(r.tag, tag, StringComparison.OrdinalIgnoreCase));

            if (matchingEntities != null && matchingEntities.Any())
            {
                return matchingEntities.ToArray();
            }

            // Handle case where no entities with the specified tag are found.
            return new Entity[0];
        }

        #endregion
    }
}
