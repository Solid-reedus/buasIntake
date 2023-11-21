#pragma once

#include "BaseHeader.h"
#include "BaseScene.h"
#include "surface.h"
#include "Event.h"


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

		private:
		//Sprite* rotatingGun;
		//int frame;
		Surface* surface;

		Event menuEvents;

	};
}
