#pragma once

#include "BaseHeader.h"
#include "BaseScene.h"
#include "UiHeader.h"
#include "surface.h"
#include "Event.h"
#include "SDL.h"


namespace Tmpl8
{
	class MenuScene : public BaseScene
	{
		public:
		MenuScene(Surface* m_surface);
		~MenuScene() override;

		void InitScene() override;
		void Update() override;
		void Delete() override;
		void KeyDown(int m_key) override;
		void MouseDown(int m_button, int m_x, int m_y) override;

		private:
		//Sprite* rotatingGun;
		//int frame;
		Surface* surface;

		Event menuClickEvents;
		int mouseBtnInput, mouseX, mouseY;

		Button testBtn;

	};
}
