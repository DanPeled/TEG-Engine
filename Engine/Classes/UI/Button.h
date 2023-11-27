
// #include <windows.h>
// #include "../Vector2.h"
// #include <string>
// #include "../Object.h"
// #include <algorithm>
// #include <sstream>
// #include <string>
// namespace TEG
// {
// 	namespace UI
// 	{
// 		class Button : public Object
// 		{
// 		public:
// 			std::string text;
// 			WORD color;

// 			template <typename... K>
// 			Button(Vector2 position_, std::string text_, WORD color, void (*func)(K...));
// 			template <typename... K>
// 			Button(Vector2 position_, std::string text_, void (*func)(K...));
// 			template <typename... K>
// 			static Button *Instantiate(Vector2 position, std::string text, WORD color, void (*func)(K...));
// 			template <typename... K>
// 			static Button *Instantiate(Vector2 position, std::string text, void (*func)(K...));
// 			void (*onClick)();
// 		};
// 	}
// }
