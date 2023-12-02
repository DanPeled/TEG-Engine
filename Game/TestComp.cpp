#include "TestComp.h"
#include <iostream>
#include "../Engine/Engine.h"
void TestComp::Update()
{
	std::cout << "Test";
}
void TestComp::Start()
{
	Engine::LogOut(LogType::Warning, "TEST");
}