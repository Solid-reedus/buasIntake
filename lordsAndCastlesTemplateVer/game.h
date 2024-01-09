#pragma once

#include "BaseHeader.h"
#include "Scenes.h"
#include "BaseScene.h"
#include "surface.h"
#include "SDL.h"


namespace Tmpl8 
{
	class Surface;
	class Game
	{
		public:
		void SetTarget( Surface* surface ) { m_ptrScreen = surface; }
		void Init();
		void Shutdown();
		void Tick(float deltaTime);
		void MouseUp(int button, int x, int y) {};
		void MouseDown(int button, int x, int y);
		void MouseMove(int x, int y);
		void MouseScroll(int y);
		void KeyUp(SDL_Keycode  key) {};
		void KeyDown(SDL_Keycode key);

		void ChangeScene(GameSceneEnum newScene);

		private:
		Surface* m_ptrScreen;
		std::unique_ptr<BaseScene> m_ptrCurrentScene = nullptr;
		GameSceneEnum m_currentSceneEnum = menuScn;


	};

}; // namespace Tmpl8s

