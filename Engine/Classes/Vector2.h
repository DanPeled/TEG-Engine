#pragma once

namespace TEG
{
	struct Vector2
	{
		int x;
		int y;

		Vector2(int x_, int y_) : x(x_), y(y_) {}
		Vector2 operator+(Vector2 other)
		{
			Vector2 v(x + other.x, y + other.y);
			return v;
		}
	};
}
