#pragma once
#include <string>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Engine/Main/EngineHeader.h"
#include "Scene_1.h"
#include "Configs/CmakeConfig.h"

namespace Game
{
	class App
	{
	public:
		App();
		App(const App &rhs) = delete;
		App(App &&rhs) = delete;
		~App();

	public:
		void Start();
		void Quit();

	private:
		bool ShouldExit();

	private:
		bool isActive;
		Scene* scene;
		Engine::Window window;
		Engine::Engine engine;
	};
}
