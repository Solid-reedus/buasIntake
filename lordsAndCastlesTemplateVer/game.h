#pragma once

#include "BaseHeader.h"
#include "Scenes.h"
#include "surface.h"
#include "BaseScene.h"
#include <functional>


namespace Tmpl8 
{
	class Surface;
	class Game
	{
		public:
		void SetTarget( Surface* surface ) { m_ptrScreen = surface; }
		void Init();
		void Shutdown();
		void Tick( float deltaTime );
		void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
		void MouseDown(int button, int x, int y);
		void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
		void KeyUp( int key ) { /* implement if you want to handle keys */ }
		void KeyDown(int key);
		void ChangeScene(GameSceneEnum newScene);

		private:

		Surface* m_ptrScreen;
		std::unique_ptr<BaseScene> m_ptrCurrentScene = nullptr;
		GameSceneEnum m_currentSceneEnum = menuScn;
	};

}; // namespace Tmpl8s

