using System.Security.Cryptography.X509Certificates;

namespace TEG.Classes
{
    public class Vec2
    {
        public int x, y;
        public Vec2(int x, int y)
        {
            this.x = x;
            this.y = y;
        }
        public Vec2()
        {
            this.x = 0;
            this.y = 0;
        }
        public static Vec2 operator +(Vec2 vec1, Vec2 vec2)
        {
            return new Vec2(vec1.x + vec2.x, vec1.y + vec2.y);
        }
        public static Vec2 operator -(Vec2 vec1, Vec2 vec2)
        {
            return vec1 + (-vec2);
        }
        public static Vec2 operator *(Vec2 vec, int scalar)
        {
            return new Vec2(vec.x * scalar, vec.y * scalar);
        }
        public static Vec2 operator /(Vec2 vec, int scalar)
        {
            if (scalar != 0)
            {
                return new Vec2(vec.x / scalar, vec.y / scalar);
            }
            throw new DivideByZeroException($"Division of {vec} by 0");
        }
        public static Vec2 operator -(Vec2 v)
        {
            return new Vec2(-v.x, -v.y);
        }
        public override string ToString()
        {
            return $"{x}, {y}";
        }
    }
}