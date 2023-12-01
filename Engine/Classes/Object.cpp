#include "Object.h"
using namespace TEG;
void Object::Render(const CONSOLE_SCREEN_BUFFER_INFO &csbi) const
{
}

bool Object::GetEnabled()
{
	return this->enabled;
}

void Object::SetEnabled(bool state)
{
	this->enabled = state;
	for (Object &child : GetChildren())
	{
		child.SetEnabled(state);
	}
}

void Object::Destroy()
{
	auto it = std::remove_if(Object::objects.begin(), Object::objects.end(), [this](Object &ref)
							 { return &ref == this; });

	if (it != Object::objects.end())
	{
		Object::objects.erase(it, Object::objects.end());
	}
	else
	{
		// std::cerr << "Error: Object not found in objects vector." << std::endl;
	}
	if (this->GetChildCount() > 0)
	{
		DestroyChildren();
	}
	system("cls");
}
Object::~Object() {}

Object Object::GetObjectWithID(unsigned int ID)
{
	auto it = std::find_if(objects.begin(), objects.end(),
						   [ID](const std::reference_wrapper<Object> &objRef)
						   {
							   return objRef.get().GetID() == ID;
						   });

	if (it != objects.end())
	{
		return it->get();
	}
	else
	{
		// Handle the case when the object with the given ID is not found.
		return Object(Vector2(0, 0));
	}
}
std::vector<std::reference_wrapper<Object>> Object::GetChildren() const
{
	std::vector<std::reference_wrapper<Object>> result;

	for (unsigned int childID : this->children)
	{
		auto it = std::find_if(objects.begin(), objects.end(),
							   [childID](const std::reference_wrapper<Object> &objRef)
							   {
								   return objRef.get().GetID() == childID;
							   });

		if (it != objects.end())
		{
			result.emplace_back(*it);
		}
		// Handle the case when the child with the specified ID is not found.
		// For now, do nothing.
	}

	return result;
}