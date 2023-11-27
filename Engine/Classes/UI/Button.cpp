// #include "Button.h"
// using namespace TEG;
// template <typename... K>
// UI::Button::Button(Vector2 position_, std::string text_, WORD color_, void (*func)(K...))
// 	: Object(position_), text(text_), color(color_), onClick(func)
// {
// }

// template <typename... K>
// UI::Button::Button(Vector2 position_, std::string text_, void (*func)(K...))
// 	: Object(position_), text(text_), color(ConsoleAttributes().WHITE), onClick(func)
// {
// }

// template <typename... K>
// UI::Button *UI::Button::Instantiate(Vector2 pos, std::string text, WORD color, void (*func)(K...))
// {
// 	UI::Button *obj = new UI::Button(pos, text, color, func);
// 	Object::objects.push_back(*obj);
// 	return obj;
// }

// template <typename... K>
// UI::Button *UI::Button::Instantiate(Vector2 pos, std::string text, void (*func)(K...))
// {
// 	UI::Button *obj = new UI::Button(pos, text, func);
// 	Object::objects.push_back(obj);
// 	return obj;
// }

// // Explicit instantiation for the combinations of template arguments you expect to use
// template UI::Button::Button(Vector2 position_, std::string text_, WORD color_, void (*func)());
// template UI::Button::Button(Vector2 position_, std::string text_, void (*func)());
// template UI::Button *UI::Button::Instantiate(Vector2 pos, std::string text, WORD color, void (*func)());
// template UI::Button *UI::Button::Instantiate(Vector2 pos, std::string text, void (*func)());
