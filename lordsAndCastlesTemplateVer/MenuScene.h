#pragma once

#include "BaseHeader.h"
#include "BaseScene.h"
#include "surface.h"
#include "Event.h"
#include "game.h"
#include "Button.h"

namespace Tmpl8
{
	// Forward declaration
	class Game;

	class MenuScene : public BaseScene
	{
		public:

		MenuScene(Surface* surface, Game* game);
		~MenuScene() override;

		void InitScene() override;
		void Update(float p_deltaTime) override;
		void Delete() override;
		void KeyDown(SDL_Keycode key) override;
		void MouseDown(int button, int x, int y) override;
		

		private:

		//preset colors
		const Pixel k_red = 0xff4444;
		const Pixel k_grey = 0x808080;
		const Pixel k_gold = 0xFFD700;

		Surface* m_ptrSurface;
		GameSceneEnum m_scene = menuScn;

		Event m_menuClickEvents;
		int m_mouseBtnInput, m_mouseX, m_mouseY;

		Button m_playGamebtn;
		Button m_GoToHowToPlaysbtn;
		Game* m_ptrGame;

	};
}
