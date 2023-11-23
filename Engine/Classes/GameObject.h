#include "Vector2.h"
namespace TEG
{
	class GameObject
	{
		Vector2 position;
		int width;
		int height;
		char symbol;

	public:
		GameObject(Vector2 position_, int width_, int height_, char symbol_);
		~GameObject();

		static GameObject instantiate(Vector2 pos, int width, int height, char symbol);

		inline Vector2 getPos() const
		{
			return position;
		}

		inline void setPos(Vector2 newPos)
		{
			position = newPos;
		}

		inline int getWidth() const
		{
			return width;
		}

		inline int getHeight() const
		{
			return height;
		}

		inline char getSymbol() const
		{
			return symbol;
		}
	};
}