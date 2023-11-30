#pragma once

#include "BaseHeader.h"
#include "BaseScene.h"

#include "UiHeader.h"
#include "surface.h"
#include "Event.h"
#include "game.h"

namespace Tmpl8
{
	// Forward declaration
	class Game;

	class GameScene : public BaseScene
	{
		public:
		GameScene(Surface* surface, Game* game);
		~GameScene() override;

		void InitScene() override;
		void Update() override;
		void Delete() override;
		void KeyDown(int key) override;
		void MouseDown(int button, int x, int y) override;


		private:
		Surface* m_ptrSurface;
		GameSceneEnum m_scene = menuScn;

		Event m_menuClickEvents;
		int m_mouseBtnInput, m_mouseX, m_mouseY;

		Game* m_ptrGame;

	};
}
