using System;
using System.Collections.Generic;

namespace TEG.Classes.Input
{
    public class Input
    {
        private static List<ConsoleKey> pressedKeys = new List<ConsoleKey>();
        private static List<ConsoleKey> lastFrameKeys = new List<ConsoleKey>();

        public static bool IsKeyPressed(ConsoleKey key)
        {
            return pressedKeys.Contains(key);
        }

        public static bool IsKeyReleased(ConsoleKey key)
        {
            return !IsKeyPressed(key);
        }

        public static bool IsKeyClicked(ConsoleKey key)
        {
            bool wasPressedLastFrame = lastFrameKeys.Contains(key);
            bool isPressedNow = IsKeyPressed(key);

            // Return true if the key is pressed now but was not pressed in the last frame
            return isPressedNow && !wasPressedLastFrame;
        }

        public static void UpdateLoop()
        {
            // Update the list of keys pressed in the last frame
            lastFrameKeys.Clear();
            lastFrameKeys.AddRange(pressedKeys);

            // Update the list of keys pressed now
            UpdatePressedKeys();
        }

        private static void UpdatePressedKeys()
        {
            pressedKeys.Clear();

            while (Console.KeyAvailable)
            {
                ConsoleKeyInfo keyInfo = Console.ReadKey(intercept: true);
                pressedKeys.Add(keyInfo.Key);
            }
        }
    }
}
