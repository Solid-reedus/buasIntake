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

	class HowToPlayScene : public BaseScene
	{
		public:

		HowToPlayScene(Surface* p_ptrSurface, Game* p_ptrGame);
		~HowToPlayScene() override;

		void InitScene() override;
		void Update(float p_deltaTime) override;
		void Delete() override;
		void KeyDown(SDL_Keycode key) override;
		void MouseDown(int button, int x, int y) override;
		void MouseScroll(int y) override;

		private:

		void DrawScrollBar();

		//preset colors
		const Pixel k_red = 0xff4444;
		const Pixel k_grey = 0x808080;
		const Pixel k_gold = 0xFFD700;

		Surface* m_ptrSurface;
		GameSceneEnum m_scene = howToPlayScn;

		Event m_HowToPlayClickEvents;
		int m_mouseBtnInput, m_mouseX, m_mouseY;

		int relativeHeight = 0;
		int maxHeight = 500;


		Button m_GoToMenubtn;

		Game* m_ptrGame;

		Sprite uiImage = Sprite(new Surface("assets/uiBannerBuildings.png"), 1);
		Sprite uiStats = Sprite(new Surface("assets/uiStats.png"), 1);

	};
}
