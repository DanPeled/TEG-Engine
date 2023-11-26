#pragma once
#include <stdexcept>
namespace TEG
{
	struct Vector2
	{
		int x;
		int y;

		Vector2(int x_, int y_) : x(x_), y(y_) {}
		Vector2() : x(0), y(0){}

		Vector2 operator+(const Vector2 &other) const
		{
			return Vector2(x + other.x, y + other.y);
		}

		Vector2 operator-(const Vector2 &other) const
		{
			return Vector2(x - other.x, y - other.y);
		}

		Vector2 operator*(int scalar) const
		{
			return Vector2(x * scalar, y * scalar);
		}

		Vector2 operator/(int scalar) const
		{
			if (scalar != 0)
			{
				return Vector2(x / scalar, y / scalar);
			}
			else
			{
				throw std::invalid_argument("Division by 0 is not allowed!");
			}
		}

		Vector2 operator-() const
		{
			return Vector2(-x, -y);
		}
	};
}
